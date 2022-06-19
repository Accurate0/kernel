LIBC_PATH=../libc
RUST_PATH=./target/i686/release

CC=i686-elf-gcc
CFLAGS=-Wall -std=c99 -Wextra -ffreestanding -ggdb -mgeneral-regs-only
CFLAGS+=-Iinclude -I$(LIBC_PATH)/include -I$(LIBC_PATH)/ext
LDFLAGS=-nostdlib -lgcc

SOURCES=$(shell find . -type f -name '*.c')
HEADERS=$(shell find ./include -type f -name '*.h')
OBJ=${SOURCES:.c=.o}

RUST_SRC=$(wildcard src/*.rs)
RUST_LIB=$(RUST_PATH)/libkernel.a

LIBC=$(LIBC_PATH)/libc.a
LIBC_FILES=$(wildcard $(LIBC_PATH)/*.c) $(wildcard $(LIBC_PATH)/include/libc/*.h)

ASM=$(wildcard asm/*.s)
ASSEMBLY_OBJ=${ASM:.s=.o}

TARGET=skernel

$(TARGET): $(ASSEMBLY_OBJ) $(OBJ) $(HEADERS) $(LIBC) $(RUST_LIB)
	$(CC) -T linker.ld -o $(TARGET) $(CFLAGS) $(ASSEMBLY_OBJ) $(OBJ) $(LIBC) $(RUST_LIB) $(LDFLAGS)

$(OBJ) : $(SOURCES) $(HEADERS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(RUST_LIB): $(RUST_SRC)
	cargo build --release

$(LIBC): $(LIBC_FILES)
	$(MAKE) -C $(LIBC_PATH)

$(ASSEMBLY_OBJ): $(ASM)
	$(MAKE) -C asm

clean:
	rm -rf $(OBJ) $(TARGET)
	$(MAKE) -C asm clean
	cargo clean
