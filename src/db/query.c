#define QUERY_INTERNAL

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"alloc.h"
#include"query.h"

Query *query_init(const char *str)
{
	if(str==NULL && yyparse()) {
		fprintf(stderr, "[-]Query: Error in query parsing!\n");
		_exit(-1);
	} else if(str!=NULL){
		YY_BUFFER_STATE buffer=yy_scan_string(str);
		yyparse();
		yy_delete_buffer(buffer);
	}

	Query *q=db_query_alloc();
	q->tbl=tables;
	q->alist=boolean;
	q->sel_atts=attsToSelect;
	q->qtype=queryType;
	q->opvar=outputVar;
	q->tbl_name=tableName;
	q->ins_fname=fileToInsert;
	q->cr_atts=attsToCreate;

	return q;
}

void alist_deinit(AndList *alist, OrList *olist)
{
	if(alist==NULL)
		return;

	if(olist==NULL && alist->left!=NULL) {
		alist_deinit(alist, alist->left);
		free(alist->left);
	} else {
		ComparisonOp *cop=olist->left;
		Operand *opL=cop->left, *opR=cop->right;
		free(opL->value); free(opR->value);
		free(cop);
	}

	if(olist!=NULL && olist->rightOr!=NULL) {
		alist_deinit(alist, olist->rightOr);
		free(olist->rightOr);
	}

	if(olist==NULL && alist->rightAnd!=NULL) {
		alist_deinit(alist->rightAnd, NULL);
		free(alist->rightAnd);
	}
}

void tablelist_deinit(TableList *list)
{
	if(list==NULL)
		return;

	while(list->next!=NULL) {
		TableList *curr=list->next;
		free(curr->tableName);
		free(curr->aliasAs);
		list->next=curr->next;
		free(curr);
	}

	free(list->tableName);
	free(list->aliasAs);
	free(list);
}

void namelist_deinit(NameList *list)
{
	if(list==NULL)
		return;

	while(list->next!=NULL) {
		NameList *curr=list->next;
		free(curr->name);
		list->next=curr->next;
		free(curr);
	}

	free(list->name);
	free(list);
}

void attrlist_deinit(AttrList *list)
{
	if(list==NULL)
		return;

	while(list->next!=NULL) {
		AttrList *curr=list->next;
		free(curr->name);
		list->next=curr->next;
		free(curr);
	}

	free(list->name);
	free(list);
}

void query_deinit(Query *q)
{
	free(q->ins_fname);
	free(q->tbl_name);
	free(q->opvar);
	alist_deinit(q->alist, NULL); free(q->alist);
	free(q->tbl); free(q->sel_atts); free(q->cr_atts);
}
