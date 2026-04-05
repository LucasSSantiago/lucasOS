#include <drivers/terminal.h>
#include <kernel/kmain.h>

void kernel_main(void) {
    terminal_initialize();
    terminal_writestring("Hello, kernel World!");
}