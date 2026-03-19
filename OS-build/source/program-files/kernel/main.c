#include "print.h"
#define COMMAND_SIZE 128

static char command[COMMAND_SIZE] = {0};
static int cmd_index = 0;
int i = 0;
char shift_pressed = 'n';

typedef struct {
	const char* name;
	uint8_t value;
} ColorEntry;

static ColorEntry colors[] = {
	{"BLACK", BLACK},
	{"BLUE", BLUE},
	{"GREEN", GREEN},
	{"CYAN", CYAN},
	{"RED", RED},
	{"MAGENTA", MAGENTA},
	{"BROWN", BROWN},
	{"LIGHT_GREY", LIGHT_GREY},
	{"LIGHT_BLUE", LIGHT_BULE},
	{"LIGHT_GREEN", LIGHT_GREEN},
	{"LIGHT_CYAN", LIGHT_CYAN},
	{"LIGHT_RED", LIGHT_RED},
	{"PINK", PINK},
	{"YELLOW", YELLOW},
	{"WHITE", WHITE},
};

#define COLOR_COUNT (sizeof(colors)/sizeof(colors[0]))





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


static uint8_t color_from_name(const char* name) {
	for (int i = 0; i < COLOR_COUNT; i++) {
		if (str_equal(name, colors[i].name)) {
			return colors[i].value;
		}
	}
	return BLACK; // default if unknown
}


void str_to_upper(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		}
		i++;
	}
}

// Capture whatever the user typed in command buffer, then reset it
// Reads input from keyboard into buffer, similar to command input
void get_input(char* output, int max_len) {
	int idx = 0;
	print_str("> "); // show prompt

	while (1) {
		uint8_t status = inb(0x64);
		if (!(status & 1)) continue;
		uint8_t scancode = inb(0x60);

		// Shift press/release
		if (scancode == 0x2A || scancode == 0x36) { shift_pressed = 'y'; continue; }
		if (scancode == 0xAA || scancode == 0xB6) { shift_pressed = 'n'; continue; }

		// Only key press, not release
		if (scancode & 0x80) continue;

		char c = lookup_key(scancode);

		if (c == '\n') {
			print_newline();
			output[idx] = '\0';
			return;
		}

		if (c == '\b') {
			if (idx > 0) {
				idx--;
				delete_char();
			}
			continue;
		}

		// Normal char
		if (idx < max_len - 1) {
			output[idx++] = c;
			print_char(c);
		}
	}
}




void colour_change() {
	char text_color[32] = {0};
	char bg_color[32] = {0};

	print_str("Available colors:\nBLACK\nBLUE\nGREEN\nCYAN\nRED\nMAGENTA\nBROWN\nLIGHT_GREY\nLIGHT_BLUE\nLIGHT_GREEN\nLIGHT_CYAN\nLIGHT_RED\nPINK\nYELLOW\nWHITE\n");

	// Get text color
	print_str("Enter text color: ");
	get_input(text_color, sizeof(text_color));
	str_to_upper(text_color);

	// Get background color
	print_str("Enter background color: ");
	get_input(bg_color, sizeof(bg_color));
	str_to_upper(bg_color);

	// Convert names to enum values
	uint8_t fg = color_from_name(text_color);
	uint8_t bg = color_from_name(bg_color);

	print_set_color(fg, bg);

	print_str("\nColors changed!\n");
}




// Handle a command
static void handle_command(void) {
	if (str_equal(command, "help")) {
		print_char('\n');
		print_str("Available commands:\n");
		print_str("help  - Show this message\n");
		print_str("ALU  - performs ALU check\n");
		print_str("colour  - changes colours");
	} else if (str_equal(command, "ALU")) {
		print_char('\n');
		print_str("perfroming ALU test...\n");
		ALU_test ();
	} else if (str_equal(command, "colour")) {
		print_char('\n');
		print_str("change colurs to what you want...\n");
		colour_change ();
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


