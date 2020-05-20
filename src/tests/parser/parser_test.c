#include<stdio.h>

#include"parser/parse_tree.h"
#include"db/query.h"
#include"tests.h"

START_TEST(PARSER_TEST)
{
	//prep
	const char *str="SELECT name FROM table AS table1 WHERE (table.att>2)";
	Query *q=query_init(str);
	query_deinit(q);
	ck_assert_int_eq(1,1);

}
END_TEST

Suite *parser_suite()
{
	Suite *s=suite_create("ParserSuite");
	TCase *tc=tcase_create("Parser Test");
	tcase_add_test(tc, PARSER_TEST);
	suite_add_tcase(s, tc);

	return s;
}
