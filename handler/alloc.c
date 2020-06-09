#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"alloc.h"
#include"clogger/clogger.h"

extern Logger *logger;

char *handler_char_alloc(int size)
{
	char *ret=calloc(size, 1);
	if(ret==NULL) {
		logger_msg(logger, LOG_ERR,
				"[-]HANDLER: Error in allocating memory!\n");
		_exit(-1);
	}

	return ret;
}
