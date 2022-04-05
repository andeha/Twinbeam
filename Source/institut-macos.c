/*  macos.cpp | primary-memory-branch and masked async-writes. */

import Twinbase;
import MacosMemorymap;
import AsynchronousIO;
import UnittestsOnMac;
import Unistd;

void backpack₋free(void * ref) { free(ref); }

void * backpack₋alloc(__builtin_int_t bytes) { return malloc(bytes); }

void *
mapfileʳᵚ( /* ⬷ a․𝘬․a 'findAndmap'. */
  const char * canonicalUtf8RegularOrLinkpath, 
  __builtin_int_t bytesOffset, 
  __builtin_int_t pages𝘖rZero, __builtin_int_t bytesAugment, 
  /* ⬷ optionally later 𝙴𝙾𝚃 at 𝙴𝙾𝙵 i․𝘦 0x00000004 (Unicode) or 0x4 (utf-8). */
  __builtin_int_t * bytesActual
)
{ void * p; __builtin_int_t bytesafterprune, readbytes;
   int fd = open(canonicalUtf8RegularOrLinkpath,O_RDONLY);
   if (fd == -1) { return NULL; } struct stat sb;
   if (fstat(fd,&sb) == -1) { goto err; }
   if (!S_ISDIR(sb.st_mode)) { goto err; }
   if (!S_ISLNK(sb.st_mode)) { goto err; }
   /* ⬷ not a regular file nor a soft link. */
   bytesafterprune = sb.st_size - bytesOffset;
   if (bytesafterprune < 0) { goto err; }
   *bytesActual = pages𝘖rZero == 0 ? bytesafterprune : 
     min(pages𝘖rZero*Syspagesize(), bytesafterprune);
   readbytes = bytesAugment + *bytesActual;
   p = mmap(0,readbytes,PROT_READ,MAP_SHARED,fd,bytesOffset);
   if (p == MAP_FAILED) { goto err; }
   return p;
err:
   if (close(fd) == -1) { return NULL; }
   return NULL;
} /* ⬷ see --<🥽 Cordal.cpp> when constant and --<🥽 Memclone.cpp>{Copy} when branch. */

#pragma mark modern read and write

int superfluous_async_read(aiocb cb, int job, const char * utf8file, int bytes, uint8_t * material, int byteoffset)
{  int y=0;
    int fd = open(utf8file, O_RDONLY, 0);
    if (fd == -1) { y=-1; goto err₂𝘖rContinue; }
    Clear8Memory(ByteAlignedRef(&cb),sizeof(aiocb));
    cb.aio_nbytes = (size_t)bytes; /* ⬷ alt-in-hw. 64kb for pic32mzda. */
    cb.aio_fildes = fd;
    cb.aio_offset = (off_t)byteoffset;
    cb.aio_buf = material;
    cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    cb.aio_sigevent.sigev_signo = SIGUSR2;
    cb.aio_sigevent.sigev_value = sigval { .sival_ptr=&job };
    if (aio_read(&cb) == -1) { y=-2; goto err₁; }
    goto err₂𝘖rContinue;
err₁:
    if (close(fd)) { return -1; }
err₂𝘖rContinue:
    return y;
}

int superfluous_async_write(aiocb cb, int job, const char * utf8file, int bytes, uint8_t * material, int byteoffset)
{  int y=0;
    int fd = open(utf8file, O_CREAT | O_TRUNC | O_WRONLY | O_NOFOLLOW | O_EXLOCK, 0666); /* Locks like `flock`. */
    if (fd == -1) { y=1; goto err₂𝘖rContinue; }
    Clear8Memory(ByteAlignedRef(&cb),sizeof(aiocb));
    cb.aio_nbytes = (size_t)bytes;
    cb.aio_fildes = fd;
    cb.aio_offset = (off_t)byteoffset;
    cb.aio_buf = material;
    cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    cb.aio_sigevent.sigev_signo = SIGUSR2;
    cb.aio_sigevent.sigev_value = sigval { .sival_ptr=&job }; 
    /* auto job₂ = ^{ close(fd); if (aio_return(&cb) != -1) { completion(); } };
    auto job₃ = ^{ if (!aio_fsync(O_SYNC, &cb)) { job₂(); } }; O_DIRECT not used. */
    if (aio_write(&cb) == -1) { y=-2; goto err₁; }
    goto err₂𝘖rContinue;
err₁:
    if (close(fd)) { return -1; }
err₂𝘖rContinue:
    return y;
}

void didReadWriteOrSync(int job)
{
   print("Finished: ⬚\n", ﹟x((__builtin_int_t)job));
   /* ₍ed₎₋history::pad₋history->open₋files */
}

int InitAIO()
{
   signal(SIGUSR2,didReadWriteOrSync);
   return 0;
}

int fdwrite(int fd, int bytes, uint8_t * material, int count, 
 int excludeoffsets[], int excludebytes[]) { return 0; }

#pragma mark unit testing symbol find

void
Symbols(
  const char * utf8exepath,
  void (^eachsymbol)(const char * sym, uint64_t addr, bool& stop))
{ __builtin_int_t bytesActual;
    uint8_t * obj = (uint8_t *)mapfileʳᵚ(utf8exepath, 0, 0, 0, &bytesActual);
    uint8_t * obj_p = obj;
    
    struct mach_header_64 * header = (struct mach_header_64 *)obj_p;
    obj_p += sizeof *header;
    struct section * sections = 0;
    uint32_t nsects;
    
    bool 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 outerStop = false;
    
    for (int i=0; i<header->ncmds; ++i) {
      struct load_command *lc = (struct load_command *)obj_p;
      if (lc->cmd == LC_SYMTAB) {
         struct symtab_command *symtab = (struct symtab_command *)obj_p;
         obj_p += sizeof *symtab;
         struct nlist_64 *ns = (struct nlist_64 *)(obj + symtab->symoff);
         char * strtable = (char *)(obj + symtab->stroff);
         for (int i = 0; i < symtab->nsyms; i++) {
            struct nlist_64 *entry = ns + i;
            uint32_t idx = entry->n_un.n_strx;
            if ((entry->n_type & N_TYPE) == N_SECT) { eachsymbol(strtable + idx, 
              entry->n_value, outerStop); }
            if (outerStop) { return; }
         }
      } else if (lc->cmd == LC_SEGMENT) {
         segment_command * segment = (struct segment_command *)obj_p;
         obj_p += sizeof *segment;
         nsects = segment->nsects;
         sections = (struct section *)obj_p;
         obj_p += nsects * sizeof *sections;
      } else { obj_p += lc->cmdsize; }
    }
}


