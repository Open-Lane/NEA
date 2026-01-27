#include "print.h"

/* Playfield size */
#define FIELD_W 10
#define FIELD_H 20

/* small RNG */
static unsigned int rng_state = 123456789u;
static unsigned int rnd32(void) {
    rng_state ^= (rng_state << 13);
    rng_state ^= (rng_state >> 17);
    rng_state ^= (rng_state << 5);
    return rng_state;
}

/* field: 0 empty, 1 filled */
static unsigned char field[FIELD_H][FIELD_W];

/* 4x4 tetromino bitmaps (16-bit each, MSB->LSB) */
static const unsigned short tetrominos[7] = {
    0x0F00, /* I */
    0x8E00, /* J */
    0x2E00, /* L */
    0x6600, /* O */
    0x6C00, /* S */
    0x4E00, /* T */
    0xC600  /* Z */
};

/* tetromino 4x4 bit access with rotation */
static int tetromino_bit(unsigned short shape, int x, int y, int rot) {
    int index;
    if (rot == 0) index = y * 4 + x;
    else if (rot == 1) index = (3 - x) * 4 + y;
    else if (rot == 2) index = (3 - y) * 4 + (3 - x);
    else index = x * 4 + (3 - y);
    return (shape >> (15 - index)) & 1;
}

/* collision test */
static int collides(unsigned short shape, int px, int py, int rot) {
    int x, y;
    for (y = 0; y < 4; ++y) {
        for (x = 0; x < 4; ++x) {
            if (!tetromino_bit(shape, x, y, rot)) continue;
            int fx = px + x;
            int fy = py + y;
            if (fx < 0 || fx >= FIELD_W) return 1;
            if (fy < 0 || fy >= FIELD_H) return 1;
            if (field[fy][fx]) return 1;
        }
    }
    return 0;
}

/* place piece into field */
static void place_piece(unsigned short shape, int px, int py, int rot) {
    int x, y;
    for (y = 0; y < 4; ++y) {
        for (x = 0; x < 4; ++x) {
            if (tetromino_bit(shape, x, y, rot)) {
                int fx = px + x;
                int fy = py + y;
                if (fx >= 0 && fx < FIELD_W && fy >= 0 && fy < FIELD_H)
                    field[fy][fx] = 1;
            }
        }
    }
}

/* clear completed lines */
static void clear_lines(void) {
    int y, x, yy;
    for (y = FIELD_H - 1; y >= 0; --y) {
        int full = 1;
        for (x = 0; x < FIELD_W; ++x) if (!field[y][x]) { full = 0; break; }
        if (full) {
            for (yy = y; yy > 0; --yy)
                for (x = 0; x < FIELD_W; ++x)
                    field[yy][x] = field[yy - 1][x];
            for (x = 0; x < FIELD_W; ++x) field[0][x] = 0;
            ++y; /* recheck same row after shift */
        }
    }
}

/* render the field and current falling piece */
static void render(unsigned short shape, int px, int py, int rot) {
    int y, x;
    print_str("\n");
    for (y = 0; y < FIELD_H; ++y) {
        print_char('|');
        for (x = 0; x < FIELD_W; ++x) {
            int occ = field[y][x];
            int relx = x - px;
            int rely = y - py;
            if (!occ && relx >= 0 && relx < 4 && rely >= 0 && rely < 4)
                if (tetromino_bit(shape, relx, rely, rot)) occ = 1;
            print_char(occ ? '#' : ' ');
        }
        print_char('|');
        print_char('\n');
    }
    print_str("+----------+\n");
    print_str("a:left d:right s:down w:rot (space):drop q:quit\n");
}

/* non-blocking keyboard poll: returns 0 if no key available */
static char poll_key_nonblocking(void) {
    uint8_t status = inb(0x64);
    if (!(status & 1)) return 0;
    uint8_t scancode = inb(0x60);
    if (scancode & 0x80) return 0; /* release code */
    return lookup_key(scancode);
}

/* wait ticks while polling keyboard; returns 1 and sets *out if a key found */
static int wait_tick_with_key(char *out, int ticks) {
    int t;
    for (t = 0; t < ticks; ++t) {
        char k = poll_key_nonblocking();
        if (k) { *out = k; return 1; }
        volatile int z;
        for (z = 0; z < 20000; ++z) asm volatile("nop");
    }
    return 0;
}

/* tetris_start: public entry that runs until user quits back to prompt */
void tetris_start(void) {
    int x, y;
    for (y = 0; y < FIELD_H; ++y) for (x = 0; x < FIELD_W; ++x) field[y][x] = 0;

    unsigned short shape = tetrominos[(int)(rnd32() % 7)];
    int px = FIELD_W / 2 - 2;
    int py = 0;
    int rot = 0;

    render(shape, px, py, rot);

    for (;;) {
        char key = 0;
        int got = wait_tick_with_key(&key, 300);

        if (got) {
            if (key == 'q') {
                print_str("\nReturning to prompt\n");
                the_kernel();
                return;
            }
            if (key == 'a') {
                if (!collides(shape, px - 1, py, rot)) px--;
            } else if (key == 'd') {
                if (!collides(shape, px + 1, py, rot)) px++;
            } else if (key == 's') {
                if (!collides(shape, px, py + 1, rot)) {
                    py++;
                } else {
                    place_piece(shape, px, py, rot);
                    clear_lines();
                    shape = tetrominos[(int)(rnd32() % 7)];
                    px = FIELD_W / 2 - 2; py = 0; rot = 0;
                    if (collides(shape, px, py, rot)) { print_str("\nGame Over\n"); return; }
                }
            } else if (key == 'w') {
                int nr = (rot + 1) & 3;
                if (!collides(shape, px, py, nr)) rot = nr;
            } else if (key == ' ') {
                while (!collides(shape, px, py + 1, rot)) py++;
                place_piece(shape, px, py, rot);
                clear_lines();
                shape = tetrominos[(int)(rnd32() % 7)];
                px = FIELD_W / 2 - 2; py = 0; rot = 0;
                if (collides(shape, px, py, rot)) { print_str("\nGame Over\n"); return; }
            }
        } else {
            /* gravity */
            if (!collides(shape, px, py + 1, rot)) {
                py++;
            } else {
                place_piece(shape, px, py, rot);
                clear_lines();
                shape = tetrominos[(int)(rnd32() % 7)];
                px = FIELD_W / 2 - 2; py = 0; rot = 0;
                if (collides(shape, px, py, rot)) { print_str("\nGame Over\n"); return; }
            }
        }

        /* crude screen refresh then render */
        print_clear();
		row = 0;
		col = 0;
		print_str("TETRIS  -  a:left d:right s:down w:rot space:drop q:quit\n");
		render(shape, px, py, rot);
    }
}

