ASM		:= nasm
DD		:= dd
CC		:= i686-elf-gcc
LD		:= i686-elf-ld

SRC_FILES := src/drivers/ps2/keyboard.c src/kernels/kernel.c src/kernels/io.c src/user/shell/shell.c
OBJ_FILES := build/keyboard.o build/kernel.o build/io.o build/shell.o
INC_DIR := include

CFLAGS	:= -ffreestanding -Wall -I$(INC_DIR) -Wextra -nostdlib
LDFLAGS := -Ttext 0x10000 -nostdlib -e _start

all: build/kernel.elf

build/kernel_entry.o: src/assembly/kernel_entry.asm
	$(ASM) -f elf32 src/assembly/kernel_entry.asm -o build/kernel_entry.o

build/keyboard.o: src/drivers/ps2/keyboard.c
	$(CC) $(CFLAGS) -c $< -o $@

build/kernel.o: src/kernels/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

build/io.o: src/kernels/io.c
	$(CC) $(CFLAGS) -c $< -o $@

build/shell.o: src/user/shell/shell.c
	$(CC) $(CFLAGS) -c $< -o $@

build/kernel.elf: build/kernel_entry.o $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $@ build/kernel_entry.o $(OBJ_FILES)

clean:
	rm -rf build/*.o build/kernel.elf
