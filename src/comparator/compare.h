#ifndef COMPARE_H
#define COMPARE_H

#include<stdint.h>

#include"parser/parse_tree.h"
#include"glbl/defs.h"
#include"db/schema.h"
#include"fs/record.h"

typedef struct Literal
{
	Attribute *attL, *attR;
	int8_t val[64];

} Literal;

typedef struct Cnf
{
	Literal lit[16];
	uint8_t nlit;
} Cnf;

Cnf *cnf_init_ll(Schema *, AndList *);
Cnf *cnf_init_lr(Schema *, Schema *, AndList *);
uint8_t cnf_compare_ll(Schema *, Record *, Cnf *);
uint8_t cnf_compare_lr(Schema *, Schema *, Record *,
			Record *);
void cnf_deinit(Cnf *);

#endif
