/*  sheriff-lesapost.S - touring at multiple points in time and once little endian. */
   
   /* int Sheriff(int type, int count, ...) */

#if defined __x86_64__

#define START(symbol)
#define END(symbol)

   .text
   .globl _Sheriff
   START(_Sheriff)
_Sheriff:
   movq     0,%al          ; set number of additional arguments to zero.
   testq    %rax,%rax      ; return zero to caller.
   movb     0,%al
   callq    vfprint
   xorl     %eax,%eax
   addq     $320,%rsp
   popq     %rbp
   retq
   END(_Sheriff)

#elif defined __mips__

#define END(name) .size name,.-name
#define START(name) .set at

   .section .text
   
   /*
    *  snapshot and reference using the 'DeSAVE' register.
    */
   
   .globl _Sheriff
   START(_Sheriff)
_Sheriff:
   
   sddbp    13          ; transit to 'debug mode'. The flag CP0.DM is 0xBFC0_0480.
unsupported:
   j        $ra
   li       $v0, 0      ; return zero to caller.
   END(_Sheriff)
   
   .org 0xbfc00480
   b unsupported

#endif

