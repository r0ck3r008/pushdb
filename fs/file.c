#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

#include"alloc.h"
#include"file.h"

File *file_open(char *path, Schema *sch)
{
	File *file=fs_file_alloc();
	struct stat buf;
	int mode, status;
	if(!(status=stat(path, &buf))) {
		mode=O_RDWR;
	} else if(status<0 && errno==ENOENT) {
		mode=O_CREAT | O_RDWR;
	} else {
		fprintf(stderr, "[-]FILE: %s: %s\n",
			strerror(errno), path);
		goto exit_err;
	}

	if((file->fd=open(path, mode, 0644))<0) {
		fprintf(stderr, "[-]FILE: %s: %s\n",
			strerror(errno), path);
		goto exit_err;
	}

	if(!status) {
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

File *file_load(char *fname, Schema *sch)
{
	File *fbin=file_open(fname, sch);
	FILE *f=NULL;
	if((f=fopen(fname, "r"))==NULL) {
		fprintf(stderr, "[-]FILE: %s\n", strerror(errno));
		return NULL;
	}
	Page *pg=page_init();
	fbin->curr_pg=pg;
	char *line=NULL;
	size_t n=0;
	while(getline(&line, &n, f)!=-1) {
		int flag=0;
		if(!page_add_rec(pg, line, sch) && !(flag=file_add_page(fbin))) {
			fprintf(stderr, "[-]FILE: Error in adding record!\n");
			return NULL;
		}
		if(flag) {
			page_deinit(pg);
			pg=page_init();
			fbin->curr_pg=pg;
		}
	}

	page_deinit(pg);
	free(line);
	fclose(f);
	return fbin;
}

int file_add_page(File *f)
{
	char buf[PAGE_SIZE];
	page_to_bin(f->curr_pg, buf, f->sch);

	lseek(f->fd, PAGE_SIZE*(f->tot_pgs+1), SEEK_SET);
	if(write(f->fd, buf, PAGE_SIZE)<0) {
		fprintf(stderr, "[-]FILE: Error in writing: %s\n",
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
		fprintf(stderr, "[-]FILE: Error in page count: %s\n",
			strerror(errno));
		_exit(-1);
	}

	if(close(f->fd)<0) {
		fprintf(stderr, "[-]FILE: Error in closeing the file: %s\n",
			strerror(errno));
		_exit(-1);
	}
	free(f);
}
