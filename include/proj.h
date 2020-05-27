#ifndef PROJ_H
#define PROJ_H

#include<stdint.h>

#include"schema.h"
#include"file.h"

typedef struct
{
	Schema *sch;
	File *file;
} ProjOp;

void *proj_run(void *);

#endif
