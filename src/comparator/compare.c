#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"
#include"compare.h"

void alist_trav(AndList *alist, OrList *olist, Cnf *cnf,
				Schema *schL, Schema *schR)
{
	if(olist==NULL && alist->left!=NULL) {
		alist_trav(alist, alist->left, cnf, schL, schR);
	} else if(olist!=NULL) {
		if(cnf->nlit==16) {
			fprintf(stderr, "[-]Cnf: Exceeded comparisons > 16\n");
			_exit(-1);
		}
		Operand *left=olist->left->left, *right=olist->left->right;
		uint32_t lenL, lenR;
		cnf->lit[cnf->nlit].attL=attmap_find(schL->map,
							left->value, &lenL);
		if(schR!=NULL)
			cnf->lit[cnf->nlit].attR=attmap_find(schR->map,
							right->value, &lenR);
		else
			sprintf(cnf->lit[cnf->nlit].val, "%s", right->value);
		cnf->nlit++;
	}

	if(olist!=NULL && olist->rightOr!=NULL)
		alist_trav(alist, olist->rightOr, cnf, schL, schR);
	if(olist==NULL && alist->rightAnd!=NULL)
		alist_trav(alist->rightAnd, NULL, cnf, schL, schR);
}

Cnf *cnf_init_ll(Schema *sch, AndList *alist)
{
	Cnf *cnf=comparator_cnf_alloc();
	alist_trav(alist, NULL, cnf, sch, NULL);

	return cnf;
}

Cnf *cnf_init_lr(Schema *schL, Schema *schR, AndList *alist)
{
	Cnf *cnf=comparator_cnf_alloc();
	alist_trav(alist, NULL, cnf, schL, schR);

	return cnf;
}

void cnf_deinit(Cnf *cnf)
{
	// placeholder function for future compatibility
	free(cnf);
}
