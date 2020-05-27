#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

#include"alloc.h"
#include"ddl.h"

uint8_t ddl_create(Query *q)
{
	if(q->tbl_name==NULL || q->cr_atts==NULL) {
		fprintf(stderr, "[-]DDL: Empty table/attribute name!\n");
		return 0;
	}

	Schema *sch=schema_init(q->tbl_name);
	for(AttrList *curr=q->cr_atts; curr!=NULL; curr=curr->next) {
		uint32_t len;
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

uint8_t ddl_insert(Query *q)
{
	if(q->tbl_name==NULL || q->ins_fname==NULL) {
		fprintf(stderr, "[-]DDL: Empty table/attribute name!\n");
		return 0;
	}
	Schema *sch=schema_read(q->tbl_name);

	// fs/file implementation goes here, the per record serialization
	// and bin file creation

	schema_deinit(sch);
	return 1;
}

uint8_t ddl_drop(Query *q)
{
	if(q->tbl_name==NULL) {
		fprintf(stderr, "[-]DDL: Empty table name!\n");
		return 0;
	}

	int8_t *sch_fname=handler_char_alloc(128),
		*bin_fname=handler_char_alloc(128);
	sprintf(sch_fname, "%s.sql", q->tbl_name);
	sprintf(bin_fname, "%s.bin", q->tbl_name);

	if(unlink(sch_fname)<0) {
		fprintf(stderr, "[-]DDL: Error in unlinking %s file: %s\n",
			sch_fname, strerror(errno));
		_exit(-1);
	}

	if(unlink(bin_fname)<0) {
		fprintf(stderr, "[-]DDL: Error in unlinking %s file: %s\n",
			bin_fname, strerror(errno));
		_exit(-1);
	}

	free(sch_fname); free(bin_fname);
	return 1;
}
