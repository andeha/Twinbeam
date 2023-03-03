/*  macos-institut.c | primary-memory-branch and masked async-writes. */

import Twinbeam;

#include <malloc/malloc.h>

void * Heap₋alloc(__builtin_int_t bytes)
{
   return malloc(bytes);
} /*  a․𝘬․a 'malloc₋alloc'. */

void * Alloc(__builtin_int_t bytes) ⓣ
{
   return calloc(bytes,1);
} /*  a․𝘬․a 'User₋alloc'. */

void * Cons₋alloc(__builtin_int_t object₋bytes)
{
   return Heap₋alloc(object₋bytes);
} /*  a․𝘬․a 'Coalesc₋alloc'. */

__builtin_int_t Heap₋object₋size(void * ref) { return malloc_size(ref); }

void Heap₋unalloc(void * ref) { free(ref); }

void Fallow(void * ref) ⓣ { Heap₋unalloc(ref); }

void Cons₋fallow(void * reference) { Heap₋unalloc(reference); }

void * _Block₋copy(const void * block)
{
   struct Block₋layout * origin = (struct Block₋layout *)block;
   __builtin_int_t size=origin->descriptor->size;
   struct Block₋layout * copy = (struct Block₋layout *)Heap₋alloc(size);
   Copy8Memory((ByteAlignedRef)copy,(ByteAlignedRef)origin,size);
   return copy;
}

void _Block₋release(const void * block)
{
   Heap₋unalloc((void *)block);
}

/*  see --<🥽 Cordal.cpp> when constant and --<🥽 Memclone.cpp>{Copy} when branch. */

/*  improved version available in --<Reconcile.cpp ∧ Tape.h>{'syncro_read' alt. 'syncro_write'}. */

/* do not call 'MacosMemorymap' and do not call 'aio'. */

int
TransformAndResolve(
  struct Unicodes path, 
  void (^final)(char * regular𝘖rLinkpath)
)
{
   char8₋t u8s[path.tetras*4]; __builtin_int_t actual;
   if (UnicodeToUtf8(path.tetras,path.unicodes,u8s,&actual)) return -1;
   final((char *)u8s);
   return 0;
}

#pragma recto seldom used arrangements

#if defined __x86_64__
__attribute__ ((target("rdrnd")))
#endif
void RandomInteger(uint64_t * out)
{ int y;
again:
#if defined __x86_64__
   y = __builtin_ia32_rdrand64_step(out);
#elif defined __armv8a__
   y = __builtin_arm_rndr(out); /* asm { mrs x0, RNDR } also 'mrs x1, NZCV'. */
#endif
  if (y == 0) goto again;
}

#pragma recto modern read and write

#include <aio.h> /* Addition/heavy-duty/Tape.h */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

int superfluous_async_read(struct aiocb cb, int job, const char * utf8file, 
 int bytes, uint8_t * material, int byteoffset)
{ int y=0;
   int fd = open(utf8file, O_RDONLY, 0);
   if (fd == -1) { y=-1; goto err₂𝘖rContinue; }
   Clear8Memory((ByteAlignedRef)&cb,sizeof(struct aiocb));
   cb.aio_nbytes = (size_t)bytes; /*  alt-in-hw. 64kb for pic32mzda. */
   cb.aio_fildes = fd;
   cb.aio_offset = (off_t)byteoffset;
   cb.aio_buf = material;
   cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
   cb.aio_sigevent.sigev_signo = SIGUSR2;
   union sigval sv = { .sival_ptr=&job };
   cb.aio_sigevent.sigev_value = sv;
   if (aio_read(&cb) == -1) { y=-2; goto err₁; }
   goto err₂𝘖rContinue;
err₁:
   if (close(fd)) { return -1; }
err₂𝘖rContinue:
   return y;
}

int superfluous_async_write(struct aiocb cb, int job, const char * utf8file, 
 int bytes, uint8_t * material, int byteoffset)
{ int y=0;
   int fd = open(utf8file, O_CREAT | O_TRUNC | O_WRONLY | O_NOFOLLOW | O_EXLOCK, 0666); /* Locks like `flock`. */
   if (fd == -1) { y=-1; goto err₂𝘖rContinue; }
   Clear8Memory((ByteAlignedRef)&cb,sizeof(struct aiocb));
   cb.aio_nbytes = (size_t)bytes;
   cb.aio_fildes = fd;
   cb.aio_offset = (off_t)byteoffset;
   cb.aio_buf = material;
   cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
   cb.aio_sigevent.sigev_signo = SIGUSR2;
   union sigval sv = { .sival_ptr=&job };
   cb.aio_sigevent.sigev_value = sv;
   /* auto job₂ = ^{ close(fd); if (aio_return(&cb) != -1) { completion(); } };
   auto job₃ = ^{ if (!aio_fsync(O_SYNC, &cb)) { job₂(); } }; O_DIRECT not used. */
   if (aio_write(&cb) == -1) { y=-2; goto err₁; }
   goto err₂𝘖rContinue;
err₁:
   if (close(fd)) { return -1; }
err₂𝘖rContinue:
   return y;
}

void didReadWriteOrSync₁(int job)
{
  print("Finished: ⬚\n", ﹟x((__builtin_int_t)job));
  /* ₍ed₎₋history::pad₋history->open₋files */
}

void didReadWriteOrSync₂(int job, struct __siginfo *, void *)
{
  print("Finished: ⬚\n", ﹟x((__builtin_int_t)job));
}

int InitAIO(void (^jots)(const char * utf8logformat, ...))
{
   typedef void (^Init)();
   Init init₁ = ^{ signal(SIGUSR2,didReadWriteOrSync₁); };
   Init init₂ = ^{ struct sigaction sa, sa_old;
     sigemptyset(&sa.sa_mask);
     sa.sa_flags = SA_RESTART | SA_SIGINFO;
     sa.sa_sigaction = didReadWriteOrSync₂;
     if (sigaction(SIGUSR2,&sa,&sa_old) != 0) { jots("Error in InitIO\n"); Sheriff(); }
   }; init₁();
   return 0;
}

/* When the flag 'O_DIRECT' is not include when 'open': */

#pragma recto even less used arrangements

int fdwrite(int fd, int bytes, uint8_t * material, int count, 
 int excludeoffsets[], int excludebytes[]) { return 0; }

int Cattle(struct Unicodes * regularpathOrΨΛΩ, struct collection * branch, 
  void (^ping)(double⁺ʳ 𝟬₋𝟭percent, int * stop), 
  void (^zero𝘖rSeveral)(__builtin_int_t offset, short bytes, uint8_t * page, int * stop), 
  int (^completion)(__builtin_int_t bytes, int * no₋go)
) NEVERBLURTS /*  c𝘧․ Intel 'segmentation' and 'paging'. */
{
    /* Compute a rolling CRC and a hash for each page. (To further 'man rsync'.) */
    typedef void (^Galois)(uint8_t *, __builtin_int_t);
    Galois Δ₋encode = ^(uint8_t * buf, __builtin_int_t bytes)
    {  uint8_t prev=0; for (__builtin_int_t i=0; i<bytes; i+=1) {
         uint8_t curr=buf[i]; buf[i]=curr-prev; prev=curr;
       }
    }, Δ₋dencode = ^(uint8_t * buf, __builtin_int_t bytes)
    {  uint8_t prev=0; for (__builtin_int_t i=0; i<bytes; i+=1) {
         uint8_t delta=buf[i]; buf[i]=delta+prev; /* buf[i]=delta and curr; */
       }
    };
   
    return 0;
} /*  a․𝘬․a 'Reconcile', 'Stock', 'Settle' and 'Arbitrate'. See also 'rsync'. */

#pragma recto commands installed and big com-put-err

#include <stdio.h>

int Order(void (^out)(char32̄_t * ucs, __builtin_int_t bytes), char32̄_t * command, ...)
{ int y1, 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 y2,status=0; pid_t pid; size_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 bytes₋read;
   va_prologue(command)
   y1 = Play(command,__various,^(__builtin_int_t total, char32̄_t * ucs) {
     char8₋t text[4*total]; __builtin_int_t u8bytes;
     y2 = UnicodeToUtf8(total,ucs,text,&u8bytes);
     if (y2 != 0) goto unagain2;
     text[u8bytes] = '\0';
     FILE * fp = popen((char *)text,"r");
     if (fp == ΨΛΩ) goto unagain2;
     uint8_t buffer[4097];
again:
     if (ferror(fp)) { y2 = -1; goto unagain1; }
     if (feof(fp)) goto unagain1;
     bytes₋read = fread(buffer,1,4096,fp);
     buffer[bytes₋read] = '\0'; printf("%s",buffer);
      /* out(char32,bytes) */ goto again;
unagain1:
     pclose(fp);
unagain2:
     ;
   });
   va_epilogue
   return y2;
}

#pragma recto unit testing and symbol find in executables

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
    uint8_t * obj = Heap₋alloc(sb.st_size); 
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

#pragma recto analysis post-mortem and single-steps

#if defined __x86_64__
void Sheriff(void)
{
   Intel👈
      int 3
   }
}
#endif

#pragma recto miscellaneous initialization functions

void InitFpu()
{
#if defined __x86_64__
   asm {
     finit
   }
#endif
}

