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

File *file_load(char *fbin_name, FILE *insf, Schema *sch)
{
	File *fbin=file_create(fbin_name, sch, 0);

	char *line=NULL;
	size_t n=0;
	fbin->curr_pg=page_init(sch);
	while(getline(&line, &n, insf)>0) {
		int flag=0;
		if(!page_add_rec(fbin->curr_pg, line, 1) &&
			!(flag=file_add_pg(fbin))) {
			logger_msg(logger, LOG_ERR,
				"FILE: Load: Error in adding record!");
			return NULL;
		}
		if(flag)
			fbin->curr_pg=page_init(sch);

		free(line);
		line=NULL;
		n=0;
	}
	free(line);

	return fbin;
}

int file_close(File *fbin)
{
	if(!file_writeback(fbin, 1))
		return 0;

	close(fbin->fd);
	page_deinit(fbin->pg_head); page_deinit(fbin->pg_tail);
	page_deinit(fbin->lst_pg); page_deinit(fbin->curr_pg);
	free(fbin);

	return 1;
}
