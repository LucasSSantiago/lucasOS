#include <drivers/terminal.h>
#include <drivers/keyboard.h>
#include <kernel/kmain.h>
#include <lib/kstring.h>

#define MAX_COMMAND_LENGTH 128

static void print_prompt(void) {
    terminal_writestring("> ");
}

static void process_command(const char *command) {
    if (kstrcmp(command, "help") == 0) {
        terminal_setcolor(terminal_make_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK));
        terminal_writestring("Available commands: \nhelp \nclear\n");
        terminal_setcolor(terminal_make_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
    } else if (kstrcmp(command, "clear") == 0) {
        terminal_clear();
    } else if (*command != '\0') {
        terminal_writestring("Unknown command: ");
        terminal_writestring(command);
        terminal_putchar('\n');
    }
}

static void handle_input_char(char c, char *command_buffer, size_t *command_length) {
    if (c == '\b') {
        if (*command_length > 0) {
            (*command_length)--;
            command_buffer[*command_length] = '\0';
            terminal_putchar('\b');
        }
        return;
    }

    if (c == '\n') {
        command_buffer[*command_length] = '\0';
        terminal_putchar('\n');

        process_command(command_buffer);

        *command_length = 0;
        command_buffer[0] = '\0';

        print_prompt();
        return;
    }

    if (*command_length < MAX_COMMAND_LENGTH -1) {
        command_buffer[*command_length] = c;
        (*command_length)++;
        command_buffer[*command_length] = '\0';

        terminal_putchar(c);
    }
}

void kernel_main(void) {
    char command_buffer[MAX_COMMAND_LENGTH];
    size_t command_length = 0;
    
    terminal_initialize();
    terminal_setcolor(terminal_make_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));

    command_buffer[0] = '\0';

    terminal_writestring("LucasOS\n");
    terminal_writestring("32-bit x86 kernel\n");
    terminal_writestring("------------------------------\n");
    terminal_writestring("Keyboard test ready.\n");
    print_prompt();

    while (1) {
        char c = keyboard_getchar();

        if (c != 0) {
            handle_input_char(c, command_buffer, &command_length);
        }
    }
}