#include "kernel.h"
#include "gdt.h"
/**

|** VGA TEXT MODE 80x25 **|

16 bit video buffer elements

character's ASCII code: 8-bits
foreground-color: 4-bits
background-color: 4-bits
_____________________________________________________________________________
| background-color | foreground-color | character's ASCII Code to be printed |
15_______________12_11_______________8_7____________________________________0

-pointer for video buffer array
|---uint16* vga_buffer;
-video buffer array index
|---uint32 vga_index;

|** counter for new lines **|
|---static uint32 new_line_count =1;

**/
//
uint16 vga_entry(uint8 ch,uint8 fore_color,uint8 back_color)
{
	//psuedo ax-register
	uint16 ax=0;
	
	//lower and higher bits of ax-register
	uint8 ah = 0,al=0;
	
	//background-color to 4-7 bits
	ah=back_color;
	ah <<= 4;
	
	//adding foregroun-color to 0-3 bits
	ah  |= fore_color;
	ax = ah;
	
	//ax is shifted to 8-bits to the left so that we can put character's ASCII code in lower 8-bits
	ax <<= 8;
	al = ch;
	
	//adding character's ASCII code by oring it
	ax |= al;
	
	//returning 16-bit ax content;
	return ax;
}

//clearing VGA buffer array
void clear_vga_buffer(uint16 **buffer,uint8 fore_Color,uint8 back_color)
{
	uint32 i;
	for(i=0;i < VGA_BUF_SIZE;i++)
	{
		(*buffer)[i] = vga_entry(NULL,fore_Color,back_color);
	}
	new_line_count=1;
	vga_index = 0;
}

//initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  global_fore_color = fore_color;
  global_back_color = back_color;
}

/*
increase vga_index by width of row(80)
*/
void print_new_line()
{
  if(new_line_count >= 55){
    new_line_count = 0;
    clear_vga_buffer(&vga_buffer, global_fore_color, global_back_color);
  }
  vga_index = 80*new_line_count;
  new_line_count++;
}

//assign ascii character to video buffer
void print_char(char ch)
{
  vga_buffer[vga_index] = vga_entry(ch, global_fore_color, global_back_color);
  vga_index++;
}


uint32 str_len(const char* str)
{
  uint32 length = 0;
  while(str[length])
    length++;
  return length;
}

uint32 digit_count(int num)
{
  uint32 count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

//print string by calling print_char
void print_string(char *str)
{
  uint32 index = 0;
  while(str[index]){
    print_char(str[index]);
    index++;
  }
}

//print int by converting it into string
//& then printing string
void print_int(int num)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  print_string(str_num);
}

void kernel_entry()
{
 	init_gdt();
 	init_vga(WHITE, BLACK);

	print_string("Hello World!");
	print_new_line();

}
