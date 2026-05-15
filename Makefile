CC = i686-elf-gcc
AS = i686-elf-as

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
ASFLAGS =
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

TARGET = lucasOS
ISO = $(TARGET).iso

C_SOURCES = \
	src/kernel/kmain.c \
	src/kernel/shell.c \
	src/drivers/terminal.c \
	src/drivers/serial.c \
	src/drivers/keyboard.c \
	src/lib/kstring.c
	

ASM_SOURCES = \
	src/arch/i386/boot/boot.s

C_OBJECTS = $(C_SOURCES:.c=.o)
ASM_OBJECTS = $(ASM_SOURCES:.s=.o)
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

src/kernel/%.o: src/kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/drivers/%.o: src/drivers/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/lib/%.o: src/lib/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/arch/i386/boot/%.o: src/arch/i386/boot/%.s
	$(AS) $(ASFLAGS) $< -o $@

iso: $(TARGET)
	mkdir -p isodir/boot/grub
	cp $(TARGET) isodir/boot/kernel.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) isodir

run: iso
	qemu-system-i386 -cdrom $(ISO) -serial mon:stdio

run-log: iso
	qemu-system-i386 -cdrom $(ISO) -serial file:serial.log

clean:
	rm -rf $(OBJECTS) $(TARGET) $(ISO) isodir serial.log