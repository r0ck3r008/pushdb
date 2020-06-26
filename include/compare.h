#ifndef COMPARATOR_H
#define COMPARATOR_H

#include"defs.h"
#include"parse_tree.h"
#include"attmap.h"
#include"schema.h"

typedef struct Cnf
{
	Attribute *att1, *att2;
	int flag;
	union
	{
		int ival;
		float fval;
		char *sval;
	};
	Cnf *nxt, *dwn;
} Cnf;

Cnf *cnf_init(AndList *);
void cnf_deinit(Cnf *);

#endif
