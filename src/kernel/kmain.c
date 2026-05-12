#include <drivers/terminal.h>
#include <drivers/keyboard.h>
#include <kernel/kmain.h>
#include <kernel/shell.h>

void kernel_main(void) {
    shell_initialize();
    terminal_setcolor(terminal_make_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));

    terminal_writestring("LucasOS\n");
    terminal_writestring("32-bit x86 kernel\n");
    terminal_writestring("------------------------------\n");

    shell_initialize();

    while (1) {
        char c = keyboard_getchar();

        if (c != 0) {
            shell_handle_input_char(c);
        }
    }
}