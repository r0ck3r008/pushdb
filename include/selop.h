#ifndef SELOP_H
#define SELOP_H

#include<stdint.h>

#include"schema.h"
#include"parse_tree.h"
#include"file.h"

typedef struct
{
	Schema *sch;
	File *file;
	AndList *alist;
} SelOp;

void *selop_run(void *);

#endif
