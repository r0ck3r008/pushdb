#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"

Record *fs_record_alloc()
{
	Record *rec=malloc(sizeof(Record));
	if(rec==NULL) {
		fprintf(stderr, "[-]Fs: Error in allocating Record!\n");
		_exit(-1);
	}

	return rec;
}

int8_t *fs_char_alloc(int8_t *prev, uint16_t size)
{
	int8_t *ret;
	if(prev==NULL)
		ret=calloc(size, 1);
	else
		ret=realloc(prev, size);

	if(ret==NULL) {
		fprintf(stderr, "[-]Fs: Error in allocating!\n");
		_exit(-1);
	}

	return ret;
}

int8_t *fs_char_copy(int8_t *str_in)
{
	int8_t *str=strdup(str_in);
	if(str==NULL) {
		fprintf(stderr, "[-]Fs: Error in copying the string!\n");
		_exit(-1);
	}

	return str;
}
