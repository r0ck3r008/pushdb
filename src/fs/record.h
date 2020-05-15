#ifndef RECORD_H
#define RECORD_H

#include<stdint.h>

#include"glbl/defs.h"
#include"db/schema.h"

typedef struct Record
{
	uint64_t mask;
	int8_t *bits;
} Record;

Record *record_ser(int8_t *, int8_t *, Schema *);
int8_t *record_deser(Record *, int8_t *, Schema *);

#endif
