/*  llvmʳᵗ².cpp - Middle manages dynamic memory unfortunately. */

#include <Twinbeam.h>

void * _NSConcreteStackBlock[32];
void * _NSConcreteGlobalBlock[32];

void * operator new(size_t size) { return Alloc(size); }
void operator delete(void * p) { Fallow(p); }

