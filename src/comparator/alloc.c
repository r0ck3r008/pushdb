#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"alloc.h"

Cnf *comparator_cnf_alloc()
{
	Cnf *cnf=malloc(sizeof(Cnf));
	if(cnf==NULL) {
		fprintf(stderr, "[-]Cnf: Error in allocating memory!\n");
		_exit(-1);
	}

	return cnf;
}
