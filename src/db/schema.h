#ifndef SCHEMA_H
#define SCHEMA_H

#include<stdint.h>

#include"glbl/defs.h"

// This structure is the atomic representation of the
// attribute which stores.
typedef struct Attribute
{
	int8_t *name;
	DataType type;
} Attribute;

// This structure defines the layout and types of columns of
// any relation in the database. This is basically how we
// handle DDL commands.

typedef struct Schema
{
	int8_t *name;
	int8_t *fname;
	Attribute **atts;
	uint8_t natts;
} Schema;

Schema *schema_init();
void schema_add_att();

#endif
