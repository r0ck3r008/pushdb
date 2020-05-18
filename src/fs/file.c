#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "file.h"
// LinkedList functions
// Node *last,*head;
void create() {
    
}

void addFirst (int t){
    if(head == NULL){
        head = (struct Node*) malloc(sizeof(struct Node));
        last = (struct Node*) malloc(sizeof(struct Node));
        last = head;
        head->val = t;
        head->next = NULL;
        return;
    }
    Node* temp = (struct Node*) malloc(sizeof(struct Node));
    temp->val = t;
    temp->next = head;
    head = temp;
}

void addLast (int t)   {
    Node *temp = (struct Node*) malloc(sizeof(struct Node));
    temp->val = t;
    temp->next = NULL;
    last->next = temp;
    last = temp;
}
// //Page
// void create(){
//     curSizeInBytes = sizeof (int);
//     numRecs = 0;
//     myRecs = (struct Node*) malloc(sizeof(struct Node));
// }
// void FromBinary(char *bits){
//     numRecs = ((int *) bits)[0];
    
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