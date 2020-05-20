#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "db/schema.h"
// LinkedList functions
void create() {
    
}

void addFirst (Record *t, Page *target) {
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

void addLast (Record *t, Page *target) {
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
void create(Page *rec){
    rec = (struct Page*) malloc(sizeof(struct Page));
    rec->curSizeInBytes = sizeof (int);
    rec->numRecs = 0;
}
void EmptyItOut (Schema *target,Page *rec) {

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

int Append (Record *addMe, Schema *target, Page *rec){
    uint32_t *b = target->map->tot_len;

    //check if the record can fit inside the page
    if(rec->curSizeInBytes + b > PAGE_SIZE) {
        return 0;
    }

    addLast(addMe,rec);
    rec->numRecs++;
    return 1;
}

int GetFirst (Record *firstOne,Schema *target, Page *rec) {
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

void ToBinary (int8_t *bits, Schema *target, Page *rec) {
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

void FromBinary (int8_t *bits, Schema *target, Page *rec) {
    rec->numRecs = target->map->tot_len;
    char *curPos = bits + sizeof (int);
    Node *temp = rec->head;
    while (temp!=NULL) {
        Node *temp1 = temp;
        free(temp);
        temp = temp->next;
    }

}

// File
void createFile (File *fName) {
    fName->fileOff = 0;
    fName->curPage = 0;
}
void getPage (Page *putItHere, off_t  whichPage, File *owner, Schema *target) {
    //write the the number of pages here.
    //right now left as blank
    whichPage++;
    if(whichPage >= owner->curPage) {
        fprintf(stderr,"BAD : you tried to read past the end of the file\n");
        exit(1);
    }
    char bits[PAGE_SIZE];
    if(bits == NULL) {
        printf("ERROR: Not enough memory. EXIT !!!\n");
        exit(1);
    }
    lseek(owner->fileOff,PAGE_SIZE * whichPage, SEEK_SET);
    read(owner->fileOff,bits, PAGE_SIZE);
    FromBinary(bits,target, putItHere);
    free(bits);
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
    Tobinary(bits,target,addMe);
    lseek (owner->fileOff,PAGE_SIZE * whichPage, SEEK_SET);
    write(owner->fileOff, bits, PAGE_SIZE);
    free(bits);
}
int Open (int fileLen, const char* fName,File *owner) {
    int mode;
    if (fileLen = 0){
        mode = O_TRUNC | O_RDWR | O_CREAT;
    }else{
        mode = O_RDWR;
    }
    owner->fileOff = open (fName, mode, S_IRUSR | S_IWUSR);
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

int Close (File *owner) {
    lseek (owner, 0, SEEK_SET);
	if(write (owner->curPage, owner, sizeof (struct File))==-1)
		return 0;

	// close the file
	if(close (owner))
		return 0;

	return 1;
}

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