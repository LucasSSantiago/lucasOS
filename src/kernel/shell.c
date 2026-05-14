#include <kernel/shell.h>

#include <drivers/terminal.h>
#include <lib/kstring.h>

#define SHELL_COMMAND_BUFFER_SIZE 128
#define SHELL_HISTORY_SIZE 8

struct shell_command {
    const char *name;
    const char *description;
    void (*handler)(const char *args);
};

static char command_buffer[SHELL_COMMAND_BUFFER_SIZE];
static int command_length = 0;

static char command_history[SHELL_HISTORY_SIZE][SHELL_COMMAND_BUFFER_SIZE];
static size_t history_count = 0;

static void print_prompt(void);
static void process_command(char *command);
static void add_to_history(const char *command);

static void command_help(const char *args);
static void command_clear(const char *args);
static void command_setcolor(const char *args);
static void command_history_handler(const char *args);

static struct shell_command commands[] = {
    {"help", "Show available commands", command_help},
    {"clear", "Clear the screen", command_clear},
    {"setcolor", "change text color. Example: setcolor red", command_setcolor},
    {"history", "Show command history", command_history_handler},
    {0,0,0}
};

void shell_initialize(void) {
    command_length = 0;
    command_buffer[0] = 0;

    print_prompt();
}

void shell_handle_input_char(char c) {
    if (c == '\b') {
        if (command_length > 0) {
            (command_length)--;
            command_buffer[command_length] = '\0';
            terminal_putchar('\b');
        }
        return;
    }

        if (c == '\n') {
        command_buffer[command_length] = '\0';
        terminal_putchar('\n');

        process_command(command_buffer);

        command_length = 0;
        command_buffer[0] = '\0';

        print_prompt();
        return;
    }

    if (command_length < SHELL_COMMAND_BUFFER_SIZE - 1) {
        command_buffer[command_length] = c;
        (command_length)++;
        command_buffer[command_length] = '\0';

        terminal_putchar(c);
    }
}

static void print_prompt(void) {
    terminal_writestring("> ");
}

static void process_command(char *command) {
    if (command[0] == '\0') {
        return;
    }

    add_to_history(command);

    char *command_name = command;
    char *args = command;

    while (*args != '\0' && *args != ' ') {
        args++;
    }

    if (*args == ' ') {
        *args = '\0';
        args++;
        
        while (*args == ' ') {
        args++;
        }
    } else {
        args = "";
    }

    for (size_t i = 0; commands[i].name != 0; i++) {
        if (kstrcmp(command_name, commands[i].name) == 0) {
            commands[i].handler(args);
            return;
        }
    }

    terminal_writestring("Unknown command: ");
    terminal_writestring(command_name);
    terminal_putchar('\n');    
}

static void add_to_history(const char *command) {
    if (command[0] == '\0') {
        return;
    }

    size_t index;

    if (history_count < SHELL_HISTORY_SIZE) {
        index = history_count;
        history_count++;
    } else {
        for (size_t i = 1; i < SHELL_HISTORY_SIZE; i++) {
            kstrncpy(
                command_history[i - 1],
                command_history[i],
                SHELL_COMMAND_BUFFER_SIZE);

        }

        index = SHELL_HISTORY_SIZE - 1;
    }

    kstrncpy(command_history[index], command, SHELL_COMMAND_BUFFER_SIZE);
}

static void command_help(const char *args) {
    (void) args;

    terminal_writestring("Available commands:\n");

    for (size_t i = 0; commands[i].name != 0; i++) {
        terminal_writestring("  ");
        terminal_writestring(commands[i].name);
        terminal_writestring(" - ");
        terminal_writestring(commands[i].description);
        terminal_putchar('\n');
    }
}

static void command_clear(const char *args) {
    (void) args;

    terminal_clear();
}

static void command_setcolor(const char *args) {
    enum vga_color color;

    if (args[0] == '\0') {
        terminal_writestring("Usage: setcolor <color>\n");
        terminal_writestring("Example: setcolor green\n");
        return;
    }

    if (terminal_parse_color(args, &color)) {
        terminal_setcolor(terminal_make_color(color, VGA_COLOR_BLACK));
        terminal_writestring("Color changed successfully\n");
    } else {
        terminal_writestring("Unknown color: ");
        terminal_writestring(args);
        terminal_putchar('\n');
    }
}

static void command_history_handler(const char *args) {
    (void) args;

    if (history_count == 0) {
        terminal_writestring("History is empty.\n");
        return;
    }

    for (size_t i = 0; i < history_count; i++) {
        terminal_writestring(" ");

        if (i < 9) {
            terminal_putchar('1' + i); 
        } else {
            terminal_putchar('?');
        }

        terminal_writestring(": ");
        terminal_writestring(command_history[i]);
        terminal_putchar('\n');
    }
}