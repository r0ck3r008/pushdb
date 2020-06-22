#ifndef FILE_H
#define FILE_H

#include"schema.h"
#include"page.h"

typedef struct
{
	int npgs, pgno, fd;
	Page *curr_pg;
} File;

int file_writeback(File *);
File *file_create(char *, int);
File *file_load(char *, FILE *, Schema *);
void file_close(File *);

#endif
