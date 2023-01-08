/*  bowler-ketter.c | association /mul-t-i-set/ thesarus and array-of-Unicods from Unicode. (ية) */

import Twinbeam;

#if !defined usage₋𝟷𝟸𝟾₋bit₋integer
#error "Requires the one-hundred-twenty-eight-bit type __uint128_t"
#endif

int form₋ōnymon(struct Unicodes key₋copy, struct Unicodes value₋copy, 
 int shares, void ** opaque, ALLOC alloc)
{
   INIT init₋with₋one₋collection = ^(void * uninited) { return 
    collection₋init(sizeof(void *),4096,uninited); };
   struct collection * list = jot(key₋copy,opaque,sizeof(struct 
    collection),alloc,init₋with₋one₋collection);
   if (list == ΨΛΩ) { return -3; }
   __builtin_int_t size = sizeof(unicode₋shatter);
   if (collection₋count(list) == 0) {
     unicode₋shatter keytext = persist₋as₋shatter(key₋copy);
     if (copy₋append₋items(size,&keytext,list,alloc)) { return -2; }
   }
   unicode₋shatter value₋text = persist₋as₋shatter(value₋copy);
   if (copy₋append₋items(size,&value₋text,list,alloc)) { return -1; }
   return 0;
} /* heap-allocated pointers to unicodes stored in one structure that may 
 be lengthen. */

inexorable int item₋not₋crossed(unicode₋shatter entry)
{
   return entry != ΨΛΩ && entry != (unicode₋shatter)0x2425;
}

inexorable void cross₋item(unicode₋shatter * ref)
{
   unalloc₋shatter(*ref);
   *ref = (unicode₋shatter)0x2425; /* as Unicode ␥ is U+2425 and E2 90 A5. */
}

int dissociate₋isolate(struct Unicodes key, int index, void ** opaque)
{
   __uint128_t fineprint = FNV1b(4*key.tetras,key.unicodes);
   struct w₋node * node = impression₋seek(*opaque,fineprint);
   if (node != ΨΛΩ) { unicode₋shatter key; struct collection * list;
     list = (struct collection *)node->note;
     key = (unicode₋shatter)collection₋relative(0,list);
     if (!item₋not₋crossed(key)) { return 0; }
     __builtin_int_t actual,i,count=collection₋count(list)-1;
     struct Unicodes values[count]; unicode₋shatter material;
     for (i=0; i<count; i+=1) {
       material = (unicode₋shatter)collection₋relative(1+i,list);
       if (item₋not₋crossed(material)) {
         if (index == actual) { cross₋item(&material); }
         actual+=1;
       }
     }
   }
   return 0;
}

int dissociate₋all(struct Unicodes key, void ** opaque)
{
   __uint128_t fineprint = FNV1b(4*key.tetras,key.unicodes);
   struct w₋node * node = impression₋seek(*opaque,fineprint);
   if (node != ΨΛΩ) { struct collection * list;
     unicode₋shatter key;
     list = (struct collection *)node->note;
     key = (unicode₋shatter)collection₋relative(0,list);
     if (item₋not₋crossed(key)) { cross₋item(&key); }
     __builtin_int_t count=collection₋count(list),i;
     for (i=0; i<count; i+=1) { unicode₋shatter material;
       material=(unicode₋shatter)collection₋relative(1+i,list);
       if (item₋not₋crossed(material)) { cross₋item(&material); }
     }
   }
   return 0;
}

int evidence₋related(struct Unicodes key, void (^right)(int count, 
 struct Unicodes values[]), void * opaque)
{
   __uint128_t fineprint = FNV1b(4*key.tetras,key.unicodes);
   struct w₋node * node = impression₋seek(opaque,fineprint);
   if (node != ΨΛΩ) { struct collection * list; unicode₋shatter * key;
     list = (struct collection *)node->note;
     key = (unicode₋shatter *)collection₋relative(0,list);
     if (item₋not₋crossed(*key)) { return 0; }
     __builtin_int_t actual,i,count=collection₋count(list)-1;
     struct Unicodes values[count];
     for (i=0; i<count; i+=1) { unicode₋shatter material;
       material = (unicode₋shatter)collection₋relative(1+i,list);
       if (item₋not₋crossed(material)) { __builtin_int_t symbols;
         symbols=Heap₋object₋size(material);
         values[i].tetras=symbols;
         values[i].unicodes=material;
         actual+=1;
       }
     }
     right(actual,values);
   }
   return 0;
}


