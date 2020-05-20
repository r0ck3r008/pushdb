//#include "glbl/defs.h"
#include "record.h"
//linkedlist

typedef struct Node
{
	Record *val;
    struct Node *next;
} Node;

void create();
void addFirst (Record *t, Page *target);
void addLast (Record *t, Page *target);

//Page
typedef struct Page
{
    Node *last,*head;
    int curSizeInBytes;
    int numRecs;
} Page;
Page *myRecs;
void createPage ();
void ToBinary (int8_t *bits);
void FromBinary (int8_t *bits);

int GetFirst (Record *firstOne);
int get_curr_size();
int get_curr_recs();

//File
int fileOff;
int curPage;

void createFile();
//Returns the current length of the file in pages
off_t GetLength();

//Opens a File.
int Open(int length, const char *fName);

//Retreive a specific page from the file.
void GetPage();
//allows user to add a new page to the desired location (page number)
//in the file.
void AddPage();

//close the file
//returns 0 if an error exists and 1 on success.
int Close();
