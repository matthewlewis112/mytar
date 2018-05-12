#include <stdlib.h>
#include <stdio.h>

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

//Heap functions
extern void swap(Entry *one, Entry *two);

extern void heapify(Heap h);

extern void addValuesToHeap(Heap *h, void *i, int p);

extern void addToHeap(Heap *h, Entry e);

extern Entry pop(Heap *h);

extern Heap newHeap();
