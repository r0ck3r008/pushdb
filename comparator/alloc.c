#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"clogger/clogger.h"
#include"alloc.h"

extern Logger *logger;

Cnf *comparator_cnf_alloc()
{
	Cnf *cnf=calloc(1, sizeof(Cnf));
	if(cnf==NULL) {
		logger_msg(logger, LOG_ERR,
				"COMPARE: Malloc: Error in allocating memory!");
		_exit(-1);
	}

	return cnf;
}

char *comparator_char_copy(char *_str)
{
	char *str=strdup(_str);
	if(str==NULL) {
		logger_msg(logger, LOG_ERR,
			"COMPARATOR: Malloc: Error in allocating memory!");
		_exit(-1);
	}

	return str;
}
