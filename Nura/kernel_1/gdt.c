#include "gdt.h"

GDT gdt_entries[3];
GDT_PTR gdt_first;

extern void load_gdt(GDT*);

void  set_gdt_segment(uint8 type,uint16 limit,uint16 base_l,uint8 middle,uint8 access,uint8 gran,uint8 base_h)
{
	gdt_entries[type].segment_limit = limit;
 	gdt_entries[type].base_low = base_l;
 	gdt_entries[type].base_middle = middle;
 	gdt_entries[type].access = access;
 	gdt_entries[type].granularity = gran;
 	gdt_entries[type].base_high = base_h;
}
void init_gdt()
{
	set_gdt_segment(NULL_SEGMENT,0,0,0,0,0,0);
	set_gdt_segment(CODE_SEGMENT,0xffff,0,0,0x9a,0b11001111,0);
	set_gdt_segment(DATA_SEGMENT,0xffff,0,0,0x92,0b11001111,0);

	gdt_first.limit_size = sizeof(gdt_entries)-1;
	gdt_first.base_address = (GDT*)&gdt_entries;
	load_gdt((GDT*)&gdt_first);
}
