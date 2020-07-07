#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

#include"file.h"
#include"defs.h"
#include"alloc.h"
#include"clogger/clogger.h"

extern Logger *logger;
extern char *tmp_prefix;

int file_fexists(char *fname)
{
	struct stat buf;
	if(stat(fname, &buf)<0)
		return 0;
	else
		return 1;
}

File *file_create(char *fbin_name, int fexists)
{
	int mode=O_RDWR;
	if(!fexists)
		mode|=O_CREAT;

	File *fbin=fs_file_alloc();

	if((fbin->fd=open(fbin_name, mode))<0) {
		logger_msg(logger, LOG_ERR,
			"FILE: Open: %s: %s\n", fbin_name, strerror(errno));
		file_close(fbin);
		return NULL;
	}

	if(fexists) {
		int tot_pgs=fcache_getnpgs(fbin->fcache, fbin->fd);
		int pgcnt=(tot_pgs < N_CACHE_PAGES) ? (tot_pgs) : (N_CACHE_PAGES);
		for(int i=0; i<pgcnt; i++) {
			fbin->currpg=fcache_getpg(fbin->fcache, fbin->fd, i);
			if(!fcache_addpg(fbin->fcache, fbin->currpg, fbin->fd))
				return NULL;
		}
	}

	return fbin;
}

File *file_load(char *relname, FILE *insf, Schema *sch)
{
	char fbin_name[128];
	sprintf(fbin_name, "%s%s.bin", tmp_prefix, relname);
	if(file_fexists(fbin_name))
		return NULL;

	File *fbin=file_create(fbin_name, 0);

	char *line=NULL;
	size_t n=0;
	fbin->currpg=page_init(sch);
	while(getline(&line, &n, insf)>0) {
		int flag=0;
		if(!page_add_rec(fbin->currpg, line, 1) &&
			!(flag=fcache_addpg(fbin->fcache, fbin->currpg, fbin->fd)))
			return NULL;
		if(flag) {
			page_deinit(fbin->currpg);
			fbin->currpg=page_init(sch);
		}
		free(line); line=NULL;
		n=0;
	}

	free(line);

	return fbin;
}

Page *file_getpg(File *fbin, int pgno)
{
	return (fcache_getpg(fbin->fcache, fbin->fd, pgno));
}

int file_addpg(File *fbin)
{
	return (fcache_addpg(fbin->fcache, fbin->currpg, fbin->fd));
}

void file_close(File *fbin)
{
	if(!fcache_addpg(fbin->fcache, fbin->currpg, fbin->fd))
		_exit(-1);
	if(!fcache_writeback(fbin->fcache, fbin->fd))
		_exit(-1);
	fcache_deinit(fbin->fcache);
	close(fbin->fd);
	free(fbin);
}
