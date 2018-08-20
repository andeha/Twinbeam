//
//  ModernTask.h
//  Additions
//

#ifndef __MODERNTASK_H
#define __MODERNTASK_H

#include <Twinbeam.h>

struct Multitasks {
    
    typedef uint8_t CpuState[512] __attribute__((aligned(16)));
    
    typedef struct Task {
        __builtin_uint_t rip;
        __builtin_uint_t rsp;
        __builtin_uint_t stack_size;
        // libthread_ucontext fiber;
        CpuState state;
        jmp_buf2 exception;
        bool stop;
        Task * next; } Task;
    
    Task *first, *last; // State necklace.
    
};

namespace SlimScheduler {
    
    void Create(void (*fnc)(void *), void * ctx);
    
    // TODO: Add Map<String, CpuStateNode *> and Guid to get rid of pointer.
    
    void Stop(Multitasks::Task task);
    
    void Init();
    
    void Start();
    
}

#endif
