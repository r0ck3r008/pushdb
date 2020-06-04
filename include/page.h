#ifndef PAGE_H
#define PAGE_H

#include<stdint.h>

#include"record.h"
#include"schema.h"

typedef struct Page
{
	Record *first, *last;
	int curr_sz;
} Page;

Page *page_init();
int page_add_rec(Page *, char *, Schema *);
// Expects an empty but allocated buffer of PAGE_SIZE
void page_to_bin(Page *, char *, Schema *);
void page_deinit(Page *);

#endif
