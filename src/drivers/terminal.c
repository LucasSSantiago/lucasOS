#include <stddef.h>
#include <stdint.h>

#include <drivers/terminal.h>
#include <lib/kstring.h>
#include <arch/i386/io.h>

int terminal_parse_color(const char *name, enum vga_color *out_color) {
    if (kstrcmp(name, "blue") == 0) {
        *out_color = VGA_COLOR_BLUE;
        return 1;
    }

    if (kstrcmp(name, "green") == 0) {
        *out_color = VGA_COLOR_GREEN;
        return 1;
    }

    if (kstrcmp(name, "cyan") == 0) {
        *out_color = VGA_COLOR_CYAN;
        return 1;
    }

    if (kstrcmp(name, "red") == 0) {
        *out_color = VGA_COLOR_RED;
        return 1;
    }

    if (kstrcmp(name, "magenta") == 0) {
        *out_color = VGA_COLOR_MAGENTA;
        return 1;
    }

    if (kstrcmp(name, "brown") == 0) {
        *out_color = VGA_COLOR_BROWN;
        return 1;
    }

    if (kstrcmp(name, "light_grey") == 0) {
        *out_color = VGA_COLOR_LIGHT_GREY;
        return 1;
    }

    if (kstrcmp(name, "white") == 0) {
        *out_color = VGA_COLOR_WHITE;
        return 1;
    }
    
    return 0;
}

uint8_t terminal_make_color(uint8_t fg, uint8_t bg) {
    return fg | bg << 4;
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer = (uint16_t*) VGA_MEMORY;

static void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}


static void terminal_update_cursor(void) {
    uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

static void terminal_scroll(void) {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t from = y * VGA_WIDTH + x;
            const size_t to = (y - 1) * VGA_WIDTH + x;
            terminal_buffer[to] = terminal_buffer[from];
        }
    }

    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_putentryat(' ', terminal_color, x, VGA_HEIGHT - 1);
    }
}

static void terminal_backspace (void) {
    if (terminal_column == 0) {
        if (terminal_row == 0) {
            return;
        }

        terminal_row--;
        terminal_column = VGA_WIDTH - 1;
    } else {
        terminal_column--;
    }

    terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
    terminal_update_cursor();
}

static void terminal_newline(void) {
    terminal_column = 0;

    if (terminal_row < VGA_HEIGHT - 1) {
        terminal_row++;
    } else {
        terminal_scroll();
    }
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_newline();
        terminal_update_cursor();
        return;
    }

    if (c == '\b') {
        terminal_backspace();
        return;
    }

    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    terminal_column++;

    if (terminal_column == VGA_WIDTH) {
        terminal_newline();
    }

    terminal_update_cursor();
}

void terminal_clear(void) {
    terminal_row = 0;
    terminal_column = 0;
    
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_putentryat(' ', terminal_color, x, y);
        }
    }

    terminal_update_cursor();
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, kstrlen(data));
}

void terminal_initialize(void) {
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_clear();
}