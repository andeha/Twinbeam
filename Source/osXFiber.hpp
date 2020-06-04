#ifdef POSIX_FIBER
#define _XOPEN_SOURCE
#include <ucontext.h>
#undef LEAF
#define LEAF
#endif
