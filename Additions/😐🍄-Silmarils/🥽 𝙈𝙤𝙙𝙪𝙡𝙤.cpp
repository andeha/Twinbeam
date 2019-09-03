/*  🥽 𝙈𝙤𝙙𝙪𝙡𝙤.cpp | Round and around again. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

/* clang++ -g -o Modulo -I ../../ -fno-rtti -fblocks -fms-extensions       \
    -fno-exceptions -std=c++2a ../Presentᵃᵘˣ.cpp ../../Source/Utf8.cpp      \
   ../Utf8Terminal.cpp ../../Source/llvmʳᵗ³.cpp ../../Source/System.cpp    \
   ../../Source/Memory.cpp ../Additions.cpp '🥽 𝙈𝙤𝙙𝙪𝙡𝙤.cpp' */

int
modulo(
  int a, int n,
  int &r₁, int &rˡᵖʳ /* ...also the 'least possible residue'. */ 
)
{  int ⁿsign = n < +0 ? -1 : 1;
    if (n == 0) return -1; r₁ = a % n;
    rˡᵖʳ = r₁ >= -0 ? r₁ : r₁ + ⁿsign*n;
    return 0;
}

int
ᵖᵃˢmod(
  int a, int n,
  void (^undefined)()
)
{
   if (n == 0) { undefined(); }
   int ⁿsign = n < +0 ? -1 : 1, r = a % n;
   /* May never be reached when n = 0. */
   return r >= -0 ? r : r + ⁿsign*n;
}

int
ᵈᵉfmod(
  int a, int n,
  void (^undefined)()
) /* The Mips instruction `MODU`/`MOD`. */ 
{ int ⁿsign = a < +0 ? -1 : 1;
    if (a < +0) { a = -a; }
    if (n == 0) { undefined(); }
    if (n < +0) { n = -n; }
    return ⁿsign*(a - n*(a/n));
} /* The `IDIV`/`DIV` returns a quotient and a remainder. A non-integral 
  quotient are unrelated to x87FCW, x87FSW and MXCSR on Intel truncated 
  towards `0`. Note that division by zero may occur. */

// ✁ until ✂️

#pragma mark - x87 FPU Control

BITMASK (uint32_t) { /* x87 FPU Control */
  INTEL_FCW_X = 0b1<<12,   // Infinity Control
  INTEL_FCW_RC = 0b11<<10, /* IEEE754 Rounding Control: 0b01='Round towards -∞', 
    default 0b00='Round to nearest'. */
  INTEL_FCW_PC = 0b11<<8,  // Precision Control
  INTEL_FCW_PM = 0b1<<5,   // Precision
  INTEL_FCW_UM = 0b1<<4,   // Underflow
  INTEL_FCW_OM = 0b1<<3,   // Overflow
  INTEL_FCW_ZM = 0b1<<2,   // Zero Divide
  INTEL_FCW_DM = 0b1<<1,   // Denormal Operand
  INTEL_FCW_IM = 0b1<<0    // Invalid Operand
};

Register Intel_x87FCW = {
  { U"INTEL_FCW_X",  INTEL_FCW_X,  U"Infinity Control" },
  { U"INTEL_FCW_RC", INTEL_FCW_RC, U"Rounding Control" },
  { U"INTEL_FCW_PC", INTEL_FCW_PC, U"Precision Control" },
  { U"INTEL_FCW_PM", INTEL_FCW_PM, U"Precision" },
  { U"INTEL_FCW_UM", INTEL_FCW_UM, U"Underflow" },
  { U"INTEL_FCW_OM", INTEL_FCW_OM, U"Overflow" },
  { U"INTEL_FCW_ZM", INTEL_FCW_ZM, U"Zero Divide" },
  { U"INTEL_FCW_DM", INTEL_FCW_DM, U"Denormal Operand" },
  { U"INTEL_FCW_IM", INTEL_FCW_IM, U"Invalid Operand" }
};

AnnotatedRegister AR_Intel_x87FCW = {
  U"FCW: x87 FPU Control",
  9, Intel_x87FCW, 0x00000000,
  U""
};

#pragma mark - x87 FPU Status

BITMASK (uint32_t) { /* x87 FPU Status */
  INTEL_FSW_B = 0b1<<15, // FPU Busy
  INTEL_FSW_C3 = 0b1<<14, // Condition Code
  INTEL_FSW_TOP = 0b111<<11, // Top of Stack Pointer
  INTEL_FSW_C2 = 0b1<<10, // Condition Code
  INTEL_FSW_C1 = 0b1<<9, // Condition Code
  INTEL_FSW_C0 = 0b1<<8, // Condition Code
  INTEL_FSW_ES = 0b1<<7, // Error Summary Status
  INTEL_FSW_SF = 0b1<<6, // Stack Fault
  INTEL_FSW_PE = 0b1<<5, // Precision Exception
  INTEL_FSW_UE = 0b1<<4, // Underflow Exception
  INTEL_FSW_OE = 0b1<<3, // Overflow Exception
  INTEL_FSW_ZE = 0b1<<2, // Zero Divide Exception
  INTEL_FSW_DE = 0b1<<1, // Denormal Operand Exception
  INTEL_FSW_IE = 0b1<<0 // Invalid Operand Exception
};

Register Intel_x87FSW = {
  { U"INTEL_FSW_B",   INTEL_FSW_B,  U"FPU Busy" },
  { U"INTEL_FSW_C3",  INTEL_FSW_C3, U"Condition Code" },
  { U"INTEL_FSW_TOP", INTEL_FSW_TOP, U"Top of Stack Pointer" },
  { U"INTEL_FSW_C2",  INTEL_FSW_C2, U"Condition Code" },
  { U"INTEL_FSW_C1",  INTEL_FSW_C1, U"Condition Code" },
  { U"INTEL_FSW_C0",  INTEL_FSW_C0, U"Condition Code" },
  { U"INTEL_FSW_ES",  INTEL_FSW_ES, U"Error Summary Status" },
  { U"INTEL_FSW_SF",  INTEL_FSW_SF, U"Stack Fault" },
  { U"INTEL_FSW_PE",  INTEL_FSW_PE, U"Precision Exception" },
  { U"INTEL_FSW_UE",  INTEL_FSW_UE, U"Underflow Exception" },
  { U"INTEL_FSW_OE",  INTEL_FSW_OE, U"Overflow Exception" },
  { U"INTEL_FSW_ZE",  INTEL_FSW_ZE, U"Zero Divide Exception" },
  { U"INTEL_FSW_DE",  INTEL_FSW_DE, U"Denormal Operand Exception" },
  { U"INTEL_FSW_IE",  INTEL_FSW_IE, U"Invalid Operand Exception" }
};

AnnotatedRegister AR_Intel_x87FSW = {
  U"FSW: x87 FPU Status",
  14, Intel_x87FSW, 0x00000000,
  U""
};

/* ✂️ << --<shoebox>{x86_64 Flag Registers} ✃ */

#pragma mark - SSE Control and Status

BITMASK (uint32_t) { // MXCSR
  INTEL_MXCSR_FZ  = 0b1<<15, // Flush to Zero
  INTEL_MXCSR_RC  = 0b11<<13, /* IEEE754 Rounding Control: 0b01='Round towards -∞', 
    default 0b00='Round to nearest'. */
  INTEL_MXCSR_PM  = 0b1<<12, // Precision Mask
  INTEL_MXCSR_UM  = 0b1<<11, // Underflow Mask
  INTEL_MXCSR_OM  = 0b1<<10, // Overflow Mask
  INTEL_MXCSR_ZM  = 0b1<<9, // Divide-by-Zero Mask
  INTEL_MXCSR_DM  = 0b1<<8, // Denormal Operation Mask
  INTEL_MXCSR_IM  = 0b1<<7, // Invalid Operation Mask
  INTEL_MXCSR_DAZ = 0b1<<6, // Denormals are Zeros
  INTEL_MXCSR_PE  = 0b1<<5, // Precision Flag
  INTEL_MXCSR_UE  = 0b1<<4, // Underflow Flag
  INTEL_MXCSR_OE  = 0b1<<3, // Overflow Flag
  INTEL_MXCSR_ZE  = 0b1<<2, // Divide-by-Zero Flag
  INTEL_MXCSR_DE  = 0b1<<1, // Denormal Flag
  INTEL_MXCSR_IE  = 0b1<<0 // Invalid Operation Flag
};

Register Intel_MXCSR = {
  { U"INTEL_MXCSR_FZ", INTEL_MXCSR_FZ, U"Flush to Zero" },
  { U"INTEL_MXCSR_RC", INTEL_MXCSR_RC, U"Rounding Control" },
  { U"INTEL_MXCSR_PM", INTEL_MXCSR_PM, U"Precision Mask" },
  { U"INTEL_MXCSR_UM", INTEL_MXCSR_UM, U"Underflow Mask" },
  { U"INTEL_MXCSR_OM", INTEL_MXCSR_OM, U"Overflow Mask" },
  { U"INTEL_MXCSR_ZM", INTEL_MXCSR_ZM, U"Divide-by-Zero Mask" },
  { U"INTEL_MXCSR_DM", INTEL_MXCSR_DM, U"Denormal Operation Mask" },
  { U"INTEL_MXCSR_IM", INTEL_MXCSR_IM, U"Invalid Operation Mask" },
  { U"INTEL_MXCSR_DAZ", INTEL_MXCSR_DAZ, U"Denormals are Zeros" },
  { U"INTEL_MXCSR_PE", INTEL_MXCSR_PE, U"Precision Flag" },
  { U"INTEL_MXCSR_UE", INTEL_MXCSR_UE, U"Underflow Flag" },
  { U"INTEL_MXCSR_OE", INTEL_MXCSR_OE, U"Overflow Flag" },
  { U"INTEL_MXCSR_ZE", INTEL_MXCSR_ZE, U"Divide-by-Zero Flag" },
  { U"INTEL_MXCSR_DE", INTEL_MXCSR_DE, U"Denormal Flag" },
  { U"INTEL_MXCSR_IE", INTEL_MXCSR_IE, U"Invalid Operation Flag" }
};

AnnotatedRegister AR_Intel_MXCSR = {
  U"MXCSR: SSE CONTROL STATUS REGISTER",
  15, Intel_MXCSR, 0x00000000,
  U""
};

Utf8Terminal _myTerminal;

uint64_t x86rflags() { uint64_t rflags; asm volatile("pushfq; popq %0" : "=r" (rflags)); return rflags; }
uint16_t x87control() { short cw; asm ("fstcw %w0" : "=m" (cw)); return cw; }
uint16_t x87status() { short sw; asm("fstsw %w0" : "=m" (sw)); return sw; }
void x87control(const uint16_t val) { asm volatile("fldcw %0;"::"m"(val)); }
/* Requires '-fms-extensions' */
/* Persists FSW, FCW, MXCSR, ST0/MM0-ST7/MM7, XMM0-XMM7: */
void ⁵¹²fxsave(uint8_t * aligned16) { Intel👈 fxsave aligned16 } }
void ⁵¹²fxrstore(uint8_t * aligned16) { Intel👈 fxrstor aligned16 } }
/* ⬷ Unfortunately not `𝟷𝟼aligned`? */

#include <stdio.h>

void FPE(int sig) { printf("Integer division by zero\n"); }

int
main(
  int argc,
  const char * argv[]
)
{ int r₁, rˡᵖʳ;
    Intel👈 finit }
    auto error = ^{ printf("error\n"); };
    if (SIG_ERR == signal(SIGFPE, FPE)) { return -1; }
    uint64_t rflags=x86rflags(), csr₁=_mm_getcsr();
    uint32_t x87fcw₁=x87control(), x87fsw=x87status();
    Present(Termlog, AR_Intel_x87FCW, x87fcw₁);
    Present(Termlog, AR_Intel_x87FSW, x87fsw);
    Present(Termlog, AR_Intel_MXCSR, csr₁);
    if (modulo(17, 5, r₁, rˡᵖʳ)) { error(); }
    else { printf("17 mod 5 = (%d, %d)\n", r₁, rˡᵖʳ); }
    printf("17 ᵖᵃˢmod 5 = %d\n", ᵖᵃˢmod(17, 5, ^{}));
    if (modulo(-17, 5, r₁, rˡᵖʳ)) { error(); }
    else { printf("-17 mod 5 = (%d, %d)\n", r₁, rˡᵖʳ); }
    printf("-17 ᵖᵃˢmod 5 = %d\n", ᵖᵃˢmod(-17, 5, ^{}));
    if (modulo(17, -5, r₁, rˡᵖʳ)) { error(); }
    else { printf("17 mod -5 = (%d, %d)\n", r₁, rˡᵖʳ); }
    printf("17 ᵖᵃˢmod -5 = %d\n", ᵖᵃˢmod(17, -5, ^{}));
    printf("...and now when the divisor is `0`\n");
    if (modulo(-5, 0, r₁, rˡᵖʳ)) { error(); }
    else { printf("-5 mod 0 = (%d, %d)\n", r₁, rˡᵖʳ); }
    /* printf("-5 ᵖᵃˢmod 0 = %d\n", ᵖᵃˢmod(-5, +0, ^{ }));
    printf("-5 ᵖᵃˢmod 0 = %d\n", ᵖᵃˢmod(-5, -0, ^{ }));   
    */ // ⬷ Undefined and crashes/SIGFPE the program.
    🎭𝑋𝟾𝟼(&csr₁, MXCSR_RC, ^(__builtin_uint_t& shifted) { shifted = 0b10; });
    🎭𝑋𝟾𝟼(&x87fcw₁, FCW_RC, ^(__builtin_uint_t& shifted) { shifted = 0b10; });
    _mm_setcsr((uint32_t)csr₁); x87control((uint32_t)x87fcw₁);
    uint32_t csr₂=_mm_getcsr(), x87fcw₂=x87control();
    Present(Termlog, AR_Intel_MXCSR, csr₂);
    Present(Termlog, AR_Intel_x87FCW, x87fcw₂);
    printf("17 ᵈᵉfmod 5 = %d\n", ᵈᵉfmod(17, 5, ^{}));
    printf("-17 ᵈᵉfmod 5 = %d\n", ᵈᵉfmod(-17, 5, ^{}));
    printf("17 ᵈᵉfmod -5 = %d\n", ᵈᵉfmod(17, -5, ^{}));
    uint8_t fxsave_region[512] __attribute__((aligned(16)));
    /* ⁵¹²fxsave(fxsave_region);
    ⁵¹²fxrstore(fxsave_region); */
    return 0;
}

