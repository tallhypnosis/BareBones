#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_shiftUp()
{
  int i;
  for(i=0; i<VGA_HEIGHT-1; i++) {
    for(int j=0; j<VGA_WIDTH; j++) {
      terminal_buffer[i*VGA_WIDTH + j] = terminal_buffer[(i+1)*VGA_WIDTH + j];
    } 
  }


  for(int j=0; j<VGA_WIDTH; j++) {
    terminal_buffer[i*VGA_WIDTH + j] = vga_entry(' ', terminal_color); 
 
  }

} 
void terminal_newline ()
{
  ++terminal_row;
  terminal_column = 0;
}

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  if(c == '\n') {
    terminal_newline();
  }
	if (++terminal_column == VGA_WIDTH) {
		terminal_shiftUp();
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!\n");
  terminal_writestring(
"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor "
"incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis "
"nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. "
"Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore "
"eu fugiat nulla pariatur.\n"
"\n"
"Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia "
"deserunt mollit anim id est laborum. Sed ut perspiciatis unde omnis iste natus "
"error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, "
"eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae "
"dicta sunt explicabo.\n"
"\n"
"Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, "
"sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. "
"Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, "
"adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et "
"dolore magnam aliquam quaerat voluptatem.\n"
"\n"
"Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit "
"laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum "
"iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae "
"consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?\n"
"\n"
"At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis "
"praesentium voluptatum deleniti atque corrupti quos dolores et quas molestias "
"excepturi sint occaecati cupiditate non provident, similique sunt in culpa "
"qui officia deserunt mollitia animi.\n"
);

}
