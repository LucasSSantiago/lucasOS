#ifndef LIB_KSTRING_H
#define LIB_KSTRING_H

#include <stddef.h>

size_t kstrlen(const char* str);
int kstrcmp(const char *a, const char *b);
void kstrncpy(char *dest, const char *src, size_t max);

#endif