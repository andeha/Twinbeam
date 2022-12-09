/*  µ⃝-code-and-intel.cxx | print assembly for Intel x86-64. */

void generate₋arithmetic(struct dynamic₋bag * left, struct dynamic₋bag * right, enum symbol₋class type)
{
   print(
"     "
   );
   switch (type)
   {
   case times: print("mul,imul"); break;
   case divide: print("div,idiv"); break;
   case plus: print("ad(c)d"); break;
   case minus: print("s(b)ub"); break;
   default: error(4,"unknown operation"); break;
   }
   print(" rax,rbx\n");
}

void generate₋cast(struct dynamic₋bag * computation)
{
   print(
"     cwb,cwde,cwd,cdq"
   );
}

void generate₋assign(struct dynamic₋bag * becomes)
{
   print(
"    movq rdi,rax\n"
   );
}

void generate₋condition(struct dynamic₋bag * select)
{ struct guid ident=Guid(); 
   print(
"    testq rax,rax\n"
"    jz sometime₋⬚\n"
"sometime₋⬚:\n",
   ﹟leap(ident),﹟leap(ident));
   print(
"either₋⬚:\n",
   ﹟leap(ident));
}

void generate₋loop(struct dynamic₋bag * etery)
{ struct guid ident=Guid(); 
   print(
"⬚:\n"
"    jmp ⬚\n", ﹟leap(ident), ﹟leap(ident));
}

void generate₋call(struct dynamic₋bag * send₋to₋recieve)
{ struct Unicodes callee=send₋to₋recieve->episod;
   print(
"    call  ⬚\n", 
   ﹟S(callee.tetras,callee.unicodes));
}

void requisi₋automat(int count)
{ char * registers[] = { "rax", "r15", "r14", "r13", "r12", "rbx", "rbp", "r9", "r8", "rcx", "rdx", "rsi", "rdi" };
   return &registers[13-count];
}

void preserve(int restore, int count, ...)
{ char * register₋name; int i=0; va_prologue(count)
again:
   if (i >= count) { goto unagain; }
   register₋name = va_unqueue(char *);
   if (restore) { print(
"    pop ⬚\n", ﹟s7(register₋name)
   ); }
   else { print(
"    push ⬚\n", ﹟s7(register₋name)
   ); }
   goto again;
unagain:
   va_epilogue
}

void codegenerate()
{ struct dynamic₋bag * item=form; struct Unicodes symbol;
   print(
"#define END(symbol)\n"
"#define START(symbol)\n\n"
"    .data\n"
"abc: .long /* .quad .uleb128 */ 0x41,0x44,0\n\n"
"    .text\n\n"
   );
again:
   symbol = Run(U"HELLO");
   if (item==ΨΛΩ) { return; }
   print(
"    .globl _⬚\n"
"    /* .type _⬚,@function */\n"
"    .intel_syntax\n"
"    /* START(_⬚) */\n"
"_⬚:\n",﹟S(symbol),﹟S(symbol),﹟S(symbol),﹟S(symbol));
   preserve(0,1,"rbx");
   print(
"    sub   24,rsp\n"
/* rdi, rsi, rdx, rcx, r8, r9 then right to left pushed. */
"    fnstcw 64[rax]\n"
"    mov   13,rax\n"
"    add   24,rsp\n"
   );
   preserve(1,1,"rbx");
   print(
"    ret\n"
"    /* END(_⬚) */\n", 
   ﹟S(symbol));
   item=item->next; goto again;
}

/* ./a.out | clang -c -x assembler - -o - */
/* ▚ ld -arch x86_64 /dev/stdin */ /* not-possible random-access required. */

