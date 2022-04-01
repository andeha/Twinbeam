/*  ketterer-order.c a․𝘬․a wrongfox-hallå.c | soft-war-an notifies and interrupts. */

import Twinbeam;

void * sw₋signal, *context₋semantic;

int Sustain₋entrust(int32_t signal, void * semantic)
{
   union Treeint leafkey = { signal, 0 };
   union Treeint * node = Lookup(sw₋signal,leafkey);
   if (node == ΨΛΩ) { return -2; }
   ϵ₋int₁ coro = (coro_t *)node->keyvalue.key;
   context₋semantic = semantic;
   if (coro_resume(coro)) { return -1; }
   return 0;
}

int Initiate₋inform(int32_t signal, Coroutine coroutine, ALLOC alloc)
{
   ϵ₋int₁ /* coro_t * */ coro = coro₋await(coroutine);
#if defined __mips__ || defined __armv6__ || defined espressif
   Treeint leafkey = { .keyvalue = { signal, (uint32_t)coro } };
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
   Treeint leafkey = { .keyvalue = { signal, (uint64_t)coro } };
#endif
   void * unchanged = Insert(sw₋signal,leafkey,alloc);
   if (unchanged == ΨΛΩ) { return -1; }
   if (sw₋signal == ΨΛΩ) { sw₋signal = unchanged; }
   return 0;
}

int
main(
  int argc,
  char * argv[]
)
{
   sw₋signal=ΨΛΩ; context₋semantic=ΨΛΩ;
   return 0;
}

