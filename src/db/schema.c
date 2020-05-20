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

	return sch;
}

void schema_add_att(Schema *sch, int8_t *aname, uint32_t len, DataType type)
{
	attmap_add_att(sch->map, aname, type, len);
}

void schema_deinit(Schema *sch)
{
	attmap_deinit(sch->map);
	free(sch->name);
	free(sch->fname);
	free(sch);
}
