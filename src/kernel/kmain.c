#include <drivers/terminal.h>
#include <kernel/kmain.h>

void kernel_main(void) {
    terminal_initialize();
    
    terminal_writestring("Teste 1: escrita simples\n");
    terminal_writestring("Teste 2: newline funcionando\n");

    terminal_setcolor(terminal_make_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
    terminal_writestring("Teste 3: texto verde\n");

    terminal_setcolor(terminal_make_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
    terminal_writestring("Teste 4: voltando para a cor padrao\n");

    terminal_clear();
    terminal_writestring("Teste 5: terminal_clear funcionando\n");

    for (int i = 0; i < 30; i++) {
        terminal_writestring("Teste de scroll\n");
    }
    
    terminal_setcolor(terminal_make_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
    terminal_writestring("Terminal initialized\n");
    terminal_writestring("Color support enabled");
}