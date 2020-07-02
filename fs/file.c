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

File *file_create(char *fbin_name, Schema *sch, int flag)
{
	int mode=O_RDWR;
	if(!flag)
		mode|=O_CREAT;

	File *fbin=fs_file_alloc();
	if((fbin->fd=open(fbin_name, mode, 0644))<0) {
		logger_msg(logger, LOG_ERR,
			"FILE: Open: %s: %s", fbin_name, strerror(errno));
		return NULL;
	}

	if(flag) {
		fbin->tot_pgs=file_getnpgs(fbin->fd);
		int npgs=(fbin->npgs < N_CACHE_PAGES) ?
			(fbin->npgs) : (N_CACHE_PAGES);
		for(int i=0; i<npgs; i++) {
			char buf[PAGE_SIZE];
			if(read(fbin->fd, buf, PAGE_SIZE*sizeof(char))<0) {
				logger_msg(logger, LOG_ERR,
				"FILE: Read: %s: %s", fbin_name, strerror(errno));
				return NULL;
			}
			Page *pg=page_frombin(buf, sch);
			file_add_pg(fbin, pg);
		}
		if(fbin->tot_pgs==npgs)
			fbin->lst_pg=fbin->pg_tail;
	}

	return fbin;
}
