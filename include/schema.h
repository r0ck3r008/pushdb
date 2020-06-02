#ifndef SCHEMA_H
#define SCHEMA_H

#include"defs.h"
#include"attmap.h"

// This structure defines the layout and types of columns of
// any relation in the database. This is basically how we
// handle DDL commands.

typedef struct Schema
{
	char *name;
	char *delim;
	AttMap *map;
} Schema;

Schema *schema_init(char *);
void schema_deinit(Schema *);
void schema_add_att(Schema *, char *,
			int, DataType);
// both these functions read and write to a file that
// directly relates to the name of the relation, a sql file.
void schema_write(Schema *);
Schema *schema_read(char *);

#endif
