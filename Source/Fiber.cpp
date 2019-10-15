/*  Fiber.cpp | Nutty, yet interesting in detail. */

#include <Twinbeam.h>

namespace Fiber {

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

/* See also MIPS_VIRTUAL_MULTITHREADED and MIPS_MCU_AUTOMATIC_PROLOG_EPILOG_IRQ. */

int
Recall(
  const Peel *ucp
)
{ /* todo: Exercise '.set  symbol, $a0' and '#define arg1 %rsi' later. */
    
#ifdef POSIX_FIBER
    return setcontext(&ucp->ctx);
#elif defined __x86_64__ && !defined __AAPL__
    
  IntelPlusATT👉
     movq    16(%rdi), %rsi   /* Retrieve formerly stored register values. */
     movq    24(%rdi), %rdx
     movq    32(%rdi), %rcx
     movq    40(%rdi), %r8
     movq    48(%rdi), %r9
     movq    56(%rdi), %rax
     movq    64(%rdi), %rbx
     movq    72(%rdi), %rbp
     movq    80(%rdi), %r10
     movq    88(%rdi), %r11
     movq    96(%rdi), %r12
     movq   104(%rdi), %r13
     movq   112(%rdi), %r14
     movq   120(%rdi), %r15
     movq   184(%rdi), %rsp
     pushq  160(%rdi)            /* The new/old `rip` is stored. */
     movq    8(%rdi), %rdi
  }
   
#elif defined __mips__
   
   Mips
 "    lw  $16, 72($4)       \n"       /* Restore register values: */
 "    lw  $17, 76($4)       \n"
 "    lw  $18, 80($4)       \n"
 "    lw  $19, 84($4)       \n"
 "    lw  $20, 88($4)       \n"
 "    lw  $21, 92($4)       \n"
 "    lw  $22, 96($4)       \n"
 "    lw  $23, 100($4)      \n"
     
 "    lw  $28, 120($4)      \n"     /* $28 = gp = Global pointer. */
 "    lw  $29, 124($4)      \n"     /* $29 = sp = Stack pointer.  */
 "    lw  $30, 128($4)      \n"     /* $30 = fp = Frame pointer.  */
     
    /*
       
       If we set $31 directly and j $31, we would loose the outer
       return address. Use a temporary register, then.
       
     */
     
 "    lw  $8, 132($4)       \n"     /* $8 = ra = Return address. */
     
     /*  Bug: not setting the pc causes a bus error. */
 "    lw  $25, 132($4)      \n"    /* $25 = pc = Program counter. */
     
 "    lw  $5, 28($4)        \n"
 "    lw  $6, 32($4)        \n"
 "    lw  $7, 36($4)        \n"
 "    lw  $4, 24($4)        \n"
     
 "    j  $8                 \n"
 "    nop                   \n"
   );
    
#else
#error "Unsupported platform. Kindly improve behaviour while continue prototyping."
#endif
   
   return 0;
   
} /* See also --<exception.S>. Also known as `RecallState`. */

int
Snapshot(
  Peel *ucp
) /*  In the System V AMD64 ABI, the first six pointer/integer arguments are
  passed in rdi, rsi, rdx, rcx, r8, r9. In the MIPS ABI, the first integer 
  argument is found in a0 a․𝘬․a `$4`. */
{
    
#ifdef POSIX_FIBER
    
    return getcontext(&ucp->ctx);
    
#elif defined __x86_64__ && !defined __AAPL__
    
  Intel👈 /* No .intel_syntax implies AT&T. */
     mov    8[rdi],  rdi // FIXME: According to belief: noprefix = unprefixed registers, otherwise '%rip'.
     mov   16[rdi],  rsi
     mov   24[rdi],  rdx
     mov   32[rdi],  rcx
     mov   40[rdi],  r8
     mov   48[rdi],  r9
     mov qword ptr 56[rdi],  1    /* rax */
     mov   64[rdi],  rbx
     mov   72[rdi],  rbp
     mov   80[rdi],  r10
     mov   88[rdi],  r11
     mov   96[rdi],  r12
     mov  104[rdi],  r13
     mov  112[rdi],  r14
     mov  120[rdi],  r15
     
     mov       rcx, [rsp]         /* rip = 64-bit instruction pointer. */
     mov  160[rdi],  rcx
     lea       rcx, 8[rsp]        /* rsp = 64-bit stack pointer. */
     mov  184[rdi], rcx
     
     mov       rcx, 32[rdi]       /* Restore rcx */
     mov       rax, 0
  };
    
#elif defined __mips__
    
  Mips
 "   sw  $4, 24($4)         \n"       /* Branch state into non-volatile memory. */
 "   sw  $5, 28($4)         \n"
 "   sw  $6, 32($4)         \n"
 "   sw  $7, 36($4)         \n"
    
 "   sw  $16, 72($4)        \n"
 "   sw  $17, 76($4)        \n"
 "   sw  $18, 80($4)        \n"
 "   sw  $19, 84($4)        \n"
 "   sw  $20, 88($4)        \n"
 "   sw  $21, 92($4)        \n"
 "   sw  $22, 96($4)        \n"
 "   sw  $23, 100($4)       \n"
    
 "   sw  $28, 120($4)       \n"      /* Global pointer */
 "   sw  $29, 124($4)       \n"      /* Stack pointer */
 "   sw  $30, 128($4)       \n"      /* Frame pointer */
 "   sw  $31, 132($4)       \n"      /* Return address */
    
 "   xor $2, $2, $2         \n"      /* Clear $2 */
 "   j   $31                \n"
 "   nop                    \n"
  );
    
#else
#error "Unsupported platform. Please stand by whilest other hearken."
#endif
    
   return 0;
    
}

void
Incubate(
  Peel *ucp,
  void (*ufnc)(...), int argc, ...
/* …and not `fuContext *ctx, void(^job)(void * ctx₂)` since we're initially
  doing cooperative multitask. (`Peel` nowdays.) */
)
{
#ifdef POSIX_FIBER
    void *arg = 0;
    va_prologue(argc)
    if (argc > 0) { arg = __builtin_va_arg(__arg, void *); }
    va_epilogue
    makecontext(&ucp->ctx, (void (*)())ufnc, 1, arg); // __builtin_va_list fed into `...`
#elif defined __x86_64__ && !defined __AAPL__ /* The __m128 type requires the stack frame to be aligned to a 16-byte boundary. */
    Clear8Memory((ByteAlignedRef)(&ucp->ctx.cpu), sizeof(ucp->ctx.cpu));
    /* On macOS, the first six 64-bit pointer/integer parameters are passed via
      `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`. */
    int 🥈 RDI=1, RSI=2, RDX=3, RCX=4;
    va_prologue(argc)
    if (argc > 0) { ucp->ctx.cpu.intel.regs[RDI] = __builtin_va_arg(__arg, __builtin_uint_t); }
    if (argc > 1) { ucp->ctx.cpu.intel.regs[RSI] = __builtin_va_arg(__arg, __builtin_uint_t); }
    if (argc > 2) { ucp->ctx.cpu.intel.regs[RDX] = __builtin_va_arg(__arg, __builtin_uint_t); }
    if (argc > 3) { ucp->ctx.cpu.intel.regs[RCX] = __builtin_va_arg(__arg, __builtin_uint_t); }
    va_epilogue
    uint8_t *sp = Frame(ucp->ctx.rtstk + ucp->ctx.bytesStk, 16);
    sp -= argc;
    *--sp = 0; /* Return address */
    ucp->ctx.cpu.intel.rsp = (__builtin_uint_t)sp;
    ucp->ctx.cpu.intel.rip = (__builtin_uint_t)ufnc;
#elif defined __mips__
    uint8_t * sp = ucp->ctx.rtstk + ucp->ctx.bytesStk;
    Clear8Memory((ByteAlignedRef)&(ucp->ctx.cpu.mips), sizeof(ucp->ctx.cpu.mips));
    va_prologue(argc)
    /* On MIPS, the first four 32-bit pointer/integer parameters are located in
       register $4 - $7 a․𝘬․a a0 - a3. */
    for (int i = 0; i < min(4, argc); i++) { ucp->ctx.cpu.mips.gprs[i+4] = __builtin_va_arg(__arg, __builtin_int_t); }
    va_epilogue
    ucp->ctx.cpu.mips.gprs[29] = (__builtin_uint_t)sp;
    ucp->ctx.cpu.mips.gprs[31] = (__builtin_uint_t)ufnc;
#endif
}

}
