#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

#include"clogger/clogger.h"
#include"alloc.h"
#include"defs.h"
#include"file.h"

extern Logger *logger;
extern char *tmp_prefix;

int file_getnpgs(int fd)
{
	struct stat buf;
	explicit_bzero(&buf, sizeof(struct stat));
	if(fstat(fd, &buf)<0) {
		logger_msg(logger, LOG_ERR,
			"FILE: Fstat: %s", strerror(errno));
		return -1;
	}

	return ((int)buf.st_size/PAGE_SIZE);
}

void file_add_pg(File *fbin, Page *pg)
{
	if(fbin->npgs==N_CACHE_PAGES) {
		logger_msg(logger, LOG_WRN,
			"FILE: PageAdd: Deleting cached page!");
	}

	if(fbin->pg_head==NULL)
		fbin->pg_head=pg;
	else
		fbin->pg_tail->next=pg;
	fbin->pg_tail=pg;
	fbin->npgs++;
}

