#ifndef DRIVERS_SERIAL_H
#define DRIVERS_SERIAL_H

#include <stdint.h>

int serial_init(void);
    
void serial_write_char(char c);
void serial_write_string(const char *s);

int serial_received(void);
int serial_try_read_char(char *out);

#endif