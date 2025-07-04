ASM		:= nasm
DD		:= dd
CC		:= i686-elf-gcc
LD		:= i686-elf-ld

SRC_FILES := src/drivers/ps2/keyboard.c src/kernels/kernel.c src/kernels/io.c src/user/shell/shell.c src/user/shell/command.c
OBJ_FILES := build/keyboard.o build/kernel.o build/io.o build/shell.o build/cmd.o
INC_DIR := include

CFLAGS	:= -ffreestanding -Wall -I$(INC_DIR) -Wextra -nostdlib
LDFLAGS := -Ttext 0x10000 -nostdlib -e _start

all: build/os.img

build/boot.bin: src/assembly/BOOT.ASM
	$(ASM) -f bin $< -o $@

build/kernel_entry.o: src/assembly/kernel_entry.asm
	$(ASM) -f elf32 $< -o $@

build/keyboard.o: src/drivers/ps2/keyboard.c
	$(CC) $(CFLAGS) -c $< -o $@

build/kernel.o: src/kernels/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

build/io.o: src/kernels/io.c
	$(CC) $(CFLAGS) -c $< -o $@

build/shell.o: src/user/shell/shell.c
	$(CC) $(CFLAGS) -c $< -o $@

build/cmd.o: src/user/shell/command.c
	$(CC) $(CFLAGS) -c $< -o $@

build/kernel.elf: build/kernel_entry.o $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $@ build/kernel_entry.o $(OBJ_FILES)

build/kernel.bin: build/kernel.elf
	objcopy -O binary $< $@

build/os.img: build/boot.bin build/kernel.bin
	$(DD) if=/dev/zero of=$@ bs=512 count=2880
	$(DD) if=build/boot.bin of=$@ bs=512 count=1 conv=notrunc
	$(DD) if=build/kernel.bin of=$@ bs=512 seek=1 conv=notrunc

run: build/os.img
	qemu-system-i386 -fda build/os.img

clean:
	rm -rf build/*.o build/kernel.elf
