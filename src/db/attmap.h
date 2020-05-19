#ifndef ATTMAP_H
#define ATTMAP_H
#define ATTMAP_SIZE 64

#include<stdint.h>

#include"glbl/defs.h"

typedef struct Attribute
{
	int8_t *name;
	DataType type;
	uint32_t pos;
	struct Attribute *nxt, *nxt_sq;
} Attribute;

typedef struct AttMap
{
	Attribute **map;
	Attribute *head, *tail;
	uint32_t tot_len;
} AttMap;

AttMap *attmap_init();
void attmap_deinit(AttMap *);
void attmap_add_att(AttMap *, int8_t *, DataType,
			uint32_t);
Attribute *attmap_find(AttMap *, int8_t *,
			uint32_t *);
uint32_t attribute_get_len(AttMap *, Attribute *);

#endif
