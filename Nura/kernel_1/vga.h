#ifndef VGA_H
#define VGA_H
#define VGA_ADDRESS 0xB8000
#define VGA_BUF_SIZE 2200
uint16* vga_buffer;
uint32 vga_index;
uint32 new_line_count =1;
uint8 global_fore_color;
uint8 global_back_color;
enum vga_Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARK_GREY,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	BRIGHT_MAGENTA,
	YELLOW,
	WHITE
};
#define NULL 0
#endif
