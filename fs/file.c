#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

#include"alloc.h"
#include"file.h"
#include"clogger/clogger.h"

extern Logger *logger;

File *file_open(char *path, int flag, Schema *sch)
{
	File *file=fs_file_alloc();
	int mode;
	if(!flag)
		mode=O_RDWR;
	else
		mode=O_CREAT | O_RDWR;

	if((file->fd=open(path, mode, 0644))<0) {
		logger_msg(logger, LOG_ERR, "[-]FILE: %s: %s\n",
			strerror(errno), path);
		goto exit_err;
	}

	if(!flag) {
		char buf[PAGE_SIZE];
		lseek(file->fd, 0, SEEK_SET);
		read(file->fd, buf, PAGE_SIZE);
		file->tot_pgs=(int)strtol(buf, NULL, 10);
	}
	file->sch=sch;

	return file;
exit_err:
	free(file);
	return NULL;
}

int file_load(char *ifname, char *ofname, Schema *sch)
{
	File *fbin=file_open(ofname, sch);
	FILE *f=NULL;
	if((f=fopen(ifname, "r"))==NULL) {
		logger_msg(logger, LOG_ERR, "[-]FILE: %s\n", strerror(errno));
		return 0;
	}
	Page *pg=page_init();
	fbin->curr_pg=pg;
	char *line=NULL;
	size_t n=0;
	while(getline(&line, &n, f)!=-1) {
		int flag=0;
		if(!page_add_rec(pg, line, sch) && !(flag=file_add_page(fbin))) {
			logger_msg(logger, LOG_ERR,
					"[-]FILE: Error in adding record!\n");
			return 0;
		}
		if(flag) {
			page_deinit(pg);
			pg=page_init();
			fbin->curr_pg=pg;
		}
	}

	file_close(fbin);
	free(line);
	fclose(f);
	return 1;
}

int file_add_page(File *f)
{
	char buf[PAGE_SIZE];
	page_to_bin(f->curr_pg, buf, f->sch);

	lseek(f->fd, PAGE_SIZE*(f->tot_pgs+1), SEEK_SET);
	if(write(f->fd, buf, PAGE_SIZE)<0) {
		logger_msg(logger, LOG_ERR, "[-]FILE: Error in writing: %s\n",
			strerror(errno));
		return 0;
	}
	f->tot_pgs++;
	f->curr_pgno=f->tot_pgs;
	page_deinit(f->curr_pg);
	f->curr_pg=NULL;

	return 1;
}

void file_close(File *f)
{
	if(f->curr_pg!=NULL && !file_add_page(f))
		_exit(-1);

	lseek(f->fd, 0, SEEK_SET);
	char buf[PAGE_SIZE];
	sprintf(buf, "%d", f->tot_pgs);
	if(write(f->fd, buf, PAGE_SIZE)<0) {
		logger_msg(logger, LOG_ERR,
			"[-]FILE: Error in page count: %s\n", strerror(errno));
		_exit(-1);
	}

	if(close(f->fd)<0) {
		logger_msg(logger, LOG_ERR,
		"[-]FILE: Error in closing the file: %s\n", strerror(errno));
		_exit(-1);
	}
	free(f);
}
