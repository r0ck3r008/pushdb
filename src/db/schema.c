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
	sch->atts=db_attributep_alloc(64);
	sch->natts=0;

	return sch;
}

void schema_add_att(Schema *sch, int8_t *aname, uint16_t len, DataType type)
{
	if(sch->natts==64) {
		fprintf(stderr, "[-]Schema: Attribute Limit reached!\n");
		return;
	}

	uint8_t n=sch->natts;
	sch->atts[n]=db_attribute_alloc();
	sch->atts[n]->name=db_char_copy(aname);
	sch->atts[n]->type=type;
	sch->atts[n]->len=len;
	sch->natts++;
}

void schema_deinit(Schema *sch)
{
	uint8_t n=sch->natts;
	for(int i=0; i<n; i++) {
		free(sch->atts[i]->name);
		free(sch->atts[i]);
	}

	free(sch->name);
	free(sch->fname);
	free(sch);
}
