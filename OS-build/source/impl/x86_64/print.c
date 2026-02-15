#include "print.h"

#define TABLE 128
#define COL_NUM 80
#define ROW_NUM 25




struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = WHITE | (BLACK << 4);

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < COL_NUM; col++) {
        buffer[col + COL_NUM * row] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < ROW_NUM; i++) {
        clear_row(i);
    }
}

void print_newline() {
    col = 0;

    if (row < ROW_NUM - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < ROW_NUM; row++) {
        for (size_t col = 0; col < COL_NUM; col++) {
            struct Char character = buffer[col + COL_NUM * row];
            buffer[col + COL_NUM * (row - 1)] = character;
        }
    }

    clear_row(ROW_NUM - 1);
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col >= COL_NUM) {
        print_newline();
    }

    buffer[col + COL_NUM * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };

    col++;
}

void print_str(const char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

void delete_char(void) {
    if (row==0 && col==0) return;
    if (col>0) col--; else { row--; col=COL_NUM-1; }
    buffer[col + COL_NUM * row] = (struct Char){ ' ', color };
}


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
