all: myos.iso

myos.iso: myos.bin
	grub-mkrescue isodir -o myos.iso

myos.bin: boot.o kernel.o
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	mkdir -p isodir/boot/grub 2> /dev/null
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg

kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: boot.s
	i686-elf-as boot.s -o boot.o

clean:
	rm -f *.o
	rm -f myos.bin myos.iso
	rm -f isodir/boot/myos.bin isodir/boot/grub/grub.cfg

