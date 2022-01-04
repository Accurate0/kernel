
ASM=nasm
ASMFLAGS=-felf32 -g
ASM_FILES=$(wildcard *.s)
OBJ=${ASM_FILES:.s=.o}

all: $(OBJ) $(ASM_FILES)

%.o : %.s
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f $(OBJ)
