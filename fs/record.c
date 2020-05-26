#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"alloc.h"
#include"record.h"

Record *record_ser(int8_t *_str, int8_t *delim, Schema *sch)
{
	int8_t *str=fs_char_copy(_str);
	int8_t *attr=strtok(str, delim);
	Attribute *att=sch->map->head;
	Record *rec=fs_record_alloc(1);
	rec->bits=fs_char_alloc(NULL, sch->map->tot_len);

	while(att!=NULL && attr!=NULL) {
		if(att->type==Int) {
			((uint32_t *)rec->bits)[att->pos]=
					(uint32_t)strtol(attr, NULL, 10);
		} else if(att->type==Float) {
			((float *)rec->bits)[att->pos]=
					(float)strtof(attr, NULL);
		} else if(att->type==String) {
			uint32_t len=attribute_get_len(sch->map, att);
			strncat(&(((int8_t *)rec->bits)[att->pos]),
						attr, len);
		}

		att=att->nxt_sq;
		attr=strtok(NULL, delim);
	}

	free(str);
	return rec;
}

int8_t *record_deser(Record *rec, Schema *sch, int8_t *delim)
{
	int8_t *str=fs_char_alloc(NULL, sch->map->tot_len);
	Attribute *curr=sch->map->head;
	while(curr!=NULL) {
		if(curr->type==Int) {
			sprintf(str, "%s%d",
				str, ((uint32_t *)rec->bits)[curr->pos]);
		} else if(curr->type==Float) {
			sprintf(str, "%s%.3f",
				str, ((float *)rec->bits)[curr->pos]);
		} else if(curr->type==String) {
			uint32_t len=attribute_get_len(sch->map, curr);
			strncat(str, &(((int8_t *)rec->bits)[curr->pos]),
				len);
		}

		curr=curr->nxt_sq;
		if(curr!=NULL)
			sprintf(str, "%s%s", str, delim);
	}

	return str;
}
