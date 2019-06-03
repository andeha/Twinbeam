/*  llvmʳᵗ³.cpp - Compiler when blocks, dynamic memory and an UART are required. */

#include <Twinbeam.h>

void * _NSConcreteStackBlock[32];
void * _NSConcreteGlobalBlock[32];

auto Alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };
auto Fallow = ^(void * p) { free(p); };

void * operator new(size_t size) { return Alloc(size); }
void operator delete(void * p) { Fallow(p); }

#ifdef __x86_64__
extern "C" int write(int fd, const char *s, short unsigned b);
auto Putₒ = ^(char * utf8s, unsigned short bytes) {
  // extern "C" int write(int fd, const char *s, short unsigned b); /* 𝘈․𝘬․a #include <unistd.h> */
  write(1, utf8s, bytes);
};
#endif

/* See --<Fossilate.h|cpp> for additional prepacked lambdas. */

