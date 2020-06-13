#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

#include"alloc.h"
#include"ddl.h"
#include"file.h"
#include"clogger/clogger.h"

extern Logger *logger;

int ddl_create(Query *q)
{
	if(q->tbl_name==NULL || q->cr_atts==NULL) {
		logger_msg(logger, LOG_ERR,
				"[-]DDL: Empty table/attribute name!\n");
		return 0;
	}

	Schema *sch=schema_init(q->tbl_name);
	for(AttrList *curr=q->cr_atts; curr!=NULL; curr=curr->next) {
		int len;
		if(curr->type==String)
			len=curr->len;
		else
			len=0;
		schema_add_att(sch, curr->name, len, curr->type);
	}

	schema_write(sch);
	schema_deinit(sch);
	return 1;
}

int ddl_insert(Query *q)
{
	if(q->tbl_name==NULL || q->ins_fname==NULL) {
		logger_msg(logger, LOG_ERR,
				"[-]DDL: Empty table/attribute name!\n");
		return 0;
	}
	Schema *sch=schema_read(q->tbl_name);
	sch->delim=db_char_copy(q->delim);
	char fname[128];
	sprintf(fname, "tmp/%s.bin", q->tbl_name);
	if(!file_load(q->ins_fname, fname, sch)) {
		logger_msg(logger, LOG_ERR,
			"[-]DDL: Error in loading file %s\n", q->ins_fname);
		return 0;
	}

	schema_write(sch);
	schema_deinit(sch);
	return 1;
}

int ddl_drop(Query *q)
{
	if(q->tbl_name==NULL) {
		logger_msg(logger, LOG_ERR,
				"[-]DDL: Empty table name!\n");
		return 0;
	}

	char *sch_fname=handler_char_alloc(128),
		*bin_fname=handler_char_alloc(128);
	sprintf(sch_fname, "tmp/%s.sql", q->tbl_name);
	sprintf(bin_fname, "tmp/%s.bin", q->tbl_name);

	if(unlink(sch_fname)<0) {
		logger_msg(logger, LOG_ERR,
			"[-]DDL: Error in unlinking %s file: %s\n", sch_fname,
			strerror(errno));
		_exit(-1);
	}

	if(unlink(bin_fname)<0) {
		logger_msg(logger, LOG_ERR,
			"[-]DDL: Error in unlinking %s file: %s\n", bin_fname,
			strerror(errno));
		_exit(-1);
	}

	free(sch_fname); free(bin_fname);
	return 1;
}
