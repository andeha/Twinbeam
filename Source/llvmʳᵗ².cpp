/*  llvmʳᵗ².cpp - Middle version that manages dynamic memory. */

#include <Twinbeam.h>

void * _NSConcreteStackBlock[32];
void * _NSConcreteGlobalBlock[32];

void * operator new(size_t size) { return Alloc(size); }
void operator delete(void * p) { Fallow₋ₒ(p); }
/* The abstractions `Alloc` and `Fallow₋ₒ` are non-overloadable in C++. */

