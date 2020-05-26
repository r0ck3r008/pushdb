#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"alloc.h"

int8_t *handler_char_alloc(uint32_t size)
{
	int8_t *ret=calloc(size, 1);
	if(ret==NULL) {
		fprintf(stderr, "[-]HANDLER: Error in allocating memory!\n");
		_exit(-1);
	}

	return ret;
}
