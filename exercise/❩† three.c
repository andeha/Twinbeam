/* ❩† three.c | the collection tests. */

#include "twinbeam.h"

CORRECT(Collection_1)
{
   unsigned bytes₋per₋item=4,bytes₋per₋tile=4096; struct collection 🅰;
   if (collection₋init(bytes₋per₋item,bytes₋per₋tile,&🅰)) 
    ENSURE(false,"error when initing collection");
   
   char32̄_t * text = U"hello world";
   if (copy₋append₋items(11+1,text,&🅰,Alloc)) 
    ENSURE(false,"error when copy-append items");
   uint8_t * byteref = collection₋relative(8,&🅰);
   char32̄_t uc = *(char32̄_t *)byteref;
   ENSURE(uc == U'r',"error when retrieving material");
    __builtin_int_t count = collection₋count(&🅰);
   ENSURE(count=3,"wrong number of elements")
   if (deinit₋collection(&🅰, Fallow)) 
    ENSURE(false,"error when deiniting collection");
}