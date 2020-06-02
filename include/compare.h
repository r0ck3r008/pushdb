#ifndef COMPARE_H
#define COMPARE_H

#include<stdint.h>

#include"parse_tree.h"
#include"defs.h"
#include"schema.h"
#include"record.h"

typedef struct Literal
{
	Attribute *attL, *attR;
	char val[64];

} Literal;

typedef struct Cnf
{
	Literal lit[16];
	int nlit;
} Cnf;

Cnf *cnf_init_ll(Schema *, AndList *);
Cnf *cnf_init_lr(Schema *, Schema *, AndList *);
int cnf_compare_ll(Schema *, Record *, Cnf *);
int cnf_compare_lr(Schema *, Schema *, Record *,
			Record *, Cnf *);
void cnf_deinit(Cnf *);

#endif
