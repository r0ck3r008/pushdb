#ifndef DDL_H
#define DDL_H

#include"db/query.h"

int ddl_create(Query *);
int ddl_insert(Query *);
int ddl_drop(Query *);

#endif
