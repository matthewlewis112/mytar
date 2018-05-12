#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Entry
{
  int *item;
  int priority;
} Entry;

typedef struct Heap
{
  int size;
  Entry *head;
} Heap;

enum bool {FALSE, TRUE};

//Heap functions
extern void swap(Entry *one, Entry *two);

extern void heapify(Heap h);

extern void addValuesToHeap(Heap *h, void *i, int p);

extern void addToHeap(Heap *h, Entry e);

extern Entry pop(Heap *h);

extern Heap newHeap();

//Parsing Functions

extern int isVerbose(char *argv);

extern int isStrict(char *argv);

extern int lookForChar(char *argv, char l);

//Archive functions

extern void createArchive(bool isVerbsoe, bool isStrict, char *argv);

extern void listArchiveTable(bool isVerbsoe, bool isStrict, char *argv);
