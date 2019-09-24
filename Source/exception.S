/*  exception.S | For Unicode parsers and product-related matters. */

#ifdef __mips__

#define v0   $2   /* The 'returned value' of a subroutine. Also in v1 when two words are required. */
#define a0   $4   /* Integer argument register: Pass 64-bit values in a register pair. For little-endian: a1:a0 and a3:a2. */
#define a1   $5   /* Second argument. The first four args are passed in regs. */
#define t0   $8   /* Temporary register that must not be preserved. */
#define s0  $16   /* Saved registers, 𝘪․𝘦 function prologue copies …*/
#define s1  $17   /* the register value to the stack frame and the …*/
#define s2  $18   /* function epilogue copies the values back to the register. */
#define s3  $19
#define s4  $20
#define s5  $21
#define s6  $22
#define s7  $23
#define s8  $24
#define sp  $29   /* The last pushed argument on the stack. */
#define ra  $31   /* The address to return to when inside a function. */
/* See [Wiki]--<🔬 Twinbeam Intricacies> for more info. */ 
    
    
    .text
    .set noreorder
    
 /*  
  *  int setjmp2(jmp_buf jb)
  *  
  *  Persists a processor context in a `jmp_buf` for reinitation 
  *  if/when a `longjmp2` is called.  Saves the current state so 
  *  a thread can return again from the call later.
  *  
  *  A `longjmp2` before a finalized `setjmp2` results in an
  *  undefined behavior.
  */
    
    .globl setjmp2
    .type setjmp2,@function
    .ent setjmp2
    
setjmp2:
    
   /*  The argument `jmp_buf` is referenced in register `a0`.  We 
      must save s0-s8, sp, and ra. To store more registers, adjust 
      the definition of --<Twinbeam.h>{`jmp_buf2`}.  Let's save 
      registers: */
    
    sw sp, 0(a0)        /*  Save registers. */
    sw ra, 4(a0)
    sw s0, 8(a0)
    sw s1, 12(a0)
    sw s2, 16(a0)
    sw s3, 20(a0)
    sw s4, 24(a0)
    sw s5, 28(a0)
    sw s6, 32(a0)
    sw s7, 36(a0)
    sw s8, 40(a0)
    
    j ra                /*  Return to caller. */
    li v0, 0            /*  Return 0 (via the 'delay slot'). */
    
.end setjmp2
  
  
 /*                         (Code updated to `__builtin_int_t`)
  *  
  *  void longjmp2(jmp_buf jb, int code)
  *  
  *  Return to the location specified by a former `setjmp2`.
  */
    
    .globl longjmp2
    .type longjmp2,@function
    .ent longjmp2
    
longjmp2:
    
   /*  Once again, `jmp_buf` is pointed out in a0, this time 
     the return code to be read from `setjmp2` is in a1.  We have 
     to restore s0-s8, sp, and ra from the jmp_buf.  The return 
     code is forced to 1 if 0 is passed in. */
    
    sltiu t0, a1, 1    /*  Set t0 to 1 if return code is 0... otherwise 0 */
    addu a1, a1, t0    /*  Update the return code. */
    
    lw sp, 0(a0)       /*  Restore registers. */
    lw ra, 4(a0)
    lw s0, 8(a0)
    lw s1, 12(a0)
    lw s2, 16(a0)
    lw s3, 20(a0)
    lw s4, 24(a0)
    lw s5, 28(a0)
    lw s6, 32(a0)
    lw s7, 36(a0)
    lw s8, 40(a0)
    
    j ra              /*  Return to where `setjmp2` was called from. */
    move v0, a1       /*  Set return value. */
    
.end longjmp2

#elif defined __x86_64__

 /***
  
  int setjmp2(jmp_buf jb);
  
  ***/
    
    .text
    .global _setjmp2
    
_setjmp2:
    
    movq    %rdi,%rax
    movq    0(%rsp),%rdx
    movq    %rdx, 0(%rax)
    movq    %rbx, 8(%rax)
    movq    %rsp,16(%rax)
    movq    %rbp,24(%rax)
    movq    %r12,32(%rax)
    movq    %r13,40(%rax)
    movq    %r14,48(%rax)
    movq    %r15,56(%rax)
    
    fnstcw  64(%rax)
    stmxcsr 68(%rax)
    xorq    %rax,%rax
    
    ret
    
 /***
  
  void longjmp2(jmp_buf jb, int code);
  
  ***/
    
    .global _longjmp2
    
_longjmp2:
    
    movq    %rdi,%rdx
    stmxcsr -4(%rsp)
    movl    68(%rdx),%eax
    andl    $0xffffffc0,%eax
    movl    -4(%rsp),%edi
    andl    $0x3f,%edi
    xorl    %eax,%edi
    movl    %edi,-4(%rsp)
    ldmxcsr -4(%rsp)
    movq    %rsi,%rax
    movq    0(%rdx),%rcx
    movq    8(%rdx),%rbx
    movq    16(%rdx),%rsp
    movq    24(%rdx),%rbp
    movq    32(%rdx),%r12
    movq    40(%rdx),%r13
    movq    48(%rdx),%r14
    movq    56(%rdx),%r15
    
    fldcw   64(%rdx)
    testq   %rax,%rax
    jnz     1f; incq    %rax; 1: movq    %rcx,0(%rsp)
    
    ret
    
#endif
