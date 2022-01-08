LIBC_PATH=../libc

CC=i686-elf-gcc
CFLAGS=-Wall -std=c99 -Wextra -ffreestanding -ggdb -mgeneral-regs-only
CFLAGS+=-Iinclude -I$(LIBC_PATH)/include -I$(LIBC_PATH)/ext
LDFLAGS=-nostdlib -lgcc

SOURCES=$(shell find . -type f -name '*.c')
HEADERS=$(shell find ./include -type f -name '*.h')
OBJ=${SOURCES:.c=.o}

LIBC=$(LIBC_PATH)/libc.a
LIBC_FILES=$(wildcard $(LIBC_PATH)/*.c) $(wildcard $(LIBC_PATH)/include/libc/*.h)

ASM=$(wildcard asm/*.s)
ASSEMBLY_OBJ=${ASM:.s=.o}

TARGET=skernel

$(TARGET): $(ASSEMBLY_OBJ) $(OBJ) $(HEADERS) $(LIBC)
	$(CC) -T linker.ld -o $(TARGET) $(CFLAGS) $(ASSEMBLY_OBJ) $(OBJ) $(LIBC) $(LDFLAGS)

$(OBJ) : $(SOURCES) $(HEADERS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBC): $(LIBC_FILES)
	$(MAKE) -C $(LIBC_PATH)

$(ASSEMBLY_OBJ): $(ASM)
	$(MAKE) -C asm

clean:
	rm -rf $(OBJ) $(TARGET)
	$(MAKE) -C asm clean
