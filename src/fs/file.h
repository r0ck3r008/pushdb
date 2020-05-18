//#include "glbl/defs.h"
#include "record.h"
//linkedlist

typedef struct Node
{
	int val;
    struct Node *next;
} Node;
Node *last,*head;
void create();
void addFirst (int t);
void addLast (int t);

//Page
int curSizeInBytes;
int numRecs;
Node *myRecs;
void createPage ();
void ToBinary (char *bits);
void FromBinary (char *bits);

int GetFirst (Record *firstOne);
int get_curr_size();
int get_curr_recs();

//File
int fileOff;
int curPage;

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
