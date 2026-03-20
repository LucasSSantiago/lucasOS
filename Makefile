CC = i686-elf-gcc
AS = i686-elf-as

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

SRC = src/kernel.c src/boot.s
OBJ = kernel.o boot.o
TARGET = myos

all: $(TARGET)

kernel.o: src/kernel.c
	$(CC) -c $< -o $@ $(CFLAGS)

boot.o: src/boot.s
	$(AS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJ)


iso: $(TARGET)
	mkdir -p isodir/boot/grub
	cp $(TARGET) isodir/boot/kernel.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir


run: iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -rf *.o $(TARGET) myos.iso isodir