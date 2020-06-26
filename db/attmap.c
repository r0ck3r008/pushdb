#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"alloc.h"
#include"attmap.h"

int hash_it(char *key)
{
	int indx=0;
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
				free(curr->name);
				free(curr);
			}
			free(map->map[i]->name);
			free(map->map[i]);
		}
	}
	free(map->map);
	free(map);
}

void attmap_add_att(AttMap *map, char *aname, DataType type, int len)
{
	//create attribute
	int indx=hash_it(aname);
	Attribute *att=db_attribute_alloc();
	att->name=db_char_copy(aname);
	att->type=type;

	att->pos=map->tot_len;
	if(type==Int)
		att->len=sizeof(int);
	else if(type==Float)
		att->len=sizeof(float);
	else if(type==String)
		att->len=len;
	map->tot_len+=att->len;

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
}

Attribute *attmap_find(AttMap *map, char *name)
{
	int indx=hash_it(name);
	Attribute *curr=map->map[indx];
	if(curr!=NULL && curr->nxt!=NULL)
		while(!(curr!=NULL && strcmp(name, curr->name) &&
			(curr=curr->nxt)));

	return curr;
}
