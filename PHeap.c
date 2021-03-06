#include "Project.h"

void swap(Entry *one, Entry *two)
{
  Entry temp = *one;
  *one = *two;
  *two = temp;
}

void heapify(Heap h)
{
  int i;
  for(i = h.size -1; i > 0; i--)
  {
    if (h.head[i/2].priority < h.head[i].priority)
      swap(h.head + i/2, h.head + i);
  }
}

void addValuesToHeap(Heap *h, void *i, int p)
{
  Entry e;
  e.item = i;
  e.priority = p;
  addToHeap(h, e);
}

void addToHeap(Heap *h, Entry e)
{
  h -> head = realloc(h -> head, sizeof(Entry) * (h -> size + 1));
  h -> size += 1;
  h -> head[h -> size - 1] = e;
  heapify(*h);
}

Entry pop(Heap *h)
{
  Entry e;
  int i;
  e = *(h -> head);
  for(i = 1; i < h -> size; i++)
  {
    swap(h-> head + i -1, h-> head + i);
  }
  h -> size -= 1;
  h -> head = realloc(h -> head, sizeof(Entry) * (h -> size));
  heapify(*h);
  return e;
}

Heap newHeap()
{
  Heap h;
  h.head = NULL;
  h.size = 0;
  return h;
}
