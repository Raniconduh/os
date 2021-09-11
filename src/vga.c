#include <vga.h>

uint16_t * vga = (uint16_t*)0xB8000;

uint8_t curs_row = CURS_MIN;
uint8_t curs_col = CURS_MIN;

void vga_scroll(void) {
	for (int row = CURS_MIN + 1; row < MAX_ROWS; row++)
		for (int col = CURS_MIN; col < MAX_COLS; col++) {
			vga[(row - 1) * MAX_COLS + col] = vga_entry(vga[row * MAX_COLS + col]);
		}

	// clear last line
	for (int col = CURS_MIN; col < MAX_COLS; col++)
		vga[(MAX_ROWS - 1) * MAX_COLS + col] = vga_entry(' ');
}

