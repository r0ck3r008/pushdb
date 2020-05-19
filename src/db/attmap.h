#ifndef ATTMAP_H
#define ATTMAP_H

#include<stdint.h>

#include"glbl/defs.h"

#define ATTMAP_SIZE 16

typedef struct Attribute
{
	int8_t *name;
	DataType type;
	uint16_t len;
	struct Attribute *next;
} Attribute;

Attribute **attmap_init();
void attmap_deinit(Attribute **);
void attmap_add_att(Attribute **, int8_t *,
			DataType, uint16_t);
Attribute *attmap_find(Attribute **, int8_t *);

#endif
