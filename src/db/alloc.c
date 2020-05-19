#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"

int8_t *db_char_copy(int8_t *str)
{
	int8_t *ret=strdup(str);
	if(ret==NULL) {
		fprintf(stderr, "[-]Schema: Unable to copy string!\n");
		_exit(-1);
	}

	return ret;
}

Schema *db_schema_alloc()
{
	Schema *sch=malloc(sizeof(Schema));
	if(sch==NULL) {
		fprintf(stderr, "[-]Schema: Unable to alloc schema!\n");
		_exit(-1);
	}

	return sch;
}

Attribute **db_attributep_alloc(uint8_t size)
{
	Attribute **atts=malloc(sizeof(Attribute *)*size);
	if(atts==NULL) {
		fprintf(stderr, "[-]Schema: Unable to allocate attributes!\n");
		_exit(-1);
	}

	return atts;
}

Attribute *db_attribute_alloc()
{
	Attribute *att=malloc(sizeof(Attribute));
	if(att==NULL) {
		fprintf(stderr, "[-]Schema: Unable to allocate attribute!\n");
		_exit(-1);
	}

	return att;
}

Query *db_query_alloc()
{
	Query *q=malloc(sizeof(Query));
	if(q==NULL) {
		fprintf(stderr, "[-]Query: Unable to allocate space!\n");
		_exit(-1);
	}
}
