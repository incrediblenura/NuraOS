#ifndef GDT_H
#define GDT_H
#include "types.h"

#define NULL_SEGMENT 0
#define CODE_SEGMENT 1
#define DATA_SEGMENT 2

typedef struct global_descriptor_table
{
	uint16 segment_limit;
	uint16 base_low;
	uint8 base_middle;
	uint8 access;
	uint8 granularity;
	uint8 base_high;
}__attribute__((packed)) GDT;

typedef struct global_descriptor_table_pointer
{
	uint16 limit_size;
	GDT* base_address;
}__attribute__((packed)) GDT_PTR;

extern GDT gdt_entries[3];
extern GDT_PTR gdt_first;

extern void init_gdt();

#endif
