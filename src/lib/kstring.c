#include <lib/kstring.h>

size_t kstrlen(const char* str) {
    size_t len = 0;

    while (str[len]) {
        len++;
    }

    return len;
}

int kstrcmp(const char *a, const char *b) {
    size_t i = 0;

    while(a[i] && b[i]) {
        if (a[i] != b[i]) {
            return (unsigned char)a[i] - (unsigned char)b[i];
        }
        i++;
    }

    return (unsigned char)a[i] - (unsigned char)b[i];
}

void kstrncpy(char *dest, const char *src, size_t max) {
    if (max == 0) {
        return;
    }

    size_t i = 0;

    while (i < max - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}