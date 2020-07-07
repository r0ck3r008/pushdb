#ifndef FILE_H
#define FILE_H

#include<stdio.h>

#include"schema.h"
#include"page.h"
#include"fcache.h"

typedef struct
{
	// File descriptor
	int fd;
	// Page being worked on
	Page *currpg;
	// File cache
	FCache *fcache;
} File;

File *file_create(char *, Schema *, int);
File *file_load(char *, FILE *, Schema *);
Page *file_getpg(File *, int);
int file_addpg(File *);
void file_close(File *);

#endif
