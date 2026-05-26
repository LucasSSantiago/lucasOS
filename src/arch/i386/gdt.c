#include <stdint.h>
#include <arch/i386/gdt.h>

#define GDT_ENTRIES 3

#define GDT_ACCESS_PRESENT      0X80
#define GDT_ACCESS_RING0        0X00
#define GDT_ACCESS_DESCRIPTOR   0X10
#define GDT_ACCESS_EXECUTABLE   0X08
#define GDT_ACCESS_READ_WRITE   0X02


#define GDT_FLAGS_GRANULARITY_4K 0X80
#define GDT_FLAGS_32_BIT         0X40

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

static struct gdt_entry gdt[GDT_ENTRIES];
static struct gdt_ptr gdt_descriptor;

extern void gdt_flush(uint32_t gdt_ptr_address);

static void gdt_set_entry (
    int index,
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t flags
) {
    gdt[index].base_low = base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = limit & 0xFFFF;
    gdt[index].granularity = (limit >> 16) & 0x0F;
    gdt[index].granularity |= flags & 0xF0;

    gdt[index].access = access;
}

void gdt_initialize(void) {
    gdt_descriptor.limit = sizeof(gdt) -1;
    gdt_descriptor.base = (uint32_t)&gdt;

    gdt_set_entry(0, 0, 0, 0, 0);

    gdt_set_entry(
        1,
        0x00000000,
        0xFFFFFFFF,
        GDT_ACCESS_PRESENT |
        GDT_ACCESS_RING0 |
        GDT_ACCESS_DESCRIPTOR |
        GDT_ACCESS_EXECUTABLE |
        GDT_ACCESS_READ_WRITE,
        GDT_FLAGS_GRANULARITY_4K |
        GDT_FLAGS_32_BIT
    );

    gdt_set_entry(
        2,
        0x00000000,
        0xFFFFFFFF,
        GDT_ACCESS_PRESENT |
        GDT_ACCESS_RING0 |
        GDT_ACCESS_DESCRIPTOR |
        GDT_ACCESS_READ_WRITE,
        GDT_FLAGS_GRANULARITY_4K |
        GDT_FLAGS_32_BIT
    );

    gdt_flush((uint32_t)&gdt_descriptor);
}