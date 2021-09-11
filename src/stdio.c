#include <stdint.h>
#include <stddef.h>
#include <vga.h>
#include <stdio.h>

void putchar(char c) {
	switch (c) {
		case '\n':
			curs_row++;
			curs_col = CURS_MIN;
			break;
		case '\t':
			for (char i = 0; i < 4; i++)
				putchar(' ');
			break;
		default:
			vga[curs_row * MAX_COLS + curs_col] = vga_entry(c);
			curs_col++;
			break;
	}
	
	if (curs_col >= MAX_COLS) {
		curs_row++;
		curs_col = CURS_MIN;
	}
	if (curs_row >= MAX_ROWS - 1) {
		vga_scroll();
		curs_row--;
		curs_col = CURS_MIN;
	}
}


void puts(char * str) {
	for (char * c = str; *c; c++)
		putchar(*c);
	putchar('\n');
}

