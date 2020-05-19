#include<stdio.h>
#include<stdlib.h>

#include"tests.h"
#include"glbl/defs.h"
#include"db/schema.h"
#include"fs/record.h"

Schema *prep_schema()
{
	int8_t *sch_name=strdup("test_name");
	int8_t *fname=strdup("dummy_fname");
	Schema *sch=schema_init(sch_name, fname);
	schema_add_att(sch, "att1", 0, 0);
	schema_add_att(sch, "att2", 0, 1);
	schema_add_att(sch, "att3", 10, 2);

	free(sch_name);
	free(fname);

	return sch;
}

START_TEST(SERIALIZATION_TEST)
{
	// prep
	Schema *sch=prep_schema();
	int8_t *delimiter=strdup("|");
	int8_t *rec_str=strdup("1|1.010|Hello");
	Record *rec=record_ser(rec_str, delimiter, sch);
	int8_t *ret=record_deser(rec, delimiter, sch);

	//test
	ck_assert_str_eq(rec_str, ret);

	//exit
	schema_deinit(sch);
	free(delimiter);
	free(rec_str);
	free(rec->bits);
	free(rec);
}
END_TEST

Suite *rec_suite()
{
	Suite *s=suite_create("RecordSuite");
	TCase *tc=tcase_create("Serialization/Deserialization");
	tcase_add_test(tc, SERIALIZATION_TEST);
	suite_add_tcase(s, tc);

	return s;
}
