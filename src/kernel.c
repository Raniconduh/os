#include <stdint.h>
#include <stddef.h>

#include <vga.h>
#include <stdio.h>

uint16_t * vga = (uint16_t*)0xB8000;

void kernel_main(void) {
	puts("Hello, World!");
	puts("Booting...");
	puts("Welcome!");
}
