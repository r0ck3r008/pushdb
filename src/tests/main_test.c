#include<check.h>

#include"tests/fs/tests.h"

int main(int argc, char **argv)
{
	Suite *rec_s=rec_suite();
	SRunner *rec_sr=srunner_create(rec_s);
	srunner_set_fork_status(rec_sr, CK_NOFORK);

	srunner_run_all(rec_sr, CK_NORMAL);
	srunner_free(rec_sr);
}
