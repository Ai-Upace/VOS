ASM      := nasm
DD       := dd
GCC      := i686-elf-gcc
LD       := i686-elf-ld
OBJCOPY  := i686-elf-objcopy
CFLAGS   := -ffreestanding -nostdlib -I$(INC_DIR) -Wall -Wextra
LDFLAGS  := -Ttext 0x10000 -nostdlib
LDFLAGS_grub  := -Ttext 0x1000000 -nostdlib

BUILD_DIR := build
ASM_DIR   := src/assembly
INC_DIR   := include
SRC_DIR   := src/kernels

all: os.img

os.img: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel_mbr.bin

	$(DD) if=/dev/zero of=$@ bs=512 count=2880

	$(DD) if=$(BUILD_DIR)/boot.bin of=$@ bs=512 count=1 conv=notrunc

	$(DD) if=$(BUILD_DIR)/kernel_mbr.bin of=$@ bs=512 seek=1 conv=notrunc

$(BUILD_DIR)/boot.bin: $(ASM_DIR)/BOOT.ASM | $(BUILD_DIR)

	$(ASM) -f bin $< -o $@

$(BUILD_DIR)/kernel_mbr.bin: $(ASM_DIR)/kernel_entry.asm $(SRC_DIR)/kernel.c | $(BUILD_DIR)

	$(ASM) -f elf32 $(ASM_DIR)/kernel_entry.asm -o $(BUILD_DIR)/kernel_entry.o
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o

	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/kernel.elf $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o
	$(OBJCOPY) -O binary $(BUILD_DIR)/kernel.elf $@

$(BUILD_DIR)/kernel_grub.bin: $(ASM_DIR)/kernel_entry.asm $(SRC_DIR)/kernel.c | $(BUILD_DIR)

	$(ASM) -f elf32 $(ASM_DIR)/kernel_entry.asm -o $(BUILD_DIR)/kernel_entry.o
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o

	$(LD) $(LDFLAGS_grub) -o $(BUILD_DIR)/kernel.elf $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o

# 单独生成内核镜像
mbr: $(BUILD_DIR)/kernel_mbr.bin

grub: $(BUILD_DIR)/kernel_grub.bin

$(BUILD_DIR):

	@mkdir -p $@

run: os.img
	qemu-system-i386 -fda $<

clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(BUILD_DIR)" rd /s /q "$(BUILD_DIR)"
	@if exist "os.img" del /q "os.img"
else
	@rm -rf $(BUILD_DIR) os.img
endif

.PHONY: all run clean