CC=i686-elf-gcc
CXX=i686-elf-g++

CFLAGS=-Wall -std=c99 -Wextra -ffreestanding -O2
CFLAGS+=-Ikernel/include -Ilibc/include -Iext/include

CXXFLAGS=-Wall -std=c++11 -Wextra -ffreestanding -O2 -fno-exceptions -fno-rtti
CXXFLAGS+=-Ikernel/include -Ilibc/include -Iext/include

LDFLAGS=-nostdlib

SOURCES=$(wildcard kernel/*.c libc/*.c ext/*.c)
CPP_SOURCES=$(wildcard kernel/*.cpp libc/*.cpp ext/*.cpp)

HEADERS=$(wildcard kernel/include/kernel*.h libc/include/libc/*.h ext/include/ext/*.h)
CPP_HEADERS=$(wildcard kernel/include/kernel*.hpp libc/include/libc/*.hpp ext/include/ext/*.hpp)

OBJ=${SOURCES:.c=.o}
CPP_OBJ=${CPP_SOURCES:.cpp=.o}

ASM=$(wildcard kernel/asm/*.asm)
ASSEMBLY_OBJ=${ASM:.asm=.o}

TARGET=skernel

run: $(TARGET)
	qemu-system-i386 -serial stdio -kernel $(TARGET) -enable-kvm -machine q35 -device intel-iommu -vga std

$(TARGET): $(ASSEMBLY_OBJ) $(OBJ) $(HEADERS) $(CPP_HEADERS) $(CPP_OBJ)
	$(CC) -T kernel/linker.ld -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(ASSEMBLY_OBJ) $(OBJ) $(CPP_OBJ) -lgcc

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(ASSEMBLY_OBJ):
	$(MAKE) -C kernel/asm

clean:
	rm -rf $(OBJ) $(ASSEMBLY_OBJ) $(TARGET)
