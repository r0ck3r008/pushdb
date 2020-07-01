#ifndef PAGE_H
#define PAGE_H

#include"record.h"
#include"schema.h"
#include"defs.h"

typedef struct Page
{
	Record *head, *tail;
	Schema *sch;
	int nrecs;
	struct Page *next;
} Page;

Page *page_init(Schema *);
void page_tobin(Page *, char *);
Page *page_frombin(char *, Schema *);
int page_add_rec(Page *, char *, int);
void page_deinit(Page *);

#endif
