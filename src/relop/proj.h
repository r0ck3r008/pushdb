#ifndef PROJ_H
#define PROJ_H

#include<stdint.h>

#include"db/schema.h"
#include"fs/file.h"

typedef struct
{
	Schema *sch;
	File *file
} ProjOp;

void *proj_run(void *);

#endif
