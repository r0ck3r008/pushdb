﻿#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include"alloc.h"
#include "file.h"

void addFirst (Record *t, Page *target)
{
	if(target->head == NULL){
		target->head = (struct Node*) malloc(sizeof(struct Node));
		target->last = (struct Node*) malloc(sizeof(struct Node));
		target->last = target->head;
		target->head->val = t;
		target->head->next = NULL;
		return;
	}
	Node* temp = (struct Node*) malloc(sizeof(struct Node));
	temp->val = t;
	temp->next = target->head;
	target->head = temp;
}

void addLast (Record *t, Page *target)
{
	if(target->head == NULL){
		target->head = (struct Node*) malloc(sizeof(struct Node));
		target->last = (struct Node*) malloc(sizeof(struct Node));
		target->last = target->head;
		target->head->val = t;
		target->head->next = NULL;
		return;
	}
	Node *temp = (struct Node*) malloc(sizeof(struct Node));
	temp->val = t;
	temp->next = NULL;
	target->last->next = temp;
	target->last = temp;
}

//Page
Page *createPage()
{
	Page *pg = calloc(1, sizeof(Page));
	if(pg==NULL) {
		fprintf(stderr, "[-]PAGE: Error in allocating the page!\n");
		_exit(-1);
	}
	return pg;
}

void EmptyItOut (Schema *target,Page *rec)
{
	// get rid of all of the records
	while (1) {
		Record temp;
		if (!GetFirst (&temp,target,rec))
			break;
	}

	// reset the page size
	rec->curSizeInBytes = sizeof (int);
	rec->numRecs = 0;
}

int Append (Record *rec, Schema *sch, Page *pg)
{
	uint32_t len = sch->map->tot_len;

	//check if the record can fit inside the page
	if((pg->curSizeInBytes + len ) > PAGE_SIZE)
		return 0;

	addLast(rec, pg);
	pg->numRecs++;
	return 1;
}

int GetFirst (Record *firstOne,Schema *target, Page *rec)
{
	if(rec->head == NULL){
		return 0;
	}
	Node *temp = rec->head;
	rec->head = rec->head->next;
	free(temp);
	int8_t *b = firstOne->bits;
	rec->curSizeInBytes -= target->map->tot_len;
	return 1;
}

void ToBinary (int8_t *bits, Schema *target, Page *rec)
{
	bits[0] = rec->numRecs;
	int8_t *curPos = bits + sizeof(int);

	//copy the records
	int i;
	Node *temp = rec->head;
	for(i = 0;i < rec->numRecs; i++) {
		int8_t *b = temp->val->bits;
		memcpy (curPos, b, target->map->tot_len);
		curPos += target->map->tot_len;
		temp = temp->next;
	}

}

void FromBinary (int8_t *bits, Schema *target, Page *rec)
{
	rec->numRecs = target->map->tot_len;
	int8_t* curPos = bits + sizeof (int);
	Node *temp = rec->head;
	while (temp!=NULL) {
		Node *temp1 = temp;
		free(temp);
		temp = temp->next;
	}
	Node *temp1;
	rec->curSizeInBytes = sizeof (int);
	int i;
	for(i=0;i<rec->numRecs;i++) {
		int len = curPos[0];
		rec->curSizeInBytes += len;
		memcpy (temp1->val->bits, bits, len);
		addLast(temp1,rec);
	}
	free(temp1);
}

// File
    
    int mode;
    if (fileLen == 0){
        mode = O_TRUNC | O_RDWR | O_CREAT;
    }else{
        mode = O_RDWR;
    }
    owner->fileOff = open (fName, mode, S_IRUSR | S_IWUSR);
    printf("file off is %d",owner->fileOff);
    if (owner->fileOff < 0) {
        fprintf(stderr, "BAD! Open did not work!");
        return 0;
    }
    if(fileLen != 0) {
        // read in the first few bits, which is the page size
        lseek (owner->fileOff,0,SEEK_SET);
        read (owner->fileOff, owner, sizeof(struct File));
    }else{
        owner->curPage = 0;
    }
    return 1;
}
void addPage(Page *addMe, off_t whichPage, File*owner, Schema *target) {
    //not skipping the first page since number of records will be there.
    //for addition at the end
    if(whichPage >= owner->curPage){
        off_t i;
        for(i = owner->curPage;i < whichPage;i++) {
            int foo = 0;
            lseek (owner->fileOff,PAGE_SIZE *i,SEEK_SET);
            write(owner->fileOff,&foo, sizeof(int));
        }
        owner->curPage = whichPage + 1;
    }

    //page writing
    char bits[PAGE_SIZE];
    if(bits == NULL) {
        printf("ERROR : Not enough memory. EXIT!!!\n");
        exit(1);
    }
    ToBinary(bits,target,addMe);
    lseek (owner->fileOff,PAGE_SIZE * whichPage, SEEK_SET);
    write(owner->fileOff, bits, PAGE_SIZE);
}
// void getPage (Page *putItHere, off_t  whichPage, File *owner, Schema *target) {
//     //write the the number of pages here.
//     //right now left as blank
//     //whichPage++;
//     if(whichPage >= owner->curPage) {
//         fprintf(stderr,"BAD : you tried to read past the end of the file\n");
//         exit(1);
//     }
//     char bits[PAGE_SIZE];
//     if(bits == NULL) {
//         printf("ERROR: Not enough memory. EXIT !!!\n");
//         exit(1);
//     }
//     lseek(owner->fileOff,PAGE_SIZE * whichPage, SEEK_SET);
//     read(owner->fileOff,bits, PAGE_SIZE);
//     FromBinary(bits,target, putItHere);
//     free(bits);
// }



// int Close (File *owner) {
//     lseek (&owner, 0, SEEK_SET);
// 	if(write (owner->fileOff, &owner, sizeof (struct File))==-1)
// 		return 0;

// 	// close the file
// 	if(close (owner))
// 		return 0;

// 	return 1;
// }

// Schema *prep_schema()
// {
// 	int8_t *sch_name=strdup("test_name");
// 	int8_t *fname=strdup("dummy_fname");
// 	Schema *sch=schema_init(sch_name, fname);
// 	schema_add_att(sch, "att1", 0, 0);
// 	schema_add_att(sch, "att2", 0, 1);
// 	schema_add_att(sch, "att3", 10, 2);

// 	free(sch_name);
// 	free(fname);

// 	return sch;
// }
// void main () {
//     Schema *sch=prep_schema();
// 	int8_t *delimiter=strdup("|");
//     int8_t *rec_str=strdup("1|1.010|Hello");
//     Schema *sch2 = prep_schema();
//     int8_t *rec_str2=strdup("1|1.010|World");
// 	Record *rec=record_ser(rec_str, delimiter, sch);
//     Record *rec2=record_ser(rec_str2, delimiter, sch2);
//     Page *try=NULL;
//     createPage(try);
//     Append(rec,sch,try);
// }
