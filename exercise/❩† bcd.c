/*  ❩† bcd.c | base ten math routines. */

import Twinbeam;
#include <stdio.h>

void print_bignum(𝓵₋bigint * n)
{
   int i;

   if (n->signbit == -1) printf("- ");
   for (i=n->lastdigit; i>=0; i--)
      printf("%c",'0'+ n->digits[i]);

   printf("\n");
}

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
   ENSURE(𝓫.digits[3] == 3,"error on first digit");
   ENSURE(𝓫.digits[4] == 2,"error on first digit");
   ENSURE(𝓫.digits[5] == 1,"error on first digit");
   ENSURE(𝓫.signbit == 1 && 𝓫.lastdigit == 5,"error in format");
}

CORRECT(BCD_subtract)
{
   int64_t ℤ₁=17; 𝓵₋bigint x₁,x₂,𝓫;
   int₋and₋bigint(ℤ₁,&x₁);
   if (digits₋and₋bigint("123456",&x₂))
    ENSURE(false,"error when converting text to bcd");
   bcd₋bigint₋subtract(&x₁,&x₂,&𝓫);
   ENSURE(𝓫.digits[0] == 9,"error on first digit");
   ENSURE(𝓫.digits[1] == 3,"error on first digit");
   ENSURE(𝓫.digits[2] == 4,"error on first digit");
   ENSURE(𝓫.digits[3] == 3,"error on first digit");
   ENSURE(𝓫.digits[4] == 2,"error on first digit");
   ENSURE(𝓫.digits[5] == 1,"error on first digit");
   ENSURE(𝓫.signbit == -1 && 𝓫.lastdigit == 5,"error in format");
}

CORRECT(BCD_multiply)
{
   int64_t ℤ₁=17; 𝓵₋bigint x₁,x₂,𝓫;
   int₋and₋bigint(ℤ₁,&x₁);
   if (digits₋and₋bigint("123456",&x₂))
    ENSURE(false,"error when converting text to bcd");
   bcd₋bigint₋multiply(&x₁,&x₂,&𝓫);
   print_bignum(&𝓫); print(" ");
   ENSURE(𝓫.digits[0] == 2,"error on first digit");
   ENSURE(𝓫.digits[1] == 5,"error on first digit");
   ENSURE(𝓫.digits[2] == 7,"error on first digit");
   ENSURE(𝓫.digits[3] == 8,"error on first digit");
   ENSURE(𝓫.digits[4] == 9,"error on first digit");
   ENSURE(𝓫.digits[5] == 0,"error on first digit");
   ENSURE(𝓫.digits[6] == 2,"error on first digit");
   ENSURE(𝓫.signbit == 1 && 𝓫.lastdigit == 6,"error in format"); // 864151 = 123456*7
}


CORRECT(BCD_divide)
{
   int64_t ℤ₁=17; 𝓵₋bigint x₁,x₂,𝓫;
   int₋and₋bigint(ℤ₁,&x₁);
   if (digits₋and₋bigint("123456",&x₂))
    ENSURE(false,"error when converting text to bcd");
   bcd₋bigint₋divide(&x₂,&x₁,&𝓫);
   print_bignum(&𝓫); print("\n");
   ENSURE(𝓫.digits[0] == 2,"error on first digit");
   ENSURE(𝓫.digits[1] == 6,"error on first digit");
   ENSURE(𝓫.digits[2] == 2,"error on first digit");
   ENSURE(𝓫.digits[3] == 7,"error on first digit");
   ENSURE(𝓫.signbit == 1 && 𝓫.lastdigit == 3,"error in format"); // 203
}

