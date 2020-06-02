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
		int lenL, lenR;
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

int cnf_compare_ll(Schema *sch, Record *rec, Cnf *cnf)
{
	for(uint8_t i=0; i<cnf->nlit; i++) {
		Attribute *att=cnf->lit[i].attL;
		if(att->type==Int) {
			int rec_val=((int *)rec->bits)[att->pos];
			int val=(int)strtol(cnf->lit[i].val,
								NULL, 10);
			if(rec_val!=val)
				return 0;
		} else if(att->type==Float) {
			float rec_val=((float *)rec->bits)[att->pos];
			float val=(float)strtof(cnf->lit[i].val, NULL);
			if(rec_val!=val)
				return 0;
		} else if(att->type==String) {
			uint32_t len=attribute_get_len(sch->map, att);
			if(strncmp(&(((char *)rec->bits)[att->pos]),
					cnf->lit[i].val, len))
				return 0;
		}
	}

	return 1;
}

int cnf_compare_lr(Schema *schL, Schema *schR,
			Record *recL, Record *recR, Cnf *cnf)
{
	for(uint8_t i=0; i<cnf->nlit; i++) {
		Attribute *attL=cnf->lit[i].attL;
		Attribute *attR=cnf->lit[i].attR;
		if(attL->type==Int) {
			uint32_t rec_valL=((uint32_t *)recL->bits)[attL->pos];
			uint32_t rec_valR=((uint32_t *)recR->bits)[attR->pos];
			if(rec_valL!=rec_valR)
				return 0;
		} else if(attL->type==Float) {
			float rec_valL=((float *)recL->bits)[attL->pos];
			float rec_valR=((float *)recR->bits)[attR->pos];
			if(rec_valL!=rec_valR)
				return 0;
		} else if(attL->type==String) {
			uint32_t lenL=attribute_get_len(schL->map, attL);
			uint32_t lenR=attribute_get_len(schR->map, attR);
			if(strncmp(&(((char *)recL->bits)[attL->pos]),
				&(((char *)recR->bits)[attR->pos]),
				((lenL>=lenR) ? (lenR) : (lenL))))
				return 0;
		}
	}

	return 1;
}

void cnf_deinit(Cnf *cnf)
{
	// placeholder function for future compatibility
	free(cnf);
}
