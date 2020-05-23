#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

#include"alloc.h"
#include"schema.h"

Schema *schema_init(int8_t *name)
{
	Schema *sch=db_schema_alloc();
	sch->name=db_char_copy(name);
	sch->map=attmap_init();

	return sch;
}

void schema_add_att(Schema *sch, int8_t *aname, uint32_t len, DataType type)
{
	attmap_add_att(sch->map, aname, type, len);
}

FILE *fhandle(int8_t *fname, int8_t *perm)
{
	FILE *f=NULL;
	struct stat buf;
	uint8_t ret=stat(fname, &buf);
	if(!strcmp(perm, "w") && !ret) {
		fprintf(stderr, "[-]Schema: Overwriting existing schema!\n");
		if(unlink(fname)<0) {
			fprintf(stderr, "[-]Unlink: Error!\n");
			_exit(-1);
		}
	} else if(!strcmp(perm, "r") && ret==-1) {
		fprintf(stderr, "[-]Schema: No such schema exists!\n");
		return NULL;
	}

	if((f=fopen(fname, perm))==NULL)
		fprintf(stderr, "[-]Schema: Error in opening sch file!\n");

	return f;
}

void schema_write(Schema *sch)
{
	int8_t *fname=db_char_alloc(128);
	sprintf(fname, "%s.sql", sch->name);
	FILE *f=fhandle(fname, "w");
	if(f==NULL)
		return;

	for(Attribute *att=sch->map->head; att!=NULL; att=att->nxt_sq)
		fprintf(f, "%s:%d:%d\n", att->name, att->type,
			att->pos);
}

void schema_read(Schema *sch)
{
	int8_t *fname=db_char_alloc(128);
	sprintf(fname, "%s.sql", sch->fname);
	FILE *f=fhandle(fname, "w");
}

void schema_deinit(Schema *sch)
{
	attmap_deinit(sch->map);
	free(sch->name);
	free(sch->fname);
	free(sch);
}
