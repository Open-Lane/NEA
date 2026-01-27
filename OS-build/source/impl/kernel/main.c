#include "print.h"
char command[128] = {0};
int i = 0;

static void drain_keyboard(void) {
    while (1) {
        uint8_t status = inb(0x64);
        if ((status & 1) == 0) break;
        (void)inb(0x60);
    }
}

void command_list(){
	char *check1 = "help";
	char *check2 = "game";
	int correct1 = 1;
	int correct2 = 1;
	for (int i = 0; i < 128; i++){
		if (command[i] != check1[i]){
			correct1 = 0;
			i = 0;
			break;
		}
		if (command[i] != check2[i]){
			correct2 = 0;
			i = 0;
			break;
		}
		if (command[i] == '\0')break;
	}
	if (correct1){
		print_char('\n');
		print_str("ah so you need some help well the current coded commands are:\n");
		print_str(command);
		print_str("\n>");
	}
	if (correct2){
		tetris_start();
	}
	else{
		print_char('\n');
		print_str("we dont know that command try h, ? or help for more info\njust to let you know ");
		print_str(command);
		print_str(" is not a command we recognise");
		print_str("\n>");
	}
}


void print_scancode_loop(char letter) {
    if (letter == '\n') {
        command_list();
        i = 0;
        command[0] = '\0';
        return;
    }
    if (letter == '\b') {
        if (i > 0) {
            i--;
            command[i] = '\0';
            delete_char();
        }
        return;
    }
    print_char(letter);
    if ((size_t)i + 1 < sizeof(command) && letter != '\0') {
        command[i++] = letter;
        command[i] = '\0';
    }
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


void the_kernel(uint64_t mbi_ptr) {
	print_init(mbi_ptr);
	print_clear();
	col = row = 0;
	init_keymap();
	print_set_colour(YELLOW,BLACK);
	print_str("|------------------------------------------------------------------------------|");
	print_str("|                this is OS hit! my computer scince NEA project                |");
	print_str("|------------------------------------------------------------------------------|");
	print_str(">");
	drain_keyboard();
	read_scancodes();
}


