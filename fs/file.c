#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

#include"defs.h"
#include"clogger/clogger.h"
#include"file.h"

extern char *tmp_prefix;
extern Logger *logger;

int file_writeback(File *fbin)
{
	char buf[PAGE_SIZE]={0};
	Page *pg=fbin->curr_pg;
	if(pg==NULL)
		return 0;

	page_tobin(pg, buf);
	if(write(fbin->fd, buf, sizeof(char)*PAGE_SIZE)<0) {
		logger_msg(logger, LOG_ERR,
				"FILE: Write: %s\n", strerror(errno));
		return 0;
	}
	fbin->npgs++;
	fbin->curr_pg=NULL;

	return 1;
}

File *file_create(char *fname, int flag)
{
	int mode=0;
	if(!flag)
		mode=O_CREAT;
	mode|=O_RDWR;

	File *fbin=calloc(1, sizeof(File));
	if(fbin==NULL) {
		logger_msg(logger, LOG_ERR, "FILE: Malloc: Error in allocating memory!\n");
		_exit(-1);
	}

	if((fbin->fd=open(fname, mode))) {
		logger_msg(logger, LOG_ERR,
				"FILE: Open: %s: %s\n", fname, strerror(errno));
		return NULL;
	}

	if(flag) {
		lseek(fbin->fd, 0, SEEK_SET);
		char buf[PAGE_SIZE];
		if(read(fbin->fd, buf, PAGE_SIZE*sizeof(char))<0) {
			logger_msg(logger, LOG_ERR,
					"FILE: Read: %s: %s\n", fname, strerror(errno));
			return NULL;
		}

		fbin->npgs=strtol(buf, NULL, 10);
	}

	return fbin;
}

File *file_load(char *rname, FILE *f, Schema *sch)
{
	char fbin_name[64];
	sprintf(fbin_name, "%s%s.bin", tmp_prefix, rname);

	File *fbin=file_create(fbin_name, 0);
	if(fbin==NULL) {
		return NULL;
	}

	char *line=NULL;
	size_t n=0;
	Page *pg=page_init(sch);
	fbin->curr_pg=pg;
	while(getline(&line, &n, f)!=-1) {
		int flag=-1;
		if(!(page_add_rec(pg, line)) && !(flag=file_writeback(fbin)))
			return NULL;
		if(flag==1) {
			page_deinit(pg);
			pg=page_init(sch);
			fbin->curr_pg=pg;
			page_add_rec(pg, line);
		}
		free(line);
	}
}
