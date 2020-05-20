#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "file.h"
// LinkedList functions
void create() {
    
}

void addFirst (Record *t, Page *target){
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

void addLast (Record *t, Page *target)   {
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
void create(){
    myRecs = (struct Page*) malloc(sizeof(struct Page));
    myRecs->curSizeInBytes = sizeof (int);
    myRecs->numRecs = 0;
}
void EmptyItOut () {

	// get rid of all of the records
	while (1) {
		Record temp;
		if (!GetFirst (&temp))
			break;
	}

	// reset the page size
	myRecs->curSizeInBytes = sizeof (int);
	myRecs->numRecs = 0;
}

int Append (Record *addMe){
    int8_t *b = addMe->bits;

    //check if the record can fit inside the page
    if(myRecs->curSizeInBytes + b[0] > PAGE_SIZE) {
        return 0;
    }

    addLast(addMe,myRecs);
    myRecs->numRecs++;
    return 1;
}

int GetFirst (Record *firstOne) {
    if(myRecs->head == NULL){
        return 0;
    }
    Node *temp = myRecs->head;
    myRecs->head = myRecs->head->next;
    free(temp);
    int8_t *b = firstOne->bits;
    myRecs->curSizeInBytes -= b[0];
    return 1;
}

void ToBinary (int8_t *bits) {
    bits[0] = myRecs->numRecs;
    int8_t *curPos = bits + sizeof(int);

    //copy the records
    int i; 
    Node *temp = myRecs->head;
    for(i = 0;i < myRecs->numRecs; i++) {
        int8_t *b = temp->val->bits;
        memcpy (curPos, b, b[0]);
		curPos += b[0];
        temp = temp->next;
    }  

}

void FromBinary (int8_t *bits) {
    myRecs->numRecs = bits[0];
    char *curPos = bits + sizeof (int);
    Node *temp = myRecs->head;
    while (temp!=NULL) {
        Node *temp1 = temp;
        free(temp);
        temp = temp->next;
    }
}

//File
// void createFile () {
//     fileOff = 0;
//     curPage = 0;
// }
// void getPage (Page *putItHere, off_t  whichPage) {

// }
// void main () {
//     create();
//     addFirst(2);
//     addLast(3);
//     addLast(4);
//     addFirst(100);
//     Node *temp = head;
//     while(temp!=NULL){
//         printf("%d ", temp->val);
//         temp = temp->next;
//     }
// }