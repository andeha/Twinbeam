/*  Terminal.cpp | animal 32-inquisitorial and 'different'. */

import Twinbeam;

rt₋namespace Terminal { extern Utf8Terminal myTrace₁, myTrace₂, myOutput; extern __builtin_int_t distribution₋error; }

/* structᵢ ⁱOutputstream { virtual int write(char8_t * u8s, __builtin_int_t bytes) = 0; };
structᵢ Inputstream { virtual __builtin_int_t read(char32_t unicode) = 0; };
  structᵢ IO : public Outputstream, public Inputstream {
  __builtin_int_t write(char8_t * p, __builtin_int_t bytes);
  __builtin_int_t read(char32_t unicode);
}; */

#pragma mark - protective inner-capsule

structᵢ Utf8Terminal::Internals { Utf8Terminal * outer; };

#pragma mark - artificially encapsuled

Utf8Terminal::Utf8Terminal() : impl_ { new Internals() }
{
   impl_->outer = this;
   format = ^(double x, Utf8Terminal &stream) { NumberformatCatalogue::Default(x,stream); };
}

Utf8Terminal::~Utf8Terminal() { delete impl_; }

int Utf8Terminal::write(char8_t * serie, __builtin_int_t bytes) const
{
   extern void (^Putₒ)(char8_t * u8s, __builtin_int_t bytes);
   extern void (^Trace₁)(char8_t * u8s, __builtin_int_t bytes);
   extern void (^Trace₂)(char8_t * u8s, __builtin_int_t bytes);
   if (this == &Terminal::µOutput) { Putₒ(serie,bytes); }
   else if (this == &Terminal::µTrace₁) { Trace₁(serie,bytes); }
   else { Trace₂(serie,bytes); }
   return 0;
}

#pragma mark - interaction and presentation

𝟄₋int₁ /* Inputctrl */ 
Utf8Terminal::corout₋Symbols(
  int periods𝘖rZero, int 𝟷𝟶ᵗʰ₋seconds, 
  void (^ping𝘖r𝖭𝖴𝖫𝖫)(bool &stop), 
  void (^child₋keyput𝘖rRecieved)(char32_t unicode, bool &stop)
 /* void (^ctrl₋keys)(uint32_t Ctrlkeys₋former, uint32_t Ctrlkeys₋current) */
 /* ⬷ before key is unpressed. */
 /* void (^track₍s₎₋pad)(doubleʳ locX, doubleʳ locY, double⁺ʳ pressure, bool is₋up) */
 /* void (^touches₋barᵧ)() */
 /* void (^morphoetic₋surface)() */ /* after-to(u)ch */
) const
{
   extern FOCAL 𝟄₋int₁ corout₋Order₋keyput(
    int periods𝘖rZero, int 𝟷𝟶ᵗʰ₋seconds, 
    void (^ping𝘖rNULL)(bool &stop), 
    void (^return₋key)(bool &stop), 
    void (^after₋key)(char32_t unicode, bool &stop));
   
   auto child₋return₋key = ^(bool &stop) { print("return"); };
   𝟄₋int₁ yₒ = co₋await corout₋Order₋keyput(periods𝘖rZero, 
     𝟷𝟶ᵗʰ₋seconds, ping𝘖r𝖭𝖴𝖫𝖫, child₋return₋key, child₋keyput𝘖rRecieved);
   bye yₒ.coroutine.promise().transport.ℤ;
} /* ⬷ hard-realtime, one-two cores and disjunct 'pointers to a coroutine'. */

#if defined __x86_64__
#include <stdio.h>
#endif

int oldschool₋WaitTerminal(char32_t * uc)
{
#ifdef __mips__
  return -1;
#elif defined __x86_64__
  wchar_t non₋uc;
  scanf("%lc", &non₋uc); /* ⬷ scanf("%["). */
  *uc=non₋uc;
  return 0;
#endif
}


