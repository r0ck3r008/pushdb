#include<stdio.h>
#include<pthread.h>

#include"proj.h"

void *proj_run(void *arg)
{
	ProjOp *args=(ProjOp *)arg;

	pthread_exit(NULL);
}
