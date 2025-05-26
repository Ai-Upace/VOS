ASM= nasm
DD = dd
gcc= i686-elf-gcc
ld = i686-elf-ld
not=-ffreestanding -nostdlib
objcopy = i686-elf-objcopy

all: os.img

os.img: boot.bin kernel.bin
# Make floppy disk image
	$(DD) if=/dev/zero of=os.img bs=512 count=2880
# Write objects to the image
	$(DD) if=build/boot.bin of=os.img bs=512 count=1 conv=notrunc
	$(DD) if=build/kernel.bin of=os.img bs=512 seek=1 conv=notrunc

boot.bin: src/BOOT.ASM
	$(ASM) -f bin src/BOOT.ASM -o build/boot.bin

kernel.bin: src/kernel_entry.asm src/kernel.c
# Build the kernel object
	$(ASM) -f elf32 src/kernel_entry.asm -o build/kernel_entry.o
	$(gcc) $(not) -c src/kernel.c -o build/kernel.o
# Link the kernel object
	$(ld) -Ttext 0x10000 -o build/kernel.elf build/kernel_entry.o build/kernel.o
	$(objcopy) -O binary build/kernel.elf build/kernel.bin

run: os.img
	qemu-system-i386 -fda os.img

clean_W:
# Windows Vistion
	del /Q build\*.*
	del /Q os.img

clean_L:
# Linux Vistion
	rm -f build/*.bin
	rm -f build/*.o
	rm -f build/*.elf
	rm -f os.img