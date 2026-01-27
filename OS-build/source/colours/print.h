#pragma once

#include <stdint.h>
#include <stddef.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;


extern size_t row;
extern size_t col;



enum {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 8,
	LIGHT_BULE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	PINK = 13,
	YELLOW = 14,
	WHITE = 15,

};

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}


extern const uint8_t FONT_8x16[96][24];
void print_init(uint64_t multiboot_info_ptr);
void tetris_start();
void the_kernel(uint64_t mbi_ptr);
void init_keymap();
char lookup_key(unsigned char scancode);
void delete_char();
void print_clear();
void print_char(char character);
void print_str(const char *string);
void print_set_colour(uint8_t foreground, uint8_t background);
