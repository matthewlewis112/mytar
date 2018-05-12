#include <stdlib.h>
#include <stdio.h>

typedef struct Entry
{
  void *item;
  int priority;
} Entry;

typedef struct Heap
{
  int size;
  Entry *head;
} Heap;
