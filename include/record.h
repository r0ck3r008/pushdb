#ifndef RECORD_H
#define RECORD_H

#include<stdint.h>

#include"schema.h"
#include"attmap.h"
#include"defs.h"

typedef struct Record
{
	uint8_t bitmap[32];
	int8_t *bits;
} Record;

Record *record_ser(int8_t *, int8_t *, Schema *);
int8_t *record_deser(Record *, Schema *, int8_t *);

#endif
