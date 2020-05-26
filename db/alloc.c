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

int8_t *db_char_alloc(uint32_t size)
{
	int8_t *ret=calloc(size, 1);
	if(ret=NULL) {
		fprintf(stderr, "[-]Schema: Unable to allocate char memory!\n");
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
	Attribute **atts=calloc(size, sizeof(Attribute *));
	if(atts==NULL) {
		fprintf(stderr, "[-]Schema: Unable to allocate attributes!\n");
		_exit(-1);
	}

	return atts;
}

Attribute *db_attribute_alloc()
{
	Attribute *att=calloc(1, sizeof(Attribute));
	if(att==NULL) {
		fprintf(stderr, "[-]Schema: Unable to allocate attribute!\n");
		_exit(-1);
	}

	return att;
}

AttMap *db_attmap_alloc()
{
	AttMap *map=calloc(1, sizeof(AttMap));
	if(map==NULL) {
		fprintf(stderr, "[-]AttMap: Error in allocating memory!\n");
		_exit(-1);
	}

	map->map=db_attributep_alloc(ATTMAP_SIZE);
	if(map->map==NULL) {
		fprintf(stderr, "[-]AttMap: Error in allocating memory!\n");
		_exit(-1);
	}

	return map;
}

Query *db_query_alloc()
{
	Query *q=malloc(sizeof(Query));
	if(q==NULL) {
		fprintf(stderr, "[-]Query: Unable to allocate space!\n");
		_exit(-1);
	}
}
