
ASM=nasm
ASMFLAGS=-felf32
ASM_FILES=$(wildcard *.asm)
OBJ=${ASM_FILES:.asm=.o}

all: $(OBJ)

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f $(OBJ)
