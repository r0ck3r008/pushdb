#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"alloc.h"

char *handler_char_alloc(int size)
{
	char *ret=calloc(size, 1);
	if(ret==NULL) {
		fprintf(stderr, "[-]HANDLER: Error in allocating memory!\n");
		_exit(-1);
	}

	return ret;
}
