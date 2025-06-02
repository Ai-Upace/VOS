ASM		:= nasm
DD		:= dd
CC		:= i686-elf-gcc
CFLAGS	:= -ffreestanding -Wall -Isrc/include -Wextra -nostdlib
SRC_DIR := src/drivers/ps2/keyboard.c src/kernels/kernel.c src/kernels/io.c src/user/shell/shell.c

all: build/kernel.bin

build/kernel.bin: $(SRC_DIR)
	@mkdir -p build
	i686-elf-gcc $(CFLAGS) -o build/kernel.o src/drivers/ps2/keyboard.c src/kernels/kernel.c src/kernels/io.c src/user/shell/shell.c

clean:
	rm -rf build