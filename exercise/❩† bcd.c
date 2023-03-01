/*  ❩† bcd.c | base ten math routines. */

import Twinbeam;

CORRECT(BCD_add)
{
   int64_t ℤ₁=17; 𝓵₋bigint x₁,x₂,𝓫;
   int₋and₋bigint(ℤ₁,&x₁);
   if (digits₋and₋bigint("123456",&x₂))
    ENSURE(false,"error when converting text to bcd");
   bcd₋bigint₋add(&x₁,&x₂,&𝓫);
   ENSURE(𝓫.digits[0] == 3,"error on first digit");
   ENSURE(𝓫.digits[1] == 7,"error on first digit");
   ENSURE(𝓫.digits[2] == 4,"error on first digit");
   ENSURE(𝓫.signbit == 1 && 𝓫.lastdigit == 5,"error in format");
}
