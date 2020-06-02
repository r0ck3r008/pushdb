#ifndef DDL_H
#define DDL_H

#include<stdint.h>

#include"schema.h"
#include"query.h"
#include"parse_tree.h"

int ddl_create(Query *);
int ddl_insert(Query *);
int ddl_drop(Query *);

#endif
