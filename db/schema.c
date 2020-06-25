#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

#include"alloc.h"
#include"schema.h"
#include"clogger/clogger.h"

extern char *tmp_prefix;
extern Logger *logger;

Schema *schema_init(char *name)
{
	Schema *sch=db_schema_alloc();
	sch->name=db_char_copy(name);
	sch->map=attmap_init();

	return sch;
}

void schema_add_att(Schema *sch, char *aname, int len, DataType type)
{
	attmap_add_att(sch->map, aname, type, len);
}

FILE *fhandle(char *fname, char *perm)
{
	FILE *f=NULL;
	struct stat buf;
	int ret=stat(fname, &buf);
	if(!strcmp(perm, "w") && !ret) {
		logger_msg(logger, LOG_WRN,
			"Schema: Overwriting existing schema!\n");
		if(unlink(fname)<0) {
			logger_msg(logger, LOG_ERR, "Unlink: Error!\n");
			_exit(-1);
		}
	} else if(!strcmp(perm, "r") && ret==-1) {
		logger_msg(logger, LOG_ERR,
				"Schema: No such schema exists!\n");
		return NULL;
	}

	if((f=fopen(fname, perm))==NULL)
		logger_msg(logger, LOG_ERR,
				"Schema: Error in opening sch file!\n");

	return f;
}

void schema_write(Schema *sch)
{
	char *fname=db_char_alloc(128);
	sprintf(fname, "%s%s.sql", tmp_prefix, sch->name);
	FILE *f=fhandle(fname, "w");
	if(f==NULL)
		return;

	for(Attribute *att=sch->map->head; att!=NULL; att=att->nxt_sq)
		fprintf(f, "%s:%d:%d\n", att->name, att->type,
			att->pos);

	fclose(f);
}

Schema *schema_read(char *rname)
{
	char *fname=db_char_alloc(128);
	sprintf(fname, "%s%s.sql", tmp_prefix, rname);
	FILE *f=fhandle(fname, "r");
	if(f==NULL)
		return NULL;

	Schema *sch=schema_init(rname);
	char *line=NULL;
	size_t n=0;
	while(!feof(f)) {
		int stat=getline(&line, &n, f);
		if(stat==-1)
			break;
		char *attname=strtok(line, ":");
		DataType type=(DataType)strtol(strtok(NULL, ":"),
						NULL, 10);
		int pos=(int)strtol(strtok(NULL, ":"),
						NULL, 10);
		schema_add_att(sch, attname, pos, type);
		free(line);
		line=NULL;
	}

	free(line);
	fclose(f);
	return sch;
}

void schema_deinit(Schema *sch)
{
	attmap_deinit(sch->map);
	free(sch->name);
	free(sch);
}
