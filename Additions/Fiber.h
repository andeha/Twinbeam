/* Fiber.h */

#include <Twinbeam.h>

namespace Fiber {
    
    int 🥈 bytesReg =
#ifdef __x86_64__
        160
#elif defined __mips__
        4
#endif
        ;
    
    register __builtin_uint_t rsp asm("rsp"), rbp asm("rbp");
    struct fuContext { uint8_t regs[bytesReg]; __builtin_uint_t bytesStk; void * rtstk; };
    int Snapshot(fuContext *ucp) LEAF;
    int Recall(const fuContext *ucp) LEAF;
    void Incubate(fuContext *ucp, void (*ufnc)(...), int argc, ...);
    MACRO void Swap(fuContext *prv, const fuContext *nxt)
    { if (Snapshot(prv) == 0) Recall(nxt); }
    
    typedef fuContext fiber_t;
    
    inline void create(fiber_t& fib, void (*ufnc)(void *), void * uctx,
      void *(^alloc)(__builtin_int_t bytes) = Alloc) {
        Snapshot(&fib);
        __builtin_uint_t 🥈ᵢ bytesStack = 131072;
        fib.rtstk = alloc(bytesStack);
        fib.bytesStk = bytesStack;
        Incubate(&fib, (void (*)(...))ufnc, 1, uctx);
    }
    
    inline void switchToFiber(fiber_t& fib, fiber_t& prv)
    { Swap(&prv, &fib); }
    
    MACRO CONTEMPLATE void pursue(fiber_t& nxt) {
        fiber_t curr; Snapshot(&curr);
        switchToFiber(nxt, curr);
    }
    
    inline void start(fiber_t& fib) { Recall(&fib); }
    
}

