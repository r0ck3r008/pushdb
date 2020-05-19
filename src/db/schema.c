#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"alloc.h"
#include"schema.h"

Schema *schema_init(int8_t *name, int8_t *fname)
{
	Schema *sch=db_schema_alloc();
	sch->name=db_char_copy(name);
	sch->fname=db_char_copy(fname);
	sch->map=attmap_init();
	sch->natts=0;

	return sch;
}

void schema_add_att(Schema *sch, int8_t *aname, uint16_t len, DataType type)
{
	uint8_t n=sch->natts;
	attmap_add_att(sch->map, aname, type, len);
	sch->natts++;
}

void schema_deinit(Schema *sch)
{
	uint8_t n=sch->natts;
	attmap_deinit(sch->map);
	free(sch->name);
	free(sch->fname);
	free(sch);
}
