#ifndef DDL_H
#define DDL_H

#include<stdint.h>

#include"db/schema.h"
#include"db/query.h"
#include"parser/parse_tree.h"

uint8_t ddl_create(Query *);
uint8_t ddl_insert(Query *);
uint8_t ddl_drop(Query *);

#endif
