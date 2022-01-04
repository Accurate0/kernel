LIBC_PATH=../libc

CC=i686-elf-gcc
CFLAGS=-Wall -std=c99 -Wextra -ffreestanding -ggdb -mgeneral-regs-only
CFLAGS+=-Iinclude -I$(LIBC_PATH)/include
LDFLAGS=-nostdlib

SOURCES=$(wildcard *.c)
HEADERS=$(wildcard include/kernel*.h)
OBJ=${SOURCES:.c=.o}

LIBC=$(LIBC_PATH)/libc.a

ASM=$(wildcard asm/*.s)
ASSEMBLY_OBJ=${ASM:.s=.o}

TARGET=skernel

$(TARGET): $(ASSEMBLY_OBJ) $(OBJ) $(HEADERS) $(LIBC)
	$(CC) -T linker.ld -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(ASSEMBLY_OBJ) $(OBJ) $(LIBC) -lgcc

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBC):
	$(MAKE) -C $(LIBC_PATH)

$(ASSEMBLY_OBJ): $(ASM)
	$(MAKE) -C asm

clean:
	rm -rf $(OBJ) $(TARGET)
	$(MAKE) -C asm clean
