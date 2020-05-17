#include<check.h>

#include"fs/tests.h"

int main(int argc, char **argv)
{
	//fs
	Suite *rec_s=rec_suite();
	SRunner *fs_sr=srunner_create(rec_s);
	srunner_set_fork_status(fs_sr, CK_NOFORK);
	srunner_run_all(fs_sr, CK_NORMAL);


	srunner_free(fs_sr);
}
