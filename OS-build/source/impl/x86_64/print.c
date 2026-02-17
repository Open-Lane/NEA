#include "print.h"

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


void print_int(int n) {
    if (n == 0) {
        print_char('0');
        return;
    }

    if (n < 0) {
        print_char('-');
        n = -n;
    }

    // Calculate the digits in reverse
    char digits[10]; // max 10 digits for int32
    int i = 0;
    while (n > 0) {
        digits[i++] = (n % 10) + '0'; // convert digit to ASCII
        n /= 10;
    }

    // Print digits in correct order
    for (int j = i - 1; j >= 0; j--) {
        print_char(digits[j]);
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



