CC=i686-elf-gcc
CFLAGS=-Wall -std=c99 -Wextra -ffreestanding -O2
CFLAGS+=-Ikernel/include -Ilibc/include -Iext/include
LDFLAGS=-nostdlib
SOURCES=$(wildcard kernel/*.c libc/*.c ext/*.c)
OBJ=${SOURCES:.c=.o}

ASM=$(wildcard kernel/asm/*.asm)
ASSEMBLY_OBJ=${ASM:.asm=.o}

TARGET=skernel

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET) -enable-kvm -machine q35 -device intel-iommu -vga std

$(TARGET): $(ASSEMBLY_OBJ) $(OBJ)
	$(CC) -T kernel/linker.ld -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(ASSEMBLY_OBJ) $(OBJ) -lgcc

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(ASSEMBLY_OBJ):
	$(MAKE) -C kernel/asm

clean:
	rm -rf $(OBJ) $(ASSEMBLY_OBJ) $(TARGET)
