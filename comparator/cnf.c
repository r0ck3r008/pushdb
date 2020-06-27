#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"clogger/clogger.h"
#include"alloc.h"
#include"cnf.h"

extern Logger *logger;

void cnf_add_node(Cnf *start, Cnf *new, int dir)
{
	if(dir)
		start->nxt=new;
	else
		start->dwn=new;
}

void cnf_olist_parse(Cnf *cnf, OrList *olist,
				Schema *schL, Schema *schR)
{
	ComparisonOp *cop=olist->left;
	Operand *opL=cop->left, *opR=cop->right;
	cnf->att1=attmap_find(schL->map, opL->value);
	switch(opR->code) {
	case NAME:
		cnf->type=ATT_COMP;
		cnf->att2=attmap_find(schR->map, opR->value);
		break;
	case INT:
		cnf->type=INT_COMP;
		cnf->ival=(int)strtol(opR->value, NULL, 10);
		break;
	case FLOAT:
		cnf->type=FLOAT_COMP;
		cnf->fval=(float)strtof(opR->value, NULL);
		break;
	case STRING:
		cnf->type=STR_COMP;
		cnf->sval=comparator_char_copy(opR->value);
		break;
	default:
		logger_msg(logger, LOG_ERR,
				"CNF: Undefined literal type!");
		_exit(-1);
	}
}

Cnf *cnf_alist_parse(AndList *alist, OrList *olist,
			Schema *schL, Schema *schR)
{
	Cnf *cnf=comparator_cnf_alloc();

	if(olist==NULL && alist->left!=NULL)
		cnf=cnf_alist_parse(alist, alist->left, schL, schR);
	else
		cnf_olist_parse(cnf, olist, schL, schR);

	if(olist!=NULL && olist->rightOr!=NULL)
		cnf_add_node(cnf,
			cnf_alist_parse(alist, olist->rightOr, schL, schR), 1);

	if(alist->rightAnd!=NULL)
		cnf_add_node(cnf,
			cnf_alist_parse(alist->rightAnd, NULL, schL, schR), 0);

	return cnf;
}

// For select family comparisons.
Cnf *cnf_init_l(AndList *alist, Schema *sch)
{
	Cnf *cnf=cnf_alist_parse(alist, NULL, sch, NULL);

	return cnf;
}

// For join family of comparisons.
Cnf *cnf_init_lr(AndList *alist, Schema *schL, Schema *schR)
{
	Cnf *cnf=cnf_alist_parse(alist, NULL, schL, schR);

	return cnf;
}

void cnf_free(Cnf *cnf)
{
	if(cnf->type==STR_COMP)
		free(cnf->sval);
	free(cnf);
}

void cnf_deinit(Cnf *cnf)
{
	while(cnf!=NULL) {
		Cnf *curr=cnf->dwn;
		while(curr!=NULL) {
			cnf->dwn=curr->dwn;
			cnf_free(curr);
			curr=cnf->dwn;
		}
		Cnf *tmp=cnf->nxt;
		cnf_free(cnf);
		cnf=tmp;
	}
}
