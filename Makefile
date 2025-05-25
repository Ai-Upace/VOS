ASM= nasm
DD = dd
gcc= i686-elf-gcc
ld = i686-elf-ld
not=-ffreestanding -nostdlib
objcopy = i686-elf-objcopy

all: os.img

os.img: boot.bin kernel.bin
	$(DD) if=/dev/zero of=os.img bs=512 count=2880
	$(DD) if=BIN/boot.bin of=os.img bs=512 count=1 conv=notrunc
	$(DD) if=BIN/kernel.bin of=os.img bs=512 seek=1 conv=notrunc

boot.bin: SOURCE/BOOT.ASM
	$(ASM) -f bin SOURCE/BOOT.ASM -o BIN/boot.bin

kernel.bin: SOURCE/kernel_entry.asm SOURCE/kernel.c
	$(ASM) -f elf32 SOURCE/kernel_entry.asm -o BIN/kernel_entry.o
	$(gcc) $(not) -c SOURCE/kernel.c -o BIN/kernel.o
	$(ld) -Ttext 0x10000 -o BIN/kernel.elf BIN/kernel_entry.o BIN/kernel.o
	$(objcopy) -O binary BIN/kernel.elf BIN/kernel.bin

run: os.img
	qemu-system-i386 -fda os.img

clean:
# Windows Vistion
	del /Q BIN\*.bin
	del /Q BIN\*.o