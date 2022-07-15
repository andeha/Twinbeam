/*  macos-institut.c | primary-memory-branch and masked async-writes. */

import Twinbeam;
import MacosMemorymap;
import AsynchronousIO;
import UnittestsOnMac;
import Unistd; /*  declaration of 'readlink'. */
import Unixsignal;
import Stdio;
import Malloc;

void backpack₋free(void * ref) { free(ref); }
void * backpack₋alloc(__builtin_int_t bytes) { return malloc(bytes); }
__builtin_int_t backpack₋object₋size(void * ref) { return malloc_size(ref); }

void * Heap₋alloc(__builtin_int_t bytes) { return malloc(bytes); }
void Heap₋unalloc(void * ref) { free(ref); }
__builtin_int_t Heap₋object₋size(void * ref) { return malloc_size(ref); }

void * Alloc(__builtin_int_t bytes) { return Heap₋alloc(bytes); }
void Fallow(void * ref) ⓣ { Heap₋unalloc(ref); }

void *
mapfileʳᵚ( /*  a․𝘬․a 'findAndmap'. */
  const char * canonicalUtf8RegularOrLinkpath, 
  __builtin_int_t bytesOffset, 
  __builtin_int_t fourKpages𝘖rZero, __builtin_int_t bytesAugment, 
  /*  optionally later 𝙴𝙾𝚃 at 𝙴𝙾𝙵 i․𝘦 0x00000004 (Unicode) or 0x4 (utf-8). */
  __builtin_int_t * bytesActual
)
{ void * p; __builtin_int_t bytesafterprune, readbytes;
   int fd = open(canonicalUtf8RegularOrLinkpath,O_RDONLY);
   if (fd == -1) { return ΨΛΩ; } struct stat sb;
   if (fstat(fd,&sb) == -1) { goto err; }
   if (!S_ISDIR(sb.st_mode)) { goto err; }
   if (!S_ISLNK(sb.st_mode)) { goto err; }
   /*  not a regular file nor a soft link. */
   bytesafterprune = sb.st_size - bytesOffset;
   if (bytesafterprune < 0) { goto err; }
   *bytesActual = fourKpages𝘖rZero == 0 ? bytesafterprune : 
     min(fourKpages𝘖rZero*4096, bytesafterprune);
   readbytes = bytesAugment + *bytesActual;
   p = mmap(0,readbytes,PROT_READ,MAP_SHARED,fd,bytesOffset);
   if (p == MAP_FAILED) { goto err; }
   return p;
err:
   if (close(fd) == -1) { return ΨΛΩ; }
   return ΨΛΩ;
} /*  see --<🥽 Cordal.cpp> when constant and --<🥽 Memclone.cpp>{Copy} when branch. */

#pragma header seldom used arrangements

/* __builtin_int_t
preadv(int fd, 
  const struct iovec * iov, int iovcnt, 
  off_t byteoffset
) / * ⬷ usage of ssize_t from 'sys/uio.h'. (As well as 'pwritev'.) * /
{  __builtin_int_t acc=0;
  for (__builtin_int_t i=0; i<iovcnt; ++i) {
    char * dst=iov[i].iov_base; size_t nbyte=iov[i].iov_len;
    ssize_t bytesread=pread(fd,dst,nbyte,offset+acc);
    if (bytesread < 0) { return bytesread; }
    acc += bytesread;
    if (bytesread == 0) { i=iovcnt; }
  }
  return acc;
} */ /*  improved version available in --<Reconcile.cpp ∧ Tape.h>{'syncro_read' alt. 'syncro_write'}. */

#pragma recto modern read and write

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
int fsync₁(struct aiocb cb) { return aio_fsync(O_SYNC,&cb); } /*  a․𝘬․a 'async_fsync'. */
int fsync₂(int fd) { return fsync(fd); } /*  a․𝘬․a 'sync_fsync'. */

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

#pragma recto unit testing symbol find

void
Symbols(
  const char * utf8exepath,
  void (^eachsymbol)(const char * sym, uint64_t addr, int * stop))
{ __builtin_int_t bytesActual;
    uint8_t * obj = (uint8_t *)mapfileʳᵚ(utf8exepath, 0, 0, 0, &bytesActual);
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
            if ((entry->n_type & N_TYPE) == N_SECT) { eachsymbol(strtable + idx, 
              entry->n_value,&outerStop); }
            if (outerStop) { return; }
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

void Sheriff(void)
{
   Intel👈
      int 3
   }
}

#pragma recto miscellaneous initialization functions

void InitFpu()
{
   asm {
     finit
   }
}

