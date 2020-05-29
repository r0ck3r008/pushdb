#ifndef FILE_H
#define FILE_H

#include<stdint.h>
#include<unistd.h>

#include"page.h"
#include"defs.h"

typedef struct File
{
	int fd, tot_pgs, curr_pgno;
	Schema *sch;
	Page *curr_pg;
} File;

File *file_open(int8_t *, Schema *);
int file_add_page(File *);
Page *file_get_page(File *, off_t);
void file_close(File *);

#endif
