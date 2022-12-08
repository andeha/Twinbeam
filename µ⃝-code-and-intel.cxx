/*  µ⃝-code-and-intel.cxx | print assembly for Intel x86-64. */

void codegenerate()
{ struct dynamic₋bag * item=form; struct Unicodes symbol;
   print(
"/*  stdout.S | material entered on stdin and fed to µ-parse. */\n\n"
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
"    fnstcw 64[rax]\n"
"    ret\n"
"    /* END(_⬚) */\n", 
   ﹟S(symbol),﹟S(symbol),﹟S(symbol),﹟S(symbol),﹟S(symbol));
   item=item->next; goto again;
}

/* ./a.out | clang -c -x assembler - -o - */

