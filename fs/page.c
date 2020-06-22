#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"defs.h"
#include"clogger/clogger.h"
#include"page.h"

extern Logger *logger;

Page *page_init(Schema *sch)
{
	Page *pg=calloc(1, sizeof(Page));
	if(pg==NULL) {
		logger_msg(logger, LOG_ERR,
				"PAGE: Malloc: Error in allocating memory!\n");
		_exit(-1);
	}
	pg->sch=sch;

	return pg;
}

int page_add_rec(Page *pg, char *str)
{
	int ret=1;
	if(((pg->nrecs)*(pg->sch->map->tot_len))<PAGE_SIZE) {
		Record *rec=record_ser(str, pg->sch);
		if(pg->head==NULL)
			pg->head=rec;
		else
			pg->tail->next=rec;
		pg->tail=rec;
		pg->nrecs++;
	} else {
		ret=0;
	}

	return ret;
}

void page_deinit(Page *pg)
{
	if(pg->head!=NULL) {
		Record *curr=pg->head->next;
		while(pg->head->next!=NULL) {
			pg->head->next=curr->next;
			record_deinit(curr);
			curr=pg->head->next;
		}
		record_deinit(pg->head);
	}

	free(pg);
}
