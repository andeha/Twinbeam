/*  llvmʳᵗ².cpp - Middle version that manages dynamic memory. */

#include <Twinbeam.h>

void * _NSConcreteStackBlock[32];
void * _NSConcreteGlobalBlock[32];

void * operator new(size_t size) { return Alloc(size); }
void operator delete(void * p) { Fall⒪⒲﹠o(p); }
/* The abstractions `Alloc` and `Fall⒪⒲﹠o` are non-overloadable in C++. */

