#include <sys/types.h>

#include"record.h"
#include"schema.h"
//Page
typedef struct Node
{
	Record *val;
    struct Node *next;
} Node;
typedef struct Page
{
    Node *last,*head;
    int curSizeInBytes;
    int numRecs;
} Page;


void addFirst (Record *, Page *);
void addLast (Record *, Page *);
Page *createPage ();
void ToBinary (int8_t *bits, Schema *target, Page *rec);
void FromBinary (int8_t *bits, Schema *target, Page *rec);
int Append (Record *addMe, Schema *target, Page *rec);
int GetFirst (Record *firstOne, Schema *target, Page *rec);
int get_curr_size();
int get_curr_recs();

//File
typedef struct File {
    int fileOff;
    int curPage;
} File;

//Returns the current length of the file in pages
off_t GetLength();

//Opens a File.
File *Open(const char *);

//Retreive a specific page from the file.
void getPage (Page *putItHere, off_t  whichPage, File *owner, Schema *target);
//allows user to add a new page to the desired location (page number)
//in the file.
void addPage(Page *addMe, off_t whichPage, File*owner, Schema *target);

//close the file
//returns 0 if an error exists and 1 on success.
int Close(File *owner);
