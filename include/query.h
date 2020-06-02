#ifndef QUERY_H
#define QUERY_H

#include<stdint.h>

#include"parse_tree.h"

#ifdef QUERY_INTERNAL

extern TableList *tables;
extern AndList *boolean;
extern NameList *attsToSelect;
extern int queryType;
extern char *outputVar;
extern char *tableName;
extern char *fileToInsert;
extern char *delim;
extern AttrList *attsToCreate;

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse(void);
extern YY_BUFFER_STATE yy_scan_string();
extern void yy_delete_buffer(YY_BUFFER_STATE);

#endif

typedef struct Query
{
	TableList *tbl;
	AndList *alist;
	NameList *sel_atts;
	int qtype;
	char *opvar, *tbl_name, *ins_fname, *delim;
	AttrList *cr_atts;
} Query;

Query *query_init(const char *);
void query_deinit(Query *);

#endif
