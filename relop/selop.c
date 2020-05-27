#include<stdio.h>
#include<pthread.h>

#include"compare.h"
#include"selop.h"

void *selop_run(void *arg)
{
	SelOp *args=(SelOp *)arg;
	Cnf *cnf=cnf_init_ll(args->sch, args->alist);

	pthread_exit(NULL);
}
