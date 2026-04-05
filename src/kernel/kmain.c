#include <drivers/terminal.h>
#include <kernel/kmain.h>

void kernel_main(void) {
    terminal_initialize();
    terminal_writestring("Terminal initialized\n");
    terminal_setcolor(terminal_make_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
    terminal_writestring("Color support enabled\n");
}