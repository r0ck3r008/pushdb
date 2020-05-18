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
