#ifndef FILE_H
#define FILE_H

#include<unistd.h>

#include"page.h"
#include"defs.h"

typedef struct File
{
	int fd, tot_pgs, curr_pgno;
	Schema *sch;
	Page *curr_pg;
} File;

File *file_open(char *, Schema *);
File *file_load(char *, Schema *);
int file_add_page(File *);
void file_close(File *);

#endif
