#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"compare.h"
#include"clogger/clogger.h"

extern Logger *logger;

int compare_cnf_exec(Cnf *cnf, Record *rec1, Record *rec2)
{
	int ret=0, pos=cnf->att1->pos;

	if(cnf->type==INT_COMP) {
		int val=((int *)rec1->bits)[pos];
		ret=(cnf->ival==val) ? (1) : (0);
	} else if(cnf->type==FLOAT_COMP) {
		float val=((float *)rec1->bits)[pos];
		ret=(cnf->fval==val) ? (1) : (0);
	} else if(cnf->type==STR_COMP) {
		char *val=&(((char *)rec1->bits)[pos]);
		ret=(!strncmp(cnf->sval, val, cnf->att1->len)) ? (1) : (0);
	} else if(cnf->type==ATT_COMP) {
		// TODO
		// Implement rec-rec comparison here!
		logger_msg(logger, LOG_WRN,
				"Record comparison unimplemented!");
		_exit(-1);
	}
	return ret;
}

{

}
