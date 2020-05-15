#include<check.h>

#include"tests/fs/tests.h"

int main(int argc, char **argv)
{
	Suite *s=rec_suite();
	SRunner *sr=srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	srunner_free(sr);
}
