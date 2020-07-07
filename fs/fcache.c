#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

#include"fcache.h"
#include"defs.h"
#include"clogger/clogger.h"

extern Logger *logger;

int fcache_getnpgs(FCache *fcache, int fd)
{
	struct stat buf;
	if(fstat(fd, &buf)<0) {
		logger_msg(logger, LOG_ERR,
			"FCACHE: Fstat: %s", strerror(errno));
		_exit(-1);
	}

	fcache->tot_pgs=(int)(buf.st_size/PAGE_SIZE);

	return fcache->tot_pgs;
}

int fcache_addpg(FCache *fcache, Page *pg, int fd)
{
	if(fcache->cache_pgs == N_CACHE_PAGES) {
		if(!fcache_syncpg(fcache, fcache->pg_head, fd))
			return 0;
		Page *currpg=fcache->pg_head;
		fcache->pg_head=currpg->next;
		fcache->cache_pgs--;
		page_deinit(currpg);
	}

	if(fcache->pg_head==NULL)
		fcache->pg_head=pg;
	else
		fcache->pg_tail->next=pg;
	fcache->pg_tail=pg;
	fcache->cache_pgs++;
	if(!pg->sync)
		// This helps in identifying if the page was ever in cache
		// before this, since if it hasn't been synced to disk yet, it
		// is a new one. Otherwise, npgs includes tot_pgs already, that
		// were synced
		fcache->npgs++;

	return 1;
}

int fcache_writeback(FCache *fcache, int fd)
{
	for(Page *currpg=fcache->pg_head; currpg!=NULL; currpg=currpg->next)
		if(!fcache_syncpg(fcache, currpg, fd))
			return 0;

	return 1;
}

void fcache_deinit(FCache *fcache)
{
	// must be called after writeback is called.
	Page *currpg=fcache->pg_head->next;
	while(currpg!=NULL) {
		fcache->pg_head->next=currpg->next;
		page_deinit(currpg);
		currpg=fcache->pg_head->next;
	}
	page_deinit(fcache->pg_head);
	free(fcache);
}
