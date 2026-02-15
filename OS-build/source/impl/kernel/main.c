#include "print.h"

int i = 0;

static void drain_keyboard(void) {
	while (1) {
		uint8_t status = inb(0x64);
		if ((status & 1) == 0) break;
		(void)inb(0x60);
	}
}



void print_scancode_loop(char letter) {
	if (letter == '\n') {
		print_char('\n');
		print_str(">");
		i = 0;
		return;
	}
	if (letter == '\b') {
		if (i > 0) {
			i--;
			delete_char();
		}
		return;
	}
	print_char(letter);
	i++;
}



void read_scancodes(){
	while (1) {
		uint8_t status = inb(0x64);
		if (status & 1) {
			uint8_t scancode = inb(0x60);
			if (!(scancode & 0x80)) {
				char letter = lookup_key(scancode);
				print_scancode_loop(letter);
			}
		}
		asm volatile("nop");
	}
}


void the_kernel() {
	print_clear();
	init_keymap();
	print_set_color(WHITE,BLACK);
	print_str("|------------------------------------------------------------------------------|");
	print_str("|                this is OS hit! my computer scince NEA project                |");
	print_str("|------------------------------------------------------------------------------|");
	print_str(">");
	drain_keyboard();
	read_scancodes();
}


