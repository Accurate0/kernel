CC=i686-elf-gcc
CFLAGS=-Wall -std=c99 -Wextra -ffreestanding -ggdb
CFLAGS+=-Iinclude

SOURCES=$(wildcard *.c)
HEADERS=$(wildcard include/libc/*.h)

EXT_SOURCES=$(shell find ext -type f -name '*.c')

OBJ=${SOURCES:.c=.o}

EXT_OBJ=${EXT_SOURCES:.c=.o}

TARGET=libc.a

$(TARGET): $(OBJ) $(HEADERS) $(EXT_OBJ)
	$(AR) rcs $(TARGET) $(OBJ) $(EXT_OBJ)

$(EXT_OBJ) : $(EXT_SOURCES)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(TARGET) $(EXT_OBJ)
