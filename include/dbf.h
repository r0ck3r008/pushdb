#ifndef DBF_H
#define DBF_H

#include"schema.h"
#include"page.h"
#include"file.h"

typedef struct
{
	Page *pg;
	File *file;
	int dirty;
} Dbf;

Dbf *dbf_open(char *, Schema *);
Dbf *dbf_load(char *, char *, Schema *);
void dbf_close(Dbf *);

#endif
