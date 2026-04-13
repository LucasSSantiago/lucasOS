#include <drivers/terminal.h>
#include <drivers/keyboard.h>>
#include <kernel/kmain.h>

void kernel_main(void) {
    terminal_initialize();
    terminal_setcolor(terminal_make_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));

    terminal_writestring("LucasOS\n");
    terminal_writestring("32-bit x86 kernel\n");
    terminal_writestring("------------------------------\n");
    terminal_writestring("Keyboard test ready.\n");;
    terminal_writestring("> ");

    while (1) {
        char c = keyboard_getchar();

        if (c) {
            terminal_putchar(c);
        }
    }
}