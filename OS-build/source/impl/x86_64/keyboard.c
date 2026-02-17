#include "print.h"
#define TABLE 128


static char scancode_map[TABLE];

void insert_key(unsigned char key, char value){
    scancode_map[key] = value;
}

char lookup_key(unsigned char key){
    char c = scancode_map[key];
    // Auto-capitalize lowercase letters if Shift is pressed
    if (c != 0) {
        if (shift_pressed == 'y' && c >= 'a' && c <= 'z') {;
            c -= 32;
            return c;
        }
    }

    if (c == 0 || key == 0x2A || key == 0x36 || key == 0x1D /* Ctrl */ || key == 0x38 /* Alt */)  {
        // Key not found: print new line and prompt
        print_newline();
        print_str("> this is an unknown scancode, add it to the table if you want IDK: ");

        // Convert scancode to hex string
        char buffer[3];
        buffer[0] = "0123456789ABCDEF"[(key >> 4) & 0xF]; // high nibble
        buffer[1] = "0123456789ABCDEF"[key & 0xF];        // low nibble
        buffer[2] = '\0';

        print_str(buffer);
        print_newline();
        print_char('>');
        return 0;
    }

    return c; // return mapped character
}


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

    insert_key(0x35, '/');
    insert_key(0x28, '\'');
    insert_key(0x1A, '[');
    insert_key(0x1B, ']');
    insert_key(0x0C, '-');
    insert_key(0x0C, '-');
    insert_key(0x0D, '=');
    insert_key(0x27, ';');
    insert_key(0x2B, '#');


}
