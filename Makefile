CC = i686-elf-gcc
AS = i686-elf-as
LD = i686-elf-ld
GRUBMKRESCUE = grub-mkrescue
QEMU = qemu-system-i386


CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

SOURCES = boot.s kernel.c
OBJS = boot.o kernel.o
ISO = myos.iso
BIN = myos.bin

all: $(ISO)

boot.o: boot.s
	$(AS) $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(ISO): $(BIN) grub.cfg
	mkdir -p isodir/boot/grub
	cp $(BIN) isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/
	$(GRUBMKRESCUE) -o $(ISO) isodir

run: $(ISO)
	$(QEMU) -cdrom $(ISO)

clean:
	rm -f $(OBJS) $(BIN) $(ISO)
	rm -rf isodir

.PHONY: all clean run
