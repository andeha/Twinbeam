/*  ❩† malloc.c | store in single-linked list. */

#include <Twinbeam.h>

CORRECT(dynamically_allocated_1)
{
   void * material = Heap₋alloc(100);
   Free₋heap(material);
}

