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

int compare_l(Cnf *cnf, Record * rec)
{
	int ret=1;

	if(cnf->dwn!=NULL) {
		ret=compare_l(cnf->dwn, rec);
		if(ret && cnf->nxt==NULL)
		// Since this cnf is being Or'd and one of the Or'd Cnf has
		// returned 1, we can skip all remaining ones and short circuit.
			goto exit;
	}

	if(cnf->nxt!=NULL) {
		ret=compare_l(cnf->nxt, rec);
		if(!ret)
		// Since this cnf is being And'd and one of the Cnfs has
		// returned 0, we can skip all others and return false by short
		// circuting.
			goto exit;
	}

	ret=compare_cnf_exec(cnf, rec, NULL);

exit:
	return ret;
}

int compare_lr(Cnf *cnf, Record *rec1, Record *rec2)
{
	return compare_cnf_exec(cnf, rec1, rec2);
}
