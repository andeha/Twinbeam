/*  couvert-antagni.c | list process and early gathered. */

#include "twinbeam-inner.h"

union cell₋continuation { Conscell * next; __builtin_uint_t 
 possibly₋maybe; };

struct cons₋cell { Material * item; union cell₋continuation nxt; };

typedef struct cons₋cell Cons₋cell;

int append₋at₋end(int count, void (^augment)(int count, Material ** 
 uninited₋sometime), Conscell ** first, Conscell ** last, 
 int sizeof₋material) ⓣ
{ int i=0; struct cons₋cell *memory,*element₋last; 
   Material * collect[count];
again:
   if (i >= count) goto unagain;
   memory = (Cons₋cell *)*last;
   element₋last = Cons₋alloc(sizeof(Conscell *) + sizeof(Material *));
   element₋last->item = Heap₋alloc(sizeof₋material);
   collect[i] = element₋last->item;
   if (memory) memory->nxt.next = element₋last;
   *last = element₋last;
   if (*first == 0) *first = memory;
   i+=1; goto again;
unagain:
   if (augment) augment(count,collect);
   return 0;
}

int unqueue(int count, void (^removed)(int count, Material ** 
 snapshot₋sometime), Conscell ** first, Conscell ** last) ⓣ
{ int i=0; Material * collect[count];
   Cons₋cell ** First=(Cons₋cell **)first;
again:
   if (i >= count) goto unagain;
   if (*first == 0) goto unagain;
   collect[i] = (*First)->item;
   Cons₋fallow(*First);
   *first = (*First)->nxt.next;
   i+=1; goto again;
unagain:
   if (removed) removed(i,collect);
   return 0;
}

int rollback₋pop(void (^scalar)(Material * snapshot₋sometime), Conscell ** 
 first, Conscell ** last) ⓣ
{ Cons₋cell * select = *(Cons₋cell **)first, *deleted;
   if (select == 0) return -1;
   if (*last == *first) { deleted=select,*first=0,*last=0; goto unagain; }
again:
   if (select->nxt.next == *last) { *last=select; goto unagain; }
   select = select->nxt.next; goto again;
unagain:
   scalar(deleted);
   return 0;
}

void recollect(void (^item)(Material *,int), Conscell * first, 
 Conscell * last) ⓣ
{ Cons₋cell * select = (Cons₋cell *)first; int index=0;
again:
   if (select == 0) goto unagain;
   item(select->item,index);
   select = select->nxt.next;
   index+=1; goto again;
unagain:
   return;
}

int is₋empty(Conscell * first, Conscell * last) ⓣ
{
   return first == 0 && last == 0;
}

int uninit₋list(void (^removed)(Material *, Material **), Conscell * first, 
 Conscell * last, Material ** address₋of₋next) ⓣ
{ Cons₋cell * select = (Cons₋cell *)first;
again:
   if (select == 0) goto unagain;
   Heap₋unalloc(select);
   if (removed) removed(select->item,address₋of₋next);
   select = select->nxt.next;
   goto again;
unagain:
   return 0;
}

