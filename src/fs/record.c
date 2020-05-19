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
	Record *rec=fs_record_alloc(sch->map->tot_len+sizeof(uint16_t));

	while(att!=NULL && attr!=NULL) {
		if(att->type==Int) {
			((uint16_t *)rec->bits)[att->pos]=
					(uint16_t)strtol(attr, NULL, 10);
		} else if(att->type==Float) {
			((float *)rec->bits)[att->pos]=
					(float)strtof(attr, NULL);
		} else if(att->type==String) {
			uint16_t len=attribute_get_len(sch->map, att);
			strncat(&(((int8_t *)rec->bits)[att->pos]),
						attr, len);
		}

		att=att->nxt_sq;
		attr=strtok(NULL, delim);
	}

	((uint16_t *)rec->bits)[0]=sch->map->tot_len;
	free(str);

	return rec;
}
