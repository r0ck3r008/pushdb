#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"alloc.h"
#include"attmap.h"

uint8_t hash_it(int8_t *key)
{
	uint8_t indx=0;
	while(*key!='\0') {
		indx+=*key;
		key+=1;
	}

	return indx%ATTMAP_SIZE;
}

AttMap *attmap_init()
{
	AttMap *map=db_attmap_alloc();

	return map;
}

void attmap_deinit(AttMap *map)
{
	for(int i=0; i<ATTMAP_SIZE; i++) {
		if(map->map[i]!=NULL) {
			Attribute *curr=map->map[i]->nxt;
			while(map->map[i]->nxt!=NULL) {
				map->map[i]->nxt=curr->nxt;
				free(curr);
			}
			free(map->map[i]);
		}
	}
	free(map->map);
	free(map);
}

void attmap_add_att(AttMap *map, int8_t *aname, DataType type, uint32_t len)
{
	//create attribute
	uint16_t indx=hash_it(aname);
	Attribute *att=db_attribute_alloc();
	att->name=db_char_copy(aname);
	att->type=type;
	att->pos=map->tot_len;

	//update map
	if(map->head==NULL)
		map->head=att;
	else
		map->tail->nxt_sq=att;
	map->tail=att;
	if(map->map[indx]==NULL) {
		map->map[indx]=att;
	} else {
		Attribute *curr=map->map[indx];
		while(!(curr->nxt!=NULL && (curr=curr->nxt)));
		curr->nxt=att;
	}
	if(type==Int)
		map->tot_len+=sizeof(uint32_t);
	else if(type==Float)
		map->tot_len+=sizeof(float);
	else if(type==String)
		map->tot_len+=len;
}

uint32_t attribute_get_len(AttMap *map, Attribute *att)
{
	if(att!=NULL && att->type==String) {
		if(map->tail!=att)
			return ((att->nxt_sq->pos)-(att->pos));
		else
			return ((map->tot_len)-(att->pos));
	}

	return 0;

}

Attribute *attmap_find(AttMap *map, int8_t *name, uint32_t *len)
{
	uint16_t indx=hash_it(name);
	Attribute *curr=map->map[indx];
	if(curr!=NULL && curr->nxt!=NULL)
		while(!(curr!=NULL && strcmp(name, curr->name) &&
			(curr=curr->nxt)));

	*len=attribute_get_len(map, curr);

	return curr;
}
