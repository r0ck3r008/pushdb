#ifndef FILE_H
#define FILE_H

#include<stdio.h>

#include"schema.h"
#include"page.h"

typedef struct
{
	int npgs, tot_pgs, fd;
	Page *pg_head, *pg_tail, *lst_pg,
		*curr_pg;
} File;

int file_writeback(File *, int);
File *file_create(char *, Schema *, int);
File *file_load(char *, FILE *, Schema *);
int file_close(File *);

#endif
