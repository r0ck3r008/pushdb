#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include"alloc.h"
#include"record.h"

Record *record_ser(int8_t *_str, int8_t *delimiter, Schema *sch)
{
	Record *rec=fs_record_alloc();
	rec->bits=fs_char_alloc(NULL, 1024);
	uint8_t n=sch->natts;
	// leave space for record size
	uint16_t ptr=sizeof(uint16_t);
	// begin splitting
	int8_t *str=fs_char_copy(_str);
	int8_t *attr=strtok(str, delimiter);

	for(uint8_t i=0, j=1; i<n; i++) {
		if(ptr>=(uint16_t)(1024*(j)*(0.1))) {
			rec->bits=fs_char_alloc(rec->bits, 1024*(++j));
			i--;
			continue;
		}

		if(sch->atts[i]->type==Int) {
			((uint16_t *)rec->bits)[ptr]=(uint16_t)strtol(attr,
								NULL, 10);
			ptr+=sizeof(uint16_t);
		} else if(sch->atts[i]->type==Float) {
			((float *)rec->bits)[ptr]=(float)strtof(attr, NULL);
			ptr+=sizeof(float);
		} else if(sch->atts[i]->type==String) {
			strncat(&((int8_t *)rec->bits)[ptr], attr,
							sch->atts[i]->len);
			ptr+=strlen(attr);
		} else {
			fprintf(stderr, "[-]Serialize: Bad attribute type!\n");
			_exit(-1);
		}
		attr=strtok(NULL, delimiter);
	}

	// Fill out the size
	((uint16_t *)rec->bits)[0]=ptr;
	free(str);

	return rec;
}

int8_t *record_deser(Record *rec, int8_t *delimiter, Schema *sch)
{
	uint16_t rec_sz=((uint16_t *)rec->bits)[0];
	uint16_t ptr=sizeof(uint16_t);
	int8_t *ret=fs_char_alloc(NULL, rec_sz);
	uint8_t n=sch->natts;
	for(uint8_t i=0; i<n; i++) {
		if(sch->atts[i]->type==Int) {
			sprintf(ret, "%s%d", ret, ((uint16_t *)rec->bits)[ptr]);
			ptr+=sizeof(uint16_t);
		} else if(sch->atts[i]->type==Float) {
			sprintf(ret, "%s%.3f", ret, ((float *)rec->bits)[ptr]);
			ptr+=sizeof(float);
		} else if(sch->atts[i]->type==String) {
			strncat(ret, &((int8_t *)rec->bits)[ptr],
							sch->atts[i]->len);
			ptr+=sch->atts[i]->len;
		} else {
			fprintf(stderr, "[-]Deserealize: Bad Attribute type!\n");
			_exit(-1);
		}
		if(i!=n-1)
			strncat(ret, delimiter, 1);
	}

	return ret;
}
