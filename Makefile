ASM		:= nasm
DD		:= dd
CC		:= i686-elf-gcc
LD		:= i686-elf-ld

SRC_DIR := src/drivers/ps2/keyboard.c src/kernels/kernel.c src/kernels/io.c src/user/shell/shell.c
INC_DIR := include

CFLAGS	:= -ffreestanding -Wall -I$(INC_DIR) -Wextra -nostdlib
LDFLAGS := -Ttext 0x10000 -nostdlib

all: build/kernel.elf

build/kernel_entry.o: src/assembly/kernel_entry.asm
	$(ASM) -f elf32 src/assembly/kernel_entry.asm -o build/kernel_entry.o

build/kernel.o: $(SRC_DIR)
	i686-elf-gcc $(CFLAGS) -o build/kernel.o src/drivers/ps2/keyboard.c src/kernels/kernel.c src/kernels/io.c src/user/shell/shell.c

build/kernel.elf: build/kernel_entry.o build/kernel.o
	$(LD) $(LDFLAGS) -o build/kernel.elf build/kernel_entry.o build/kernel.o

clean:
	rm -rf build