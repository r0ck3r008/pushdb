#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"
#include"clogger/clogger.h"

extern Logger *logger;

char *db_char_copy(char *str)
{
	char *ret=strdup(str);
	if(ret==NULL) {
		logger_msg(logger, LOG_ERR,
			"Schema: Unable to copy string!");
		_exit(-1);
	}

	return ret;
}

char *db_char_alloc(int size)
{
	char *ret=calloc(size, 1);
	if(ret==NULL) {
		logger_msg(logger, LOG_ERR,
			"Schema: Unable to allocate char memory!");
		_exit(-1);
	}

	return ret;
}

Schema *db_schema_alloc()
{
	Schema *sch=calloc(1, sizeof(Schema));
	if(sch==NULL) {
		logger_msg(logger, LOG_ERR,
			"Schema: Unable to alloc schema!");
		_exit(-1);
	}

	return sch;
}

Attribute **db_attributep_alloc(int size)
{
	Attribute **atts=calloc(size, sizeof(Attribute *));
	if(atts==NULL) {
		logger_msg(logger, LOG_ERR,
			"Schema: Unable to allocate attributes!");
		_exit(-1);
	}

	return atts;
}

Attribute *db_attribute_alloc()
{
	Attribute *att=calloc(1, sizeof(Attribute));
	if(att==NULL) {
		logger_msg(logger, LOG_ERR,
				"Schema: Unable to allocate attribute!");
		_exit(-1);
	}

	return att;
}

AttMap *db_attmap_alloc()
{
	AttMap *map=calloc(1, sizeof(AttMap));
	if(map==NULL) {
		logger_msg(logger, LOG_ERR,
				"AttMap: Error in allocating memory!");
		_exit(-1);
	}

	map->map=db_attributep_alloc(ATTMAP_SIZE);
	if(map->map==NULL) {
		logger_msg(logger, LOG_ERR,
				"AttMap: Error in allocating memory!");
		_exit(-1);
	}

	return map;
}

Query *db_query_alloc()
{
	Query *q=malloc(sizeof(Query));
	if(q==NULL) {
		logger_msg(logger, LOG_ERR,
				"Query: Unable to allocate space!");
		_exit(-1);
	}

	return q;
}
