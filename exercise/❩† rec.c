/*  ❩† rec.c | recording variable arguments to string. */

#include "twinbeam.h"

CORRECT(Record_1)
{
   int symbols = Play(^(__builtin_int_t total, char32̄_t * ucs) {
     print("recording is '⬚'",﹟S(total,ucs));
   }, U"hello world and ⬚", ﹟d(13));
   ENSURE(symbols == 18, "error executing 'Play'.");
}

