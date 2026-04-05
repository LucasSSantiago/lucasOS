#include <drivers/terminal.h>
#include <kernel/kmain.h>

static void terminal_write_int(int value) {
    char buffer[12];
    int i = 0;

    if (value == 0) {
        terminal_putchar('0');
        return;
    }

    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (i > 0) {
        terminal_putchar(buffer[--i]);
    }
}

void kernel_main(void) {
    terminal_initialize();
    for (int i = 0; i < 30; i++) {
        terminal_writestring("scroll test line");
        terminal_write_int(i);
        terminal_writestring("\n");
    }
    terminal_writestring("abc\ndef");
}