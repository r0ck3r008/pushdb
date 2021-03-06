#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"defs.h"
#include"compare.h"
#include"clogger/clogger.h"

extern Logger *logger;

int compare_cnf_exec(Cnf *cnf, Record *rec1)
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

	ret=compare_cnf_exec(cnf, rec);

exit:
	return ret;
}

int compare_lr(Cnf *cnf, Record *rec1, Record *rec2)
{
	int pos1=cnf->att1->pos, pos2=cnf->att2->pos, ret=0;
	DataType type=cnf->att1->type;

	if(type==Int) {
		int val1=((int  *)rec1->bits)[pos1],
			val2=((int *)rec2->bits)[pos2];
		if(val1<val2)
			ret=-1;
		else if(val1>val2)
			ret=1;
	} else if(type==Float) {
		float val1=((float *)rec1->bits)[pos1],
			val2=((float *)rec2->bits)[pos2];
		if(val1<val2)
			ret=-1;
		else if(val1>val2)
			ret=1;
	} else if(type==String) {
		char *val1=&(((char *)rec1->bits)[pos1]),
			*val2=&(((char *)rec2->bits)[pos2]);
		int stat=strncmp(val1, val2, cnf->att1->len);
		if(stat<0)
			ret=-1;
		else if(stat>0)
			ret=1;
	}

	return ret;
}
