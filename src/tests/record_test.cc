#include<iostream>
#include<gtest/gtest.h>
#include<stdlib.h>
#include<stdint.h>

#define _cpp

#include"glbl/defs.h"
#include"db/schema.h"
#include"fs/record.h"

Schema *prep_schema()
{
	char *sch_name=strdup("test_name");
	char *fname=strdup("dummy_fname");
	char *att_name=strdup("att_name");
	Schema *sch=schema_init((int8_t *)sch_name, (int8_t *)fname);
	for(int i=0; i<3; i++)
		schema_add_att(sch, (int8_t *)att_name, (DataType)i);

	free(sch_name);
	free(fname);
	free(att_name);

	return sch;
}

TEST(RECORD_TEST, SERIALIZATION_TEST)
{
	Schema *sch=prep_schema();
	char *delimiter=strdup("|");
	char *rec_str=strdup("1|1.02|Hello");
	Record *rec=record_ser((int8_t *)rec_str, (int8_t *)delimiter, sch);
	int8_t *ret=record_deser(rec, (int8_t *)delimiter, sch);
	ASSERT_TRUE(std::string(rec_str)==std::string((char *)ret));
	schema_deinit(sch);
	free(rec->bits);
	free(rec);
}
