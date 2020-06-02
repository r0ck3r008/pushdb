#ifndef ALLOC_H
#define ALLOC_H

// TODO
// merge similar allocation functions like char

#include"record.h"
#include"query.h"
#include"schema.h"
#include"compare.h"
#include"page.h"
#include"file.h"

Record *fs_record_alloc(int);
char *fs_char_alloc(char *, int);
char *fs_char_copy(char *);
Page *fs_page_alloc();
File *fs_file_alloc();

// These functions exist just to check return
// status of malloc/strdup

char *db_char_copy(char *);
char *db_char_alloc(int);
Schema *db_schema_alloc();
Attribute *db_attribute_alloc();
Attribute **db_attributep_alloc(int);
AttMap *db_attmap_alloc();
Query *db_query_alloc();

Cnf *comparator_cnf_alloc();

char *handler_char_alloc(int);

#endif
