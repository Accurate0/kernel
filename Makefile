CC=i686-elf-gcc
CFLAGS=-Wall -std=c99 -Wextra -ffreestanding -ggdb -mgeneral-regs-only
CFLAGS+=-Ikernel/include -Ilibc/include -Iext/include
LDFLAGS=-nostdlib
SOURCES=$(wildcard kernel/*.c libc/*.c)
HEADERS=$(wildcard kernel/include/kernel*.h libc/include/libc/*.h)
OBJ=${SOURCES:.c=.o}

ASM=$(wildcard kernel/asm/*.s)
ASSEMBLY_OBJ=${ASM:.s=.o}

TARGET=skernel

run: $(TARGET)
	qemu-system-i386 -serial stdio -kernel $(TARGET) -enable-kvm -machine q35 -device intel-iommu -vga std

$(TARGET): $(ASSEMBLY_OBJ) $(OBJ) $(HEADERS)
	$(CC) -T kernel/linker.ld -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(ASSEMBLY_OBJ) $(OBJ) -lgcc

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(ASSEMBLY_OBJ): $(ASM)
	$(MAKE) -C kernel/asm

clean:
	rm -rf $(OBJ) $(ASSEMBLY_OBJ) $(TARGET)
