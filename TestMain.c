#include "Project.h"

int main (int argc, char *argv[])
{
  Heap heap = newHeap();
  int i, one = 1, two = 2, three = 3;
  Entry temp;

  addValuesToHeap(&heap, &one, 1);
  addValuesToHeap(&heap, &two, 2);
  addValuesToHeap(&heap, &three, 3);

  for (i = 0; i < 3; i++)
  {
    temp = pop(&heap);
    printf("%d\n", temp.item[0]);
  }

  return 0;
}
