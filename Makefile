CC=i686-elf-gcc
CFLAGS=-Wall -std=c99 -Wextra -ffreestanding -O2
CFLAGS+=-Ikernel/include -Ilibc/include -Iext/include
LDFLAGS=-nostdlib
SOURCES=$(wildcard kernel/*.c libc/*.c ext/*.c)
OBJ=${SOURCES:.c=.o}

ASM=nasm
ASMFLAGS=-felf32
BOOT=$(wildcard kernel/asm/*.asm)
BOOTOBJ=${BOOT:.asm=.o}

TARGET=skernel

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET) -enable-kvm -machine q35 -device intel-iommu -vga std

$(TARGET): $(BOOTOBJ) $(OBJ)
	$(CC) -T kernel/linker.ld -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(BOOTOBJ) $(OBJ) -lgcc

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

kernel/asm/boot.o: kernel/asm/boot.asm
	$(ASM) $(ASMFLAGS) $< -o $@

kernel/asm/gdt.o: kernel/asm/gdt.asm
	$(ASM) $(ASMFLAGS) $< -o $@

kernel/asm/isr.o: kernel/asm/isr.asm
	$(ASM) $(ASMFLAGS) $< -o $@

.asm.o:
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf $(OBJ) $(BOOTOBJ) $(TARGET)
