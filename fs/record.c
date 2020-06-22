#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"alloc.h"
#include"record.h"

Record *record_ser(char *_str, Schema *sch)
{
	char *str=fs_char_copy(_str);
	char *attr=strtok(str, sch->delim);
	Attribute *att=sch->map->head;
	Record *rec=fs_record_alloc(1);
	rec->bits=fs_char_alloc(NULL, sch->map->tot_len);

	while(att!=NULL && attr!=NULL) {
		if(att->type==Int) {
			((int *)rec->bits)[att->pos]=
					(int)strtol(attr, NULL, 10);
		} else if(att->type==Float) {
			((float *)rec->bits)[att->pos]=
					(float)strtof(attr, NULL);
		} else if(att->type==String) {
			int len=attribute_get_len(sch->map, att);
			strncat(&(((char *)rec->bits)[att->pos]), attr, len);
		}

		att=att->nxt_sq;
		attr=strtok(NULL, sch->delim);
	}

	free(str);
	return rec;
}

void record_deinit(Record *rec)
{
	free(rec->bits);
	free(rec);
}

char *record_deser(Record *rec, Schema *sch)
{
	char *str=fs_char_alloc(NULL, sch->map->tot_len);
	Attribute *curr=sch->map->head;
	while(curr!=NULL) {
		if(curr->type==Int) {
			sprintf(str, "%s%d",
				str, ((int *)rec->bits)[curr->pos]);
		} else if(curr->type==Float) {
			sprintf(str, "%s%.3f",
				str, ((float *)rec->bits)[curr->pos]);
		} else if(curr->type==String) {
			uint32_t len=attribute_get_len(sch->map, curr);
			strncat(str, &(((char *)rec->bits)[curr->pos]),
				len);
		}

		curr=curr->nxt_sq;
		if(curr!=NULL)
			sprintf(str, "%s%s", str, sch->delim);
	}

	return str;
}
