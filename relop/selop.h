#ifndef SELOP_H
#define SELOP_H

#include<stdint.h>

#include"db/schema.h"
#include"parser/parse_tree.h"
#include"fs/file.h"

typedef struct
{
	Schema *sch;
	File *file;
	AndList *alist;
} SelOp;

void *selop_run(void *);

#endif
