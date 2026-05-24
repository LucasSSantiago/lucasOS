#include <drivers/terminal.h>
#include <drivers/keyboard.h>
#include <kernel/kmain.h>
#include <kernel/shell.h>
#include <drivers/serial.h>

void kernel_main(void) {
    serial_init();
    serial_write_string("[lucasOS] serial initialized\n");

    terminal_initialize();

    serial_write_string("[lucasOS] terminal initialized\n");

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