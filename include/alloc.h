#ifndef ALLOC_H
#define ALLOC_H

// TODO
// merge similar allocation functions like char

#include"record.h"
#include"query.h"
#include"schema.h"
#include"page.h"
#include"file.h"
#include"fcache.h"
#include"cnf.h"

Record *fs_record_alloc(int);
char *fs_char_alloc(char *, int);
char *fs_char_copy(char *);
Page *fs_page_alloc();
File *fs_file_alloc();

char *db_char_copy(char *);
char *db_char_alloc(int);
Schema *db_schema_alloc();
Attribute *db_attribute_alloc();
Attribute **db_attributep_alloc(int);
AttMap *db_attmap_alloc();
Query *db_query_alloc();

char *handler_char_alloc(int);

Cnf *comparator_cnf_alloc();
char *comparator_char_copy(char *);

#endif
