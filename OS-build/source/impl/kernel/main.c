#include "print.h"
#define COMMAND_SIZE 128

static char command[COMMAND_SIZE] = {0};
static int cmd_index = 0;
int i = 0;
char shift_pressed = 'n';


static void drain_keyboard(void) {
	while (1) {
		uint8_t status = inb(0x64);
		if ((status & 1) == 0) break;
		(void)inb(0x60);
	}
}


// Compare two strings manually (no string.h)
static int str_equal(const char* a, const char* b) {
	int i = 0;
	while (1) {
		if (a[i] != b[i]) return 0;
		if (a[i] == '\0') return 1;
		i++;
	}
}

// Handle a command
static void handle_command(void) {
	if (str_equal(command, "help")) {
		print_char('\n');
		print_str("Available commands:\n");
		print_str("help  - Show this message\n");
		print_str("ALU  - Start Tetris");
	} else if (str_equal(command, "ALU")) {
		print_char('\n');
		print_str("perfroming ALU test...\n");
		ALU_test ();
	} else if (command[0] != '\0') {
		print_char('\n');
		print_str("Unknown command: ");
		int i = 0;
		while (command[i] != '\0') {
			print_char(command[i]);
			i++;
		}
		print_str("\npsss (try help)");
	}

	// Reset command buffer
	cmd_index = 0;
	command[0] = '\0';
}



void print_scancode_loop(char letter) {
	if (letter == '\n') {
		handle_command();
		print_str("\n>");
		i = 0;
		return;
	}
	if (letter == '\b') {
		if (i > 0) {
			i--;
			cmd_index--;
			delete_char();
		}
		return;
	}
	print_char(letter);
	i++;
	if (cmd_index + 1 < COMMAND_SIZE) {
		command[cmd_index++] = letter;
		command[cmd_index] = '\0';
	}
}


void read_scancodes(){
	while (1) {
		uint8_t status = inb(0x64);
		if (status & 1) {
			uint8_t scancode = inb(0x60);

			// Detect Shift press
			if (scancode == 0x2A || scancode == 0x36) { // Left or Right Shift pressed
				shift_pressed = 'y';
				continue; // skip further processing
			}

			// Detect Shift release
			if (scancode == 0xAA || scancode == 0xB6) { // Left or Right Shift released
				shift_pressed = 'n';
				continue; // skip further processing
			}

			// Only handle normal key press (not release)
			if (!(scancode & 0x80)) {
				char letter = lookup_key(scancode); // this now auto-capitalizes letters if shift is pressed
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


