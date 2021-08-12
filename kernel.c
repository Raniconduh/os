#include <stdint.h>
#include <stddef.h>

#define MAX_COLS 80
#define MAX_ROWS 25

#define CURS_MIN 0


static inline uint16_t vga_entry(char);
void scroll(void);
void putchar(char);
void puts(char *);


// address for VGA buffer
uint16_t * vga = (uint16_t*)0xB8000;


uint8_t curs_row = CURS_MIN;
uint8_t curs_col = CURS_MIN;


// white on black
// returns 16 bit entry suitable for rendering
static inline uint16_t vga_entry(char c) {
	return c | 15 << 8;
}


// scroll the screen up
void scroll(void) {
	for (int row = CURS_MIN + 1; row < MAX_ROWS; row++)
		for (int col = CURS_MIN; col < MAX_COLS; col++) {
			vga[(row - 1) * MAX_COLS + col] = vga_entry(vga[row * MAX_COLS + col]);
		}

	// clear last line
	for (int col = CURS_MIN; col < MAX_COLS; col++)
		vga[(MAX_ROWS - 1) * MAX_COLS + col] = vga_entry(' ');
}


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
		scroll();
		curs_row--;
		curs_col = CURS_MIN;
	}
}


void puts(char * str) {
	for (char * c = str; *c; c++)
		putchar(*c);
	putchar('\n');
}

void kernel_main(void) {
	char * my_str = "abc";
	for (int i = 0; i < 30; i++) {
		for (int j = 1; j < i; j++)
			putchar(' ');
		puts(my_str);
	}
	puts("This is the end");
	puts("\thaha jk");
}
