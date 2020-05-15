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
	int8_t *att_name=strdup("att_name");
	Schema *sch=schema_init(sch_name, fname);
	for(int i=0; i<3; i++)
		schema_add_att(sch, att_name, (DataType)i);

	free(sch_name);
	free(fname);
	free(att_name);

	return sch;
}

START_TEST(SERIALIZATION_TEST)
{
	Schema *sch=prep_schema();
	int8_t *delimiter=strdup("|");
	int8_t *rec_str=strdup("1|1.02|Hello");
	Record *rec=record_ser(rec_str, delimiter, sch);
	int8_t *ret=record_deser(rec, delimiter, sch);
	ck_assert_str_eq(rec_str, ret);
	schema_deinit(sch);
	free(delimiter);
	free(rec_str);
	free(rec->bits);
	free(rec);
}
END_TEST

Suite *rec_suite(void)
{
	Suite *s=suite_create("RecordSuite");
	TCase *tc=tcase_create("Serialization/Deserialization");
	tcase_add_test(tc, SERIALIZATION_TEST);
	suite_add_tcase(s, tc);

	return s;
}
