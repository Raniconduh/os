all: myos.iso

myos.iso: myos.bin
	grub-mkrescue isodir -o myos.iso

myos.bin: boot.o a.o
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib *.o -lgcc
	mkdir -p isodir/boot/grub 2> /dev/null
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg

a.o:
	i686-elf-gcc -c src/*.c -Iinclude -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: src/boot.s
	i686-elf-as src/boot.s -o boot.o

clean:
	rm -f *.o
	rm -f myos.bin myos.iso
	rm -f isodir/boot/myos.bin isodir/boot/grub/grub.cfg

