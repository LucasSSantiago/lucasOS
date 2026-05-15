#include <drivers/serial.h>
#include <arch/i386/io.h>

#define COM1 0x3F8

static int serial_can_transmit(void) {
    return inb(COM1 + 5) & 0x20;
}

int serial_init(void) {
    outb(COM1 + 1, 0x00);

    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);

    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);

    return 0;
}

void serial_write_char(char c) {
    if (c == '\n') {
        serial_write_char('\r');
    }

    while (!serial_can_transmit()) {
        
    }
    
   outb(COM1, (uint8_t)c);
}

void serial_write_string(const char *s) {
    if (s == 0) {
        return;
    }
    
    while(*s) {
        serial_write_char(*s++);
    }
}

int serial_received(void) {
    return inb(COM1 + 5) & 0x01;
}

int serial_try_read_char(char *out) {
    if (out == 0) {
        return 0;
    }

    if (!serial_received()) {
        return 0;
    }

    *out = (char)inb(COM1);
    return 1;
}