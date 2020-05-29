#ifndef PAGE_H
#define PAGE_H

#include<stdint.h>

#include"record.h"
#include"schema.h"

typedef struct Page
{
	Record *first, *last;
	uint32_t curr_sz;
} Page;

Page *page_init();
uint8_t page_add_rec(Page *, int8_t *, Schema *);
// Expects an empty but allocated buffer of PAGE_SIZE
void page_to_bin(Page *, int8_t **, Schema *);
void page_deinit(Page *);

#endif
