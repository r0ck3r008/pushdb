#ifndef FILE_H
#define FILE_H

#include<stdio.h>

#include"schema.h"
#include"page.h"

typedef struct
{
	int npgs, pgno, fd;
	Page *pg_head, *pg_tail, *curr_pg;
} File;

int file_writeback(File *, int);
File *file_create(char *, Schema *, int);
File *file_load(char *, FILE *, Schema *);
void file_close(File *);

#endif
