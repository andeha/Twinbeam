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

#pragma recto buddy list

struct allocation {
   uint64_t bytes;
   int free;
   struct allocation * next;
};

void * heap₋allocations = ΨΛΩ;

inexorable struct allocation * firstfit₋in₋allocations(
  struct allocation ** previous, uint64_t bytes
)
{ int qualified=0;
   struct allocation * head = heap₋allocations;
again:
   if (head == ΨΛΩ) { return ΨΛΩ; }
   qualified = head->free && head->bytes >= bytes;
   if (qualified) { return head; }
   *previous = head;
   head = head->next;
   goto again;
}

#include <sys/mman.h>

inexorable struct allocation * 
allocate₋consecutive(
  struct allocation * last, uint64_t bytes
)
{ struct allocation * block;
   int prot = PROT_READ | PROT_WRITE, 
    flags = MAP_ANONYMOUS | MAP_PRIVATE, 
    fd = -1, offset=0;
   size_t length = bytes+sizeof(struct allocation);
   block = mmap(0,length,prot,flags,fd,offset);
   if (block == MAP_FAILED) { return ΨΛΩ; }
   if (last != ΨΛΩ) { last->next = block; }
   block->bytes = bytes;
   block->free = 0;
   block->next = ΨΛΩ;
   return block;
}

void * Heap₋alloc(uint64_t bytes)
{
   if (bytes <= 0 ) { return ΨΛΩ; }
   struct allocation * block;
   if (heap₋allocations == ΨΛΩ) {
      block = allocate₋consecutive(ΨΛΩ,bytes);
      if (block == ΨΛΩ) { return ΨΛΩ; }
      heap₋allocations = block;
   } else {
      struct allocation * last = heap₋allocations;
      block = firstfit₋in₋allocations(&last,bytes);
      if (block == ΨΛΩ) {
         block = allocate₋consecutive(last,bytes);
         if (block == ΨΛΩ) { return ΨΛΩ; }
      } else {
         block->free = 0;
      }
   }
   return block + 1;
}

void Free₋heap(void * p)
{
   if (p == ΨΛΩ) { return; }
   struct allocation * block = (struct allocation *)p - 1;
   block->free = 0;
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
#include <time.h>
__attribute__ ((target("rand")))
#elif defined __x86_64__
__attribute__ ((target("rdrnd")))
#endif
void RandomInteger(uint64_t * out)
{ int y;
#if defined __x86_64__
again:
   y = __builtin_ia32_rdrand64_step(out);
   if (y == 0) goto again;
#elif defined __arm64__
   /* y = __builtin_arm_rndr(out); a․𝘬․a asm { mrs x0, RNDR }. */
   static __uint128_t state = 1;
   if (state == 1) { state = (unsigned)time(NULL); }
#define UINT128(hi, lo) (((__uint128_t) (hi)) << 64 | (lo))
   state *= UINT128(0x0fc94e3bf4e9ab32,0x866458cd56f5e605);
   *out = state >> 64;
#endif
}

#pragma recto unit test with 'symbol find' in executables

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/dyld.h>
#include <string.h>

void
Symbols(
  const char * utf8exepath,
  void (^symbol)(const char * sym, uint64_t addr, int * stop))
{
    uint8_t * base = (uint8_t *)_dyld_get_image_header(0);
    struct mach_header_64 * header = (struct mach_header_64 *)base;
    uint8_t * pointer = base + sizeof(struct mach_header_64);
    struct symtab_command * symbols = NULL;
    uint64_t segment1_vaddr = 0x0000000100000000;
    
    for (int i=0; i<header->ncmds; i+=1) {
      struct load_command * load = (struct load_command *)pointer;
      /* print("command is ⬚\n", ﹟x((uint64_t)load->cmd)); */
      if (load->cmd == LC_SYMTAB) {
         symbols = (struct symtab_command *)pointer;
      }
      else if (load->cmd == LC_SEGMENT_64) {
         struct segment_command_64 * segment;
         segment = (struct segment_command_64 *)pointer;
         if (strcmp(segment->segname, "__TEXT") == 0) {
           segment1_vaddr = segment->vmaddr;
           /* __builtin_dump_struct(segment,&printf); */
         }
      }
      pointer += load->cmdsize;
    }
    
    /* Symbol table is remembered in the variable `symbols`. */
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 outerStop = false;
    struct nlist_64 * entries = (struct nlist_64 *)(base + symbols->symoff);
    char * strings = (char *)(base + symbols->stroff);
    for (int i=0; i<symbols->nsyms; i+=1) {
      struct nlist_64 * entry = entries + i;
      /* __builtin_dump_struct(entry,&printf); */
      uint32_t index = entry->n_un.n_strx;
      if ((entry->n_type & N_TYPE) == N_SECT) {
        uint64_t address = (uint64_t)(entry->n_value) - segment1_vaddr;
        symbol(strings + index, address + (uint64_t)base, &outerStop); }
      if (outerStop) return;
    }
}

#pragma recto library version and identity

void Identity₋Tb(char ** text)
{
   *text=SHA1GIT;
}

