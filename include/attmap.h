#ifndef ATTMAP_H
#define ATTMAP_H
#define ATTMAP_SIZE 64

#include<stdint.h>

#include"defs.h"

typedef struct Attribute
{
	char *name;
	DataType type;
	int len, pos;
	struct Attribute *nxt, *nxt_sq;
} Attribute;

typedef struct AttMap
{
	Attribute **map;
	Attribute *head, *tail;
	int tot_len;
} AttMap;

AttMap *attmap_init();
void attmap_deinit(AttMap *);
void attmap_add_att(AttMap *, char *, DataType, int);
Attribute *attmap_find(AttMap *, char *);

#endif
