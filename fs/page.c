#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"defs.h"
#include"alloc.h"
#include"page.h"

Page *page_init(Schema *sch)
{
	Page *pg=fs_page_alloc();
	pg->sch=sch;

	return pg;
}

uint8_t page_add_rec(Page *pg, int8_t *rec_str)
{
	if(pg->sch->delim==NULL) {
		fprintf(stderr, "[-]PAGE: delimiter not found in schema!\n");
		return 0;
	}

	// +1 is for the delimiter
	if((pg->curr_sz + pg->sch->map->tot_len + 1) >= PAGE_SIZE) {
		fprintf(stderr, "[-]PAGE: page full!\n");
		return 0;
	}

	Record *rec=record_ser(rec_str, pg->sch);
	if(pg->first==NULL)
		pg->first=rec;
	else
		pg->last->next=rec;

	pg->last=rec;
	pg->curr_sz+=pg->sch->map->tot_len;

	return 1;
}

void page_to_bin(Page *pg, int8_t **buf)
{
	if(*buf==NULL) {
		fprintf(stderr, "[-]PAGE: Unallocated buffer placeholder!\n");
		_exit(-1);
	}

	Record *curr=pg->first;
	while(curr!=NULL) {
		sprintf(*buf, "%s%s%s", *buf, pg->sch->delim, curr->bits);
		curr=curr->next;
	}
}

void page_deinit(Page *pg)
{
	Record *curr=pg->first->next;
	while(pg->first->next!=NULL) {
		pg->first->next=curr->next;
		free(curr->bits);
		free(curr);
	}
	free(pg->first);
	free(pg);
}
