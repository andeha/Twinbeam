/*  symbol-dynam.c | symbols are sometime edited. */

import Twinbeam;

unicode₋shatter persist₋as₋shatter(struct Unicodes ucs)
{
   __builtin_int_t bytes = ucs.tetras*4;
   void * storage = Heap₋alloc(bytes);
   Copy8Memory(storage,(ByteAlignedRef)(ucs.unicodes),bytes);
   return (unicode₋shatter)storage;
}

void unalloc₋shatter(unicode₋shatter text)
{
   Heap₋unalloc(text);
}

