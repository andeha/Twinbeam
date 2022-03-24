/*  church-pass.S | with a modern argument in 'longjmp'. */

#if defined __mips__

#define START(name) .set at; .set noreorder; .ent name
#define END(name) .size name,.-name; .end name; .set reorder; .set noat
    
    
    .section .text
    
 /*  
  *  int setjmp2(jmp_buf jb)
  *  
  *  Persists a processor context in a `jmp_buf` for reinitation 
  *  if and when a `longjmp2` is called.  Saves the current state so 
  *  a thread can return again from the call later.
  *  
  *  A `longjmp2` before a finalized `setjmp2` results in an
  *  undefined behavior.
  *  
  *  The argument 'jmp_buf' is referenced in register a0.  We 
  *  must save s0-s8, sp, and ra. To store more registers, adjust 
  *  the definition of --<Twinbeam.h>{`jmp_buf2`}.  Let us save the 
  *  registers:
  */
    
    .globl setjmp2
    .type setjmp2,@function
     START(setjmp2)
setjmp2:
    
    sw       $sp, 0($a0)                /*  save registers in 'jmp_buf'. */
    sw       $ra, 4($a0)
    sw       $s0, 8($a0)
    sw       $s1, 12($a0)
    sw       $s2, 16($a0)
    sw       $s3, 20($a0)
    sw       $s4, 24($a0)
    sw       $s5, 28($a0)
    sw       $s6, 32($a0)
    sw       $s7, 36($a0)
    sw       $s8, 40($a0)
    
    j        $ra                        /* return to caller. */
    li       $v0, 0                     /* return zero (via the delay slot). */
    
    END(setjmp2)
  
  
 /*                         (code updated for '__builtin_int_t')
  *  
  *  void longjmp2(jmp_buf jb, int code)
  *  
  *  Once again, 'jmp_buf' is pointed out in a0, this time 
  *  the return code to be read from 'setjmp2' is in a1.  We have 
  *  to restore s0-s8, sp, and ra from the jmp_buf.  The return 
  *  code is forced to 1 if 0 is passed in.
  *  
  *  Return to the location specified by a former `setjmp2`.
  */
    
    .globl longjmp2
    .type longjmp2,@function
     START(longjmp2)
longjmp2:
    
    sltiu    $t0, $a1, 1                /* set t0 to 1 if return code is 0... otherwise 0 */
    addu     $a1, $a1, $t0              /* update the return code. */
    
    lw       $sp, 0($a0)                /* restore registers. */
    lw       $ra, 4($a0)
    lw       $s0, 8($a0)
    lw       $s1, 12($a0)
    lw       $s2, 16($a0)
    lw       $s3, 20($a0)
    lw       $s4, 24($a0)
    lw       $s5, 28($a0)
    lw       $s6, 32($a0)
    lw       $s7, 36($a0)
    lw       $s8, 40($a0)
    
    j        $ra                        /* return to where 'setjmp2' was called from. */
    move     $v0, $a1                   /* set return value. */
    
    END(longjmp2)

#elif defined __x86_64__

#define END(symbol)
#define START(symbol)

 /***
  
  int setjmp2(jmp_buf jb).
  
  ***/
    
    .text
    .global _setjmp2
    START(_setjmp2)
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
    xorq    %rax,%rax         /* return 0 in rax. */
    
    ret
    END(_setjmp2)

 /***
  
  void longjmp2(jmp_buf jb, __builtin_int_t code).
  
  ***/
    
    .global _longjmp2
    START(_longjmp2)
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
    END(_longjmp2)

#endif

