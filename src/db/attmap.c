#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"alloc.h"
#include"attmap.h"

uint8_t attmap_hash_it(int8_t *name)
{
	uint8_t indx=0;
	while(*name!='\0') {
		indx+=*name;
		name+=1;
	}

	return indx%ATTMAP_SIZE;
}

Attribute **attmap_init()
{
	Attribute **map=db_attributep_alloc(ATTMAP_SIZE);
	return map;
}

void attmap_add_att(Attribute **map, int8_t *name, DataType type,
			uint16_t len)
{
	uint8_t indx=attmap_hash_it(name);
	Attribute *attr=db_attribute_alloc();
	attr->name=db_char_copy(name);
	attr->type=type;
	attr->len=len;
	if(map[indx]==NULL) {
		map[indx]=attr;
	} else {
		Attribute *curr=map[indx];
		while(!(curr->next!=NULL && (curr=curr->next)));
		curr->next=attr;
	}
}

Attribute *attmap_find_att(Attribute **map, int8_t *name)
{
	uint8_t indx=attmap_hash_it(name);
	Attribute *curr=map[indx];
	if(curr!=NULL && curr->next!=NULL)
		while(!(curr->next!=NULL && (curr=curr->next)));

	return curr;
}

void attmap_deinit(Attribute **map)
{
	for(int i=0; i<ATTMAP_SIZE; i++) {
		if(map[i]->next!=NULL) {
			Attribute *curr=map[i]->next;
			while(map[i]->next!=NULL) {
				map[i]->next=curr->next;
				free(curr);
			}
		}
		free(map[i]);
	}

	free(map);
}
