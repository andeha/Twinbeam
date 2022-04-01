/*  task-modern.c | missing pieces for one an-scheduler. 'fiber' */

import Twinbeam;

typedef struct __coro_t * ϵ₋int₁;
typedef int (*Coroutine)(ϵ₋int₁ coro);
/* ...and neither 'typedef coro_t ϵ₋int₁;'' nor 'typedef ϵ₋int₁ (*Coroutine)(void * ctx);'. */
/* a.k.a 'indirekt alternativt direkt' eqivalent-with 'endera'. */

struct Necklace { ϵ₋int₁ task; struct Necklace * prv, *nxt; };

extern void * hw₋collection; /* ⬷ a․𝘬․a map irq₋no × Coroutine₋task. */
extern struct Necklace *curr;
/* ⬷ memory-space in 'small' defined in --<℮ ia64+pic32rt>--<llvm-rt3.c>. */

int Schedule(Coroutine task, ALLOC alloc)
{
   coro_t * coro = coro_await(task);
   struct Necklace * box = (Necklace *)alloc(sizeof(Necklace));
   if (box == ΨΛΩ) { return -1; }
   box->task = coro;
   box->prv = box->nxt = ΨΛΩ;
   if (curr == ΨΛΩ) { curr = box; }
   box->prv = curr->prv;
   curr->prv = box;
   box->nxt = curr;
   return 0;
}

#pragma header interrupts

int timer₋fired(ϵ₋int₁ coro)
{
   coro_feedback(coro,1);
   while (1) {
     mprint("timer fired");
     if (curr == ΨΛΩ) { coro_feedback(coro,2); }
     curr = curr->nxt;
     coro_resume(curr->task);
     coro_feedback(coro,3);
   }
   return 0;
}

int Recognize₋and₋start(unsigned ﹟irq, Coroutine task, ALLOC alloc)
{
   coro_t * coro = coro_await(task);
#if defined __mips__ || defined __armv6__ || defined espressif
   int32_t key = (int32_t)﹟irq;
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
   int64_t key = (int64_t)﹟irq;
#endif
   Treeint valkey = { .keyvalue = { key, (__builtin_uint_t)coro } };
   hw₋collection = Insert(hw₋collection,valkey,alloc);
   if (hw₋collection == ΨΛΩ) { return -1; }
   return 0;
}

FOCAL void Process(unsigned ﹟irq)
{
#if defined __mips__ || defined __armv6__ || defined espressif
   int32_t key = (int32_t)﹟irq;
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
   int64_t key = (int64_t)﹟irq;
#endif
   struct Treeint valkey = { .keyvalue = { key, 0x0 } };
   struct Treeint * leaf = Lookup(hw₋collection,valkey);
   coro_t * coro = (coro_t *)(leaf->keyvalue.val);
   coro_resume(coro); /* Resume(coroutine->coroutine.address()) */
}

#pragma header commence operational

int Initserviceinterrupt()
{ hw₋collection=ΨΛΩ; int Timer1=17;
   if (Recognize₋and₋start(Timer1,timer₋fired,Heap₋alloc)) { return -1; }
   return 0;
}

void Initscheduler()
{ curr = ΨΛΩ; }

#pragma header operation

int hello₋world(ϵ₋int₁ coro)
{
   coro_feedback(coro,1);
   while (1) {
     print("hello ");
     coro_feedback(coro,2);
   }
   return 0;
}

int main()
{ Initserviceinterrupt();
   Initscheduler();
   if (Schedule(hello₋world,Heap₋alloc)) { return 1; }
   while (1) { wait; }
   return 0;
}
