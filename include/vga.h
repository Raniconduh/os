#ifndef VGA_H
#define VGA_H
#endif

#include <stdint.h>
#include <stddef.h>

#define MAX_COLS 80
#define MAX_ROWS 25

#define CURS_MIN 0

// white on black 16 bit VGA character entry
#define vga_entry(c) ((uint16_t)(c | 15 << 8))

// address for vga buffer
extern uint16_t * vga;

extern uint8_t curs_row;
extern uint8_t curs_col;

void vga_scroll(void);

