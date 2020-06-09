#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include"defs.h"
#include"alloc.h"
#include"page.h"
#include"clogger/clogger.h"

extern Logger *logger;

Page *page_init()
{
	Page *pg=fs_page_alloc();

	return pg;
}

int page_add_rec(Page *pg, char *rec_str, Schema *sch)
{
	if(sch->delim==NULL) {
		logger_msg(logger, LOG_ERR,
			"[-]PAGE: delimiter not found in schema!\n");
		return 0;
	}

	// +1 is for the delimiter
	if((pg->curr_sz + sch->map->tot_len + 1) >= PAGE_SIZE) {
		logger_msg(logger, LOG_ERR, "[-]PAGE: page full!\n");
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

void page_to_bin(Page *pg, char *buf, Schema *sch)
{
	if(buf==NULL) {
		logger_msg(logger, LOG_ERR,
			"[-]PAGE: Unallocated buffer placeholder!\n");
		_exit(-1);
	}

	Record *curr=pg->first;
	while(curr!=NULL) {
		sprintf(buf, "%s%s%s", buf, sch->delim, curr->bits);
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
