/*  µ⃝-code-and-intel.cxx | print assembly for Intel x86-64. */

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

void codegenerate()
{ struct dynamic₋bag * item=form; struct Unicodes symbol;
   print(
"#define END(symbol)\n"
"#define START(symbol)\n\n"
"    .data\n"
"abc: .ascii \"ABC\\n\"\n\n"
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
"_⬚:\n"
"    sub   24,rsp\n"
"    fnstcw 64[rax]\n"
"    add   24,rsp\n"
"    ret\n"
"    /* END(_⬚) */\n", 
   ﹟S(symbol),﹟S(symbol),﹟S(symbol),﹟S(symbol),﹟S(symbol));
   item=item->next; goto again;
}

/* ./a.out | clang -c -x assembler - -o - */
/* ▚ ld -arch x86_64 /dev/stdin */ /* not-possible random-access required. */

