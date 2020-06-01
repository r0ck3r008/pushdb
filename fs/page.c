#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"defs.h"
#include"alloc.h"
#include"page.h"

Page *page_init()
{
	Page *pg=fs_page_alloc();

	return pg;
}

uint8_t page_add_rec(Page *pg, int8_t *rec_str, Schema *sch)
{
	if(sch->delim==NULL) {
		fprintf(stderr, "[-]PAGE: delimiter not found in schema!\n");
		return 0;
	}

	// +1 is for the delimiter
	if((pg->curr_sz + sch->map->tot_len + 1) >= PAGE_SIZE) {
		fprintf(stderr, "[-]PAGE: page full!\n");
		return 0;
	}

	Record *rec=record_ser(rec_str, sch);
	if(pg->first==NULL)
		pg->first=rec;
	else
		pg->last->next=rec;

	pg->last=rec;
	pg->curr_sz+=sch->map->tot_len;

	return 1;
}

void page_to_bin(Page *pg, int8_t **buf, Schema *sch)
{
	if(*buf==NULL) {
		fprintf(stderr, "[-]PAGE: Unallocated buffer placeholder!\n");
		_exit(-1);
	}

	Record *curr=pg->first;
	while(curr!=NULL) {
		sprintf(*buf, "%s%s%s", *buf, sch->delim, curr->bits);
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

void page_from_bin (int8_t **buf, Schema *target, Page *rec)
{
	rec->curr_sz = target->map->tot_len;
	int8_t* curPos = *buf + sizeof (int);
	Record *temp = malloc(sizeof(struct Record));
	temp = rec->first;
	while (temp!=NULL) {
		Record *temp1 = temp;
		temp = temp->next;
		free(temp);
	}
	Record *temp1 = malloc(sizeof(struct Record));
	rec->curr_sz = sizeof (int);
	int i;
	for(i=0;i<rec->curr_sz;i++) {
		int len = curPos[0];
		rec->curr_sz += len;
		memcpy (temp1->bits, *buf, len);
		page_add_rec(rec, temp1, target);
	}
	free(temp1);
}

