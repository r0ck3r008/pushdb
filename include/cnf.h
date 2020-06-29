#ifndef CNF_H
#define CNF_H

#include"defs.h"
#include"parse_tree.h"
#include"attmap.h"
#include"schema.h"

typedef enum
{
	ATT_COMP,
	INT_COMP,
	FLOAT_COMP,
	STR_COMP
} CompType;

typedef struct Cnf
{
	Attribute *att1;
	CompType type;
	union
	{
		Attribute *att2;
		int ival;
		float fval;
		char *sval;
	};
	struct Cnf *nxt, *dwn;
} Cnf;

Cnf *cnf_init_l(AndList *, Schema *);
Cnf *cnf_init_lr(AndList *, Schema *, Schema *);
void cnf_deinit(Cnf *);

#endif
