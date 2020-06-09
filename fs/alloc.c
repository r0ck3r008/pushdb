#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"
#include"clogger/clogger.h"

extern Logger *logger;

Record *fs_record_alloc(int size)
{
	Record *rec=calloc(size, sizeof(Record));
	if(rec==NULL) {
		logger_msg(logger, LOG_ERR,
				"[-]Fs: Error in allocating Record!\n");
		_exit(-1);
	}

	return rec;
}

char *fs_char_alloc(char *prev, int size)
{
	char *ret;
	if(prev==NULL)
		ret=calloc(size, 1);
	else
		ret=realloc(prev, size);

	if(ret==NULL) {
		logger_msg(logger, LOG_ERR, "[-]Fs: Error in allocating!\n");
		_exit(-1);
	}

	return ret;
}

Page *fs_page_alloc()
{
	Page *pg=calloc(1, sizeof(PAGE_SIZE));
	if(pg==NULL) {
		logger_msg(logger, LOG_ERR,
			"[-]PAGE: Error in allocating the memory!\n");
		_exit(-1);
	}

	return pg;
}

File *fs_file_alloc()
{
	File *file=calloc(1, sizeof(File));
	if(file==NULL) {
		logger_msg(logger, LOG_ERR,
			"[-]FILE: Error in allocating file\n");
		_exit(-1);
	}

	return file;
}

char *fs_char_copy(char *str_in)
{
	char *str=strdup(str_in);
	if(str==NULL) {
		logger_msg(logger, LOG_ERR,
				"[-]Fs: Error in copying the string!\n");
		_exit(-1);
	}

	return str;
}
