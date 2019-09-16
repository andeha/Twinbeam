/*  Virtual.cpp — Memory low-Hz, high-fps. */

#define LOCATION_UNIMPORTANT (vm_address_t)0 /* To indicate `Field` wherever. */

enum Ring { RING_UNAVAILABLE, RING_READ, RING_FULLACCEESS };

typedef __builtin_uint_t vm_address_t;

#ifdef __x86_64__
#include <mach/mach.h>
#include <mach/task.h>
#include <mach/mach_vm.h>
#include <mach/vm_statistics.h>
#include <sys/mman.h>
#elif defined __mips__
#include <pic32mzda.hpp>
#endif

/**
  
  Create a field initialized with zeroes having an initial and maximally
  allowed relaxation level encoded as: 0=NONE, 1=READ-ONLY, 2=WRITE-ALSO.
  
 */

void *
Field(
  vm_address_t proposed,
  __builtin_int_t size,
  bool copyOnWrite = false,
  Ring initial = RING_UNAVAILABLE,
  Ring max = RING_UNAVAILABLE,
  __builtin_int_t offset = 0,
  bool flow = true,
  bool expandable = false /* Wrong additional level of indirection. */
)
{
#ifdef __x86_64__
    return malloc(size);
#elif defined __mips__
    return malloc(size);
#endif
}

/**
  
  If initially allowed, laxes the protection of a memory region
  to `ring++`.
  
 */

void
Relax(
  void *base,
  __builtin_int_t bytes
)
{
    
#ifdef __x86_64__
    
    kern_return_t err =
        vm_protect(
            mach_task_self(),
            (vm_address_t)result.field,
            (vm_size_t)result.fieldsize,
            (boolean_t)false,
            result.currentRing ? 3 : 1
        );
    
    if (err != KERN_SUCCESS) { return -1; }
    
#elif defined __mips__
#endif
    
    return 0;
}

/**
  
  Restrict temporal spread of a memory region.
  
 */

int
Forget(
  void *base,
  __builtin_int_t bytes,
  bool reversable = false
)
{
    
#ifdef __x86_64__
    
    kern_return_t err =
        vm_protect(
            mach_task_self(),
            (vm_address_t)base,
            (vm_size_t)size,
            !reversable,
            VM_PROT_NONE
        );
    
    if (err != KERN_SUCCESS) { return -1; }
    
    if (!reversable) {
        
        err = vm_deallocate(
            mach_task_self(),
            (vm_address_t)base,
            (vm_size_t)size
        );
        
        if (err != KERN_SUCCESS) { return -1; }
        
    }
    
#elif defined __mips__
#endif
    
    return 0;
}

/**
  
  Restrict overwrite ability of a memory region.
  
 */

void
Freeze(
  void *base,
  __builtin_int_t bytes
)
{
    
#ifdef __x86_64__
    
    kern_return_t err =
        vm_protect(
            mach_task_self(),
            (vm_address_t)base,
            (vm_size_t)bytes,
            true,
            VM_PROT_READ
        );
    
    if (err != KERN_SUCCESS) { return -1; }
    
#elif defined __mips__
#endif
    
    return 0;
}

