#ifndef SCHEMA_H
#define SCHEMA_H

#include<stdint.h>

#include "glbl/defs.h"
#include "attmap.h"

// This structure defines the layout and types of columns of
// any relation in the database. This is basically how we
// handle DDL commands.

typedef struct Schema
{
	int8_t *name;
	AttMap *map;
} Schema;

Schema *schema_init(int8_t *);
void schema_deinit(Schema *);
void schema_add_att(Schema *, int8_t *,
			uint32_t, DataType);
// both these functions read and write to a file that
// directly relates to the name of the relation, a sql file.
void schema_write(Schema *);
Schema *schema_read(int8_t *);

#endif
