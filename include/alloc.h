#ifndef ALLOC_H
#define ALLOC_H

// TODO
// merge similar allocation functions like char

#include<stdint.h>

#include"record.h"
#include"query.h"
#include"schema.h"
#include"compare.h"
#include"page.h"
#include"file.h"

Record *fs_record_alloc(uint16_t);
int8_t *fs_char_alloc(int8_t *, uint16_t);
int8_t *fs_char_copy(int8_t *);
Page *fs_page_alloc();
File *fs_file_alloc();

// These functions exist just to check return
// status of malloc/strdup

int8_t *db_char_copy(int8_t *);
int8_t *db_char_alloc(uint32_t);
Schema *db_schema_alloc();
Attribute *db_attribute_alloc();
Attribute **db_attributep_alloc(uint8_t);
AttMap *db_attmap_alloc();
Query *db_query_alloc();

Cnf *comparator_cnf_alloc();

int8_t *handler_char_alloc(uint32_t);

#endif
