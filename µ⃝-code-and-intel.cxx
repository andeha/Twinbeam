/*  µ⃝-code-and-intel.cxx | assembly for Intel x86-64. */

void codegenerate()
{ dynamic₋bag * item=list;, struct Unicodes symbol;
   print(
"#define END(symbol)\n"
"#define START(symbol)\n"
"    .section .text\n"
   );
again:
   symbol = { 5, U"HELLO" };
   if (item==ΨΛΩ) { return; }
   print(
"    .globl _⬚"
"    .type _⬚,@function"
"    START(_⬚)"
"_⬚:"
"    fnstcw 64(%rax)"
"    ret"
"    END(_⬚)"
   ﹟S(symbol),﹟S(symbol),﹟S(symbol),﹟S(symbol),﹟S(symbol));
   item=item->next; goto again;
}

