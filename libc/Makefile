CC=i686-elf-gcc
CFLAGS=-Wall -std=c99 -Wextra -ffreestanding -ggdb
CFLAGS+=-Iinclude
LDFLAGS=-nostdlib

SOURCES=$(wildcard *.c)
HEADERS=$(wildcard include/libc/*.h)
OBJ=${SOURCES:.c=.o}

TARGET=libc.a

$(TARGET): $(OBJ) $(HEADERS)
	$(AR) rcs $(TARGET) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(TARGET)
