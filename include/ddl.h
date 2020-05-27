#ifndef DDL_H
#define DDL_H

#include<stdint.h>

#include"schema.h"
#include"query.h"
#include"parse_tree.h"

uint8_t ddl_create(Query *);
uint8_t ddl_insert(Query *);
uint8_t ddl_drop(Query *);

#endif
