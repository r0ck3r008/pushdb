#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string.h>
#include<sys/file.h>
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

Page *fcache_getpg(FCache *fcache, Schema *sch, int fd, int pgno)
{
	//first search in cache
	for(Page *currpg=fcache->pg_head; currpg!=NULL; currpg=currpg->next)
		if(currpg->pgno==pgno)
			return currpg;

	// if still here, lock the fd
	char buf[PAGE_SIZE];
	Page *ret=NULL;
	int error=0;
	if(flock(fd, LOCK_SH)<0) {
		logger_msg(logger, LOG_ERR,
			"FCACHE: Flock: %s", strerror(errno));
		return NULL;
	}
	lseek(fd, pgno*sizeof(char)*PAGE_SIZE, SEEK_SET);
	if(read(fd, buf, sizeof(char)*PAGE_SIZE)<0) {
		logger_msg(logger, LOG_ERR,
			"FCACHE: Read: %s", strerror(errno));
		// Even tho read failed, unlocking is necessary, so
		// dont just return yet.
		error=1;
	}
	if(flock(fd, LOCK_UN)<0) {
		logger_msg(logger, LOG_ERR,
			"FCACHE: Flock: %s", strerror(errno));
		// unlock faliure must result in hard exit
		_exit(-1);
	}

	if(!error)
		ret=page_frombin(buf, sch);
	return ret;
}

int fcache_syncpg(FCache *fcache, Page *pg, int fd)
{
	int error=0;
	if(!pg->sync) {
		char buf[PAGE_SIZE];
		page_tobin(pg, buf);
		if(flock(fd, LOCK_EX)<0) {
			logger_msg(logger, LOG_ERR,
				"FCACHE: Flock: %s", strerror(errno));
			return 0;
		}
		lseek(fd, pg->pgno*sizeof(char)*PAGE_SIZE, SEEK_SET);
		if(write(fd, buf, sizeof(char)*PAGE_SIZE)<0) {
			logger_msg(logger, LOG_ERR,
				"FCACHE: Write: %s", strerror(errno));
			// Even tho write failed, unlocking is necessary, so
			// dont just return yet.
			error=1;
		}
		if(flock(fd, LOCK_UN)<0) {
			logger_msg(logger, LOG_ERR,
				"FCACHE: Flock: %s", strerror(errno));
			// Unlock faliure must result in hard exit
			_exit(-1);
		}
		pg->sync=1;
	}

	if(error)
		return 0;

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
