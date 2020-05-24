#include<check.h>

#include"fs/tests.h"
#include"parser/tests.h"

int main(int argc, char **argv)
{
	//fs
	Suite *rec_s=rec_suite();
	SRunner *fs_sr=srunner_create(rec_s);
	srunner_set_fork_status(fs_sr, CK_NOFORK);
	srunner_run_all(fs_sr, CK_NORMAL);

	//parser
	Suite *parse_s=parser_suite();
	SRunner *parser_sr=srunner_create(parse_s);
	srunner_set_fork_status(parser_sr, CK_NOFORK);
	srunner_run_all(parser_sr, CK_NORMAL);

	srunner_free(fs_sr);
	srunner_free(parser_sr);
}
