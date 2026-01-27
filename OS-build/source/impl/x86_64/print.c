#include "print.h"

#define TABLE 128

/* VGA text grid */
static size_t ROW_NUM = 25;
static size_t COL_NUM = 80;

/* VGA text cell */
struct cha {
    uint8_t character;
    uint8_t colour;
};

/* VGA memory */
static struct cha* vga_buffer = (struct cha*)0xB8000;
struct cha* buffer = (struct cha*)0xB8000;

/* Cursor */
size_t col = 0;
size_t row = 0;

/* Current colour attribute */
static uint8_t colour = WHITE | (BLACK << 4);

/* Clear one row */
void row_clear(size_t r) {
    struct cha empty = { ' ', colour };
    for (size_t c = 0; c < COL_NUM; c++) {
        buffer[c + COL_NUM * r] = empty;
    }
}

/* Clear screen */
static void vga_clear(void) {
    for (size_t r = 0; r < ROW_NUM; r++) row_clear(r);
}

/* Newline + scroll */
static void vga_newline(void) {
    col = 0;
    if (row < ROW_NUM - 1) {
        row++;
        return;
    }
    for (size_t r = 1; r < ROW_NUM; r++) {
        for (size_t c = 0; c < COL_NUM; c++) {
            vga_buffer[(r - 1) * COL_NUM + c] = vga_buffer[r * COL_NUM + c];
        }
    }
    row_clear(ROW_NUM - 1);
}

/* Put char */
static void vga_putc(char ch) {
    if (ch == '\n') { vga_newline(); return; }
    vga_buffer[row * COL_NUM + col].character = (uint8_t)ch;
    vga_buffer[row * COL_NUM + col].colour    = colour;
    col++;
    if (col >= COL_NUM) vga_newline();
}

/* Public API */
void print_init(uint64_t mbi_ptr) {
    (void)mbi_ptr;  /* ignore multiboot info */
    COL_NUM = 80; ROW_NUM = 25;
    vga_clear();
    col = row = 0;
}

void print_clear(void) { col = row = 0; vga_clear(); }
void print_newline(void) { vga_newline(); }
void print_char(char ch) { vga_putc(ch); }
void print_str(const char *s) { for (size_t i=0; s[i]; i++) vga_putc(s[i]); }
void print_set_colour(uint8_t fg, uint8_t bg) { colour = (fg & 0x0F) | ((bg & 0x0F) << 4); }
void delete_char(void) {
    if (row==0 && col==0) return;
    if (col>0) col--; else { row--; col=COL_NUM-1; }
    buffer[col + COL_NUM * row] = (struct cha){ ' ', colour };
}

/* -------- Keyboard mapping -------- */
static char scancode_map[TABLE];

void insert_key(unsigned char key, char value){ scancode_map[key]=value; }
char lookup_key(unsigned char key){ return scancode_map[key]; }

void init_keymap(void) {
    for (int i=0;i<TABLE;i++) scancode_map[i]=0;

    insert_key(0x1E, 'a');
    insert_key(0x30, 'b');
    insert_key(0x2E, 'c');
    insert_key(0x20, 'd');
    insert_key(0x12, 'e');
    insert_key(0x21, 'f');
    insert_key(0x22, 'g');
    insert_key(0x23, 'h');
    insert_key(0x17, 'i');
    insert_key(0x24, 'j');
    insert_key(0x25, 'k');
    insert_key(0x26, 'l');
    insert_key(0x32, 'm');
    insert_key(0x31, 'n');
    insert_key(0x18, 'o');
    insert_key(0x19, 'p');
    insert_key(0x10, 'q');
    insert_key(0x13, 'r');
    insert_key(0x1F, 's');
    insert_key(0x14, 't');
    insert_key(0x16, 'u');
    insert_key(0x2F, 'v');
    insert_key(0x11, 'w');
    insert_key(0x2D, 'x');
    insert_key(0x15, 'y');
    insert_key(0x2C, 'z');

    insert_key(0x02, '1');
    insert_key(0x03, '2');
    insert_key(0x04, '3');
    insert_key(0x05, '4');
    insert_key(0x06, '5');
    insert_key(0x07, '6');
    insert_key(0x08, '7');
    insert_key(0x09, '8');
    insert_key(0x0A, '9');
    insert_key(0x0B, '0');

    insert_key(0x39, ' ');
    insert_key(0x1C, '\n');
    insert_key(0x0E, '\b');
}
