#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#include"clogger/clogger.h"
#include"dbf.h"

extern Logger *logger;
extern char *tmp_prefix;

Dbf *dbf_load(char *ins_fname, char *rel_name, Schema *sch)
{
	FILE *insf=NULL;
	if((insf=fopen(ins_fname, "w"))==NULL) {
		logger_msg(logger, LOG_ERR,
			"DBF: Fopen: %s: %s", ins_fname, strerror(errno));
		_exit(-1);
	}
}
