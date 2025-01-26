/*  institut-macos.c | primary memory branch. */

#include "twinbeam-inner.h"
#include <stdlib.h>
#include <malloc/malloc.h>

void * Cattle(__builtin_int_t bytes)
{
   return calloc(bytes,1);
}

__builtin_int_t Heap₋object₋size(void * ref) { return malloc_size(ref); }

void Fallow(void * ref) { free(ref); }

void * _Block₋copy(const void * block)
{
   struct Block₋layout * origin = (struct Block₋layout *)block;
   __builtin_int_t size=origin->descriptor->size;
   struct Block₋layout * copy = (struct Block₋layout *)malloc(size);
   Copy8Memory((ByteAlignedRef)copy,(ByteAlignedRef)origin,size);
   return copy;
}

void _Block₋release(const void * block)
{
   free((void *)block);
}

#pragma recto platform-specifics

void register₋reflect(__builtin_uint_t mask, 
 void (^out)(char32̄_t uc)) 
{
   out((char32̄_t)U'∎');
} /* alternative definition in --<Additions>--<Present-hw.cpp>. */

void platform₋reflect(__builtin_uint_t mask,
 void (^out)(char32̄_t uc)) 
{
   out((char32̄_t)U'∎');
} /*  alternative definition in --<Additions>--<Present-hw.cpp>. */

#pragma recto seldom used arrangements

#if defined __arm64__
__attribute__ ((target("rand")))
#elif defined __x86_64__
__attribute__ ((target("rdrnd")))
#endif
void RandomInteger(uint64_t * out)
{ int y;
again:
#if defined __x86_64__
   y = __builtin_ia32_rdrand64_step(out);
#elif defined __arm64__
   y = __builtin_arm_rndr(out); /* asm { mrs x0, RNDR } also 'mrs x1, NZCV'. */
#endif
  if (y == 0) goto again;
}

#pragma recto unit testing and symbol find in executables

#include <unistd.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>

void
Symbols(
  const char * utf8exepath,
  void (^symbol)(const char * sym, uint64_t addr, int * stop))
{ __builtin_int_t bytesActual;
    int fd = open((const char *)utf8exepath, O_RDONLY | O_SYMLINK);
    if (fd == -1) return;
    struct stat sb; if (fstat(fd,&sb) == -1) return;
    uint8_t * obj = Cattle(sb.st_size);
    bytesActual = pread(fd,obj,sb.st_size,0);
    if (bytesActual != sb.st_size) return;
    uint8_t * obj_p = obj;
    
    struct mach_header_64 * header = (struct mach_header_64 *)obj_p;
    obj_p += sizeof *header;
    struct section * sections = 0;
    uint32_t nsects;
    
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 outerStop = false;
    
    for (int i=0; i<header->ncmds; i+=1) {
      struct load_command *lc = (struct load_command *)obj_p;
      if (lc->cmd == LC_SYMTAB) {
         struct symtab_command *symtab = (struct symtab_command *)obj_p;
         obj_p += sizeof *symtab;
         struct nlist_64 *ns = (struct nlist_64 *)(obj + symtab->symoff);
         char * strtable = (char *)(obj + symtab->stroff);
         for (int i = 0; i < symtab->nsyms; i+=1) {
            struct nlist_64 *entry = ns + i;
            uint32_t idx = entry->n_un.n_strx;
            if ((entry->n_type & N_TYPE) == N_SECT) { symbol(strtable + idx, 
              entry->n_value,&outerStop); }
            if (outerStop) return;
         }
      } else if (lc->cmd == LC_SEGMENT) {
         struct segment_command * segment = (struct segment_command *)obj_p;
         obj_p += sizeof *segment;
         nsects = segment->nsects;
         sections = (struct section *)obj_p;
         obj_p += nsects * sizeof *sections;
      } else { obj_p += lc->cmdsize; }
    }
}

#pragma recto library version and identity

void Identity₋Tb(char ** text)
{
   *text=SHA1GIT;
}

