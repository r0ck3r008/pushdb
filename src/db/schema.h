#ifndef SCHEMA_H
#define SCHEMA_H

#include<stdint.h>

#include"glbl/defs.h"
#include"attmap.h"

// This structure defines the layout and types of columns of
// any relation in the database. This is basically how we
// handle DDL commands.

typedef struct Schema
{
	int8_t *name;
	int8_t *fname;
	Attribute **map;
	uint8_t natts;
} Schema;

Schema *schema_init(int8_t *, int8_t *);
void schema_deinit(Schema *);
void schema_add_att(Schema *, int8_t *,
			uint16_t, DataType);

#endif
