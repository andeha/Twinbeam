/*  Async-ℱ₂.cpp | Illustrates how to asynchronously write files. (DO-NOT-PUBLISH.) */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <aio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/uio.h>

/* xcrun clang @ccargs_macᵧ² -o Async-F₂ ../../Source/llvmʳᵗ³.cpp '🥽 Async-F₂.cpp' */

struct Ongoing { int 🥈 Maxjobs=10; aiocb cb; 
  struct { __builtin_int_t iovcnt; iovec * iov; __builtin_int_t curridx; } tiles;
  int fd; AsyncJob completion; bool docancel; bool completed;
} ongoings[Ongoing::Maxjobs];

int O₍1₎Acquire(int * slot) { for (int i=0; i<Ongoing::Maxjobs; i++) {
  if (ongoings[i].completed) *slot=i; return 0; } return -1; 
} /* ⬷ See also `Acquire𝟷ᵈ` for a speedier indexed method. */

/* When the flag `O_DIRECT` is not include when `open`: */
inexorable int async_fsync(aiocb cb) {
  if (!aio_fsync(O_SYNC,&cb)) { return -1; }
  return 0;
}

inexorable int chained_write(int job)
{
    Ongoing & ongoing = ongoings[job]; aiocb & cb = ongoing.cb;
    __builtin_int_t idx=ongoing.tiles.curridx;
    cb.aio_nbytes = (size_t)ongoing.tiles.iov[idx].iov_len;
    cb.aio_offset = (off_t)0;
    cb.aio_buf = ongoing.tiles.iov[idx].iov_base;
    if (aio_write(&cb) == -1) { return -2; }
    return 0;
}

inexorable int chained_read(int job)
{
    Ongoing & ongoing = ongoings[job]; aiocb & cb = ongoing.cb;
    __builtin_int_t idx=ongoing.tiles.curridx;
    cb.aio_nbytes = (size_t)ongoing.tiles.iov[idx].iov_len;
    cb.aio_offset = (off_t)0;
    cb.aio_buf = ongoing.tiles.iov[idx].iov_base;
    if (aio_read(&cb) == -1) { return -2; }
    return 0;
}

void didReadWriteOrSync(int job)
{
    print("didReadWriteOrSync\n");
    Ongoing & ongoing = ongoings[job];
    auto fileclose = ^{ if (close(ongoing.fd)) { print("Close failed\n"); 
       return -1; } return 0; };
    auto endofline = ^{  __builtin_int_t diff = ongoing.tiles.curridx - 
       ongoing.tiles.iovcnt;
      if (diff < 0) { if (chained_write(job)) { return -1; } }
      else if (diff == 0) { if (async_fsync(ongoing.cb)) { return -1; } }
      else { fileclose(); ongoing.completion(); ongoing.completed=true; }
      ongoing.tiles.curridx++; return 0; };
    aiocb & cb = ongoings[job].cb;
    int errⱿ = aio_error(&cb);
    switch (errⱿ) {
    case EINPROGRESS: /* Does not happen after a signal has fired. */ break;
    case ECANCELED: print("Job ⬚ cancelled\n", ﹟d(__builtin_int_t(job))); 
      /* rollback₂ */ fileclose(); break;
/*     case 0: print("Completed successfully.\n"); if (endofline()) 
      { print("Kettering failed\n"); } break;
    default: print("A read/write/f(data)sync errno: ⬚ (job ⬚)\n", 
      ﹟d(__builtin_int_t(errⱿ)), ﹟d(__builtin_int_t(job))); break;    */
    }
    
    ssize_t ret = aio_return(&cb); if (ret != -1) { 
      if (endofline()) { print("Kettering failed\n"); }
    }
}

FOCAL
int
stop(int job)
{
    Ongoing & ongoing = ongoings[job];
    if (ongoing.completed) { return -1; }
    ongoing.docancel = true;
    if (aio_cancel(ongoing.fd,NULL)) { return -1; }
    /* rollback₁ */
    return 0;
}

FOCAL
int
read(int job, 
  const char * utf8file, 
  __builtin_int_t count, struct iovec * iov, 
  AsyncJob completion
)
{  int y=0;
    int fd = open(utf8file, O_RDONLY, 0);
    if (fd == -1) { return -1; }
    Ongoing & ongoing = ongoings[job]; aiocb & cb = ongoing.cb;
    Clear8Memory(ByteAlignedRef(&cb),sizeof(aiocb));
    cb.aio_fildes = fd;
    cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    cb.aio_sigevent.sigev_signo = SIGUSR2;
    cb.aio_sigevent.sigev_value.sival_int = job;
    iovec * recio = (iovec *)malloc(count*sizeof(iovec)); /* new iovec[count]; */
    Copy8Memory(ByteAlignedRef(recio), ByteAlignedRef(iov), count*sizeof(struct iovec));
    ongoings[job] = { cb, { count, recio, 0 }, fd, completion, false, false };
    /* Note also possible to store `count` down-to `0` as well as disjunct unrelated 'tiles'. */
    if (chained_read(job)) { return -1; }
    goto err₂𝘖rContinue;
err₁:
    if (close(fd)) { return -1; }
err₂𝘖rContinue:
    return y;
}

FOCAL
int
write(int job, 
  __builtin_int_t count, struct iovec * iov, 
  const char * utf8file, 
  AsyncJob completion
)
{  int y=0;
    int fd = open(utf8file, O_CREAT | O_TRUNC | O_WRONLY | O_NOFOLLOW | O_EXLOCK, 0666); /* Locks possilby like `flock`. */
    if (fd == -1) { return -1; }
    Ongoing & ongoing = ongoings[job]; aiocb & cb = ongoing.cb;
    Clear8Memory(ByteAlignedRef(&cb),sizeof(aiocb));
    cb.aio_fildes = fd;
    cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    cb.aio_sigevent.sigev_signo = SIGUSR2;
    cb.aio_sigevent.sigev_value.sival_int = job;
    iovec * recio = (iovec *)malloc(count*sizeof(iovec)); /* new iovec[count]; */
    Copy8Memory(ByteAlignedRef(recio), ByteAlignedRef(iov), count*sizeof(struct iovec));
    ongoings[job] = { cb, { count, recio, 0 }, fd, completion, false, false };
    /* Note also possible to store `count` down-to `0` as well as disjunct unrelated 'tiles'. */
    if (chained_write(job)) { return -1; }
    goto err₂𝘖rContinue;
err₁:
    if (close(fd)) { return -1; }
err₂𝘖rContinue:
    return y;
}

void InitIO()
{
    /* struct sigaction sa, sa_old;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = didReadWriteOrSync;
    if (sigaction(SIGUSR2, &sa, &sa_old) < 0) { return -1; } */ /* #include <signal.h> */
    signal(SIGUSR2,didReadWriteOrSync);
    for (int i=0; i<Ongoing::Maxjobs; i++) {
      ongoings[i].completed = true;
    }
}

#pragma mark - Syncronous helpers

FOCAL int syncronous_write(int job, 
  __builtin_int_t count, struct iovec * iov, 
  const char * utf8file, AsyncJob polling)
{  auto completion = ^{ };
    if (write(job, count, iov, utf8file, completion)) { return -1; }
    Ongoing & ongoing = ongoings[job]; aiocb & cb = ongoing.cb;
    while (aio_error(&cb) == EINPROGRESS) { polling(); }
    return 0;
}

FOCAL int syncronous_read(int job, const char * utf8file, 
  __builtin_int_t count, struct iovec * iov, AsyncJob polling
) {  auto completion = ^{ };
    if (read(job, utf8file, count, iov, completion)) { return -1; }
    Ongoing & ongoing = ongoings[job]; aiocb & cb = ongoing.cb;
    while (aio_error(&cb) == EINPROGRESS) { polling(); }
    return 0;
}

#pragma mark - ...and the main entry point:

int
main(
  int argc,
  const char * argv[]
)
{  InitIO(); const char * utf8path = "🥽𝜀📖F².txt";
    const char * message = "The brown fox jumped over the lazy dog.";
    AsyncJob polling=^{ print("Processing...\n"); };
    
    int ᵚjob; if (O₍1₎Acquire(&ᵚjob)) { return 1; }
    __builtin_int_t 🥈 count=3; struct iovec writes[count] = { 
      { (char *)(message+1), 2 }, { (char *)(message+5), 3 }, { (char *)(message+15), 4 }
    };
    if (syncronous_write(ᵚjob,count,writes,utf8path,polling)) { return 2; }
    
    int ʳjob; if (O₍1₎Acquire(&ʳjob)) { return 3; } char * input[100];
    struct iovec reads[count] = { 
      { (char *)(message+1), 2 }, { (char *)(message+5), 3 }, { (char *)(message+15), 4 }
    };
    if (syncronous_read(ʳjob,utf8path,count,reads,polling)) { return 4; }
    
    return 0;
}


