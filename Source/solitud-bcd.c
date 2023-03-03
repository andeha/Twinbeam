/*  solitud-bcd.c | Jon Bentley decimal arithetics. */

import Twinbeam;

#define PLUS +1
#define MINUS -1
#define DIGITS 628

inexorable void bcd₋bigint₋zero(𝓵₋bigint * z)
{
   int₋and₋bigint(0,z);
}

inexorable void bcd₋zero₋justify(𝓵₋bigint * z)
{
   while (z->lastdigit>0 && z->digits[z->lastdigit]==0) z->lastdigit--;
   if (z->lastdigit==0 && z->digits[0]==0) z->signbit=PLUS;
}

inexorable __builtin_int_t sevenbit₋strlen(char * s)
{
   char *p=s; while (*p) { p+=1; }
   return (__builtin_int_t)p - (__builtin_int_t)s;
}

void int₋and₋bigint(int64_t /* base-2 */ s, 𝓵₋bigint * n)
{   int i;            /* counter */
   int t;            /* int to work with */

   if (s >= 0) n->signbit = PLUS;
   else n->signbit = MINUS;

   for (i=0; i<DIGITS; i++) n->digits[i] = (char) 0;

   n->lastdigit = -1;

   t = abs(s);

   while (t > 0) {
      n->lastdigit ++;
      n->digits[ n->lastdigit ] = (t % 10);
      t = t / 10;
   }

   if (s == 0) n->lastdigit = 0;
} /* digits stored 'little-endian' in the 'digits' array. */

int digits₋and₋bigint(char * digits, 𝓵₋bigint * z)
{ char c; int length=sevenbit₋strlen(digits),i=0;
   bcd₋bigint₋zero(z);
again:
   c = *(digits+length-1-i);
   if (c == ΨΛΩ) { z->lastdigit=i; return 0; }
   if (!(0x30 <= c && c < 0x3a)) { return -1; }
   z->digits[i]= c - '0';
   i += 1;
   goto again;
}

void bcd₋bigint₋add(𝓵₋bigint * x₁, 𝓵₋bigint * x₂, 𝓵₋bigint * z)
{ int i,carry,sum;
   bcd₋bigint₋zero(z);
   if (x₁->signbit == x₂->signbit) { z->signbit=x₁->signbit; }
   else {
     if (x₁->signbit == MINUS) {
       x₁->signbit = PLUS;
       bcd₋bigint₋subtract(x₂,x₁,z);
       x₁->signbit = MINUS;
     } else {
       x₂->signbit = PLUS;
       bcd₋bigint₋subtract(x₁,x₂,z);
       x₂->signbit = MINUS;
     }
     return;
   }
   
   z->lastdigit = max(x₁->lastdigit,x₂->lastdigit) + 1;
   carry=0;
   
   for (i=0; i<=z->lastdigit; i+=1)
   {
     sum = x₁->digits[i]+x₂->digits[i];
     z->digits[i] = (sum + carry) % 10;
     carry = (sum + carry) / 10;
   }
   
   bcd₋zero₋justify(z);
}

void bcd₋bigint₋subtract(𝓵₋bigint * x₁, 𝓵₋bigint * x₂, 𝓵₋bigint * z)
{ __builtin_int_t i,v,borrow;
   bcd₋bigint₋zero(z);
   if (x₁->signbit == MINUS || x₂->signbit == MINUS) {
     x₂->signbit = -1 * x₂->signbit;
     bcd₋bigint₋add(x₁,x₂,z);
     x₂->signbit = -1 * x₂->signbit;
     return;
   }
   
   if (bcd₋bigint₋compare(x₁,x₂) == PLUS) {
      bcd₋bigint₋subtract(x₂,x₁,z);
      z->signbit = MINUS;
      return;
   }
   
   z->lastdigit = max(x₁->lastdigit,x₂->lastdigit);
   borrow = 0;
   
   for (i=0; i<=z->lastdigit; i+=1)
   {
     v = x₁->digits[i] - borrow - x₂->digits[i];
     if (x₁->digits[i] > 0) borrow = 0;
     if (v<0) { v += 10; borrow=1; }
     z->digits[i] = v % 10;
   }
   
   bcd₋zero₋justify(z);
}

void bcd₋bigint₋multiply(𝓵₋bigint * x₁, 𝓵₋bigint * x₂, 𝓵₋bigint * z)
{ int i,j; bigint row=*x₁,local;
   bcd₋bigint₋zero(z);
   for (i=0; i<=x₂->lastdigit; i+=1)
   {
      for (j=1; j<=x₂->digits[i]; j+=1)
      {
         bcd₋bigint₋add(z,&row,&local);
         *z = local;
      }
      bcd₋bigint₋shift(&row,1);
   }
   z->signbit = x₁->signbit * x₂->signbit;
   bcd₋zero₋justify(z);
}

void bcd₋bigint₋divide(𝓵₋bigint * x₁, 𝓵₋bigint * x₂, 𝓵₋bigint * z)
{ int i,j,one₋sgn,two₋sgn; bigint row,local;
   bcd₋bigint₋zero(z);
   z->signbit = x₁->signbit * x₂->signbit;
   one₋sgn = x₁->signbit;
   two₋sgn = x₂->signbit;
   x₁->signbit = PLUS;
   x₂->signbit = PLUS;
   bcd₋bigint₋zero(&row);
   bcd₋bigint₋zero(&local);
   z->lastdigit = x₁->lastdigit;
   for (i=x₁->lastdigit; i>=0; i=i-1)
   {
      bcd₋bigint₋shift(&row,1);
      row.digits[0] = x₁->digits[i];
      z->digits[i] = 0;
      while (bcd₋bigint₋compare(&row,x₂) != PLUS)
      {
         z->digits[i] += 1;
         bcd₋bigint₋subtract(&row,x₂,&local);
         row = local;
      }
   }
   bcd₋zero₋justify(z);
   x₁->signbit = one₋sgn;
   x₂->signbit = two₋sgn;
}

void bcd₋bigint₋shift(𝓵₋bigint * z, __builtin_int_t I)
{ __builtin_int_t i;
   if (z->lastdigit == 0 && z->digits[0] == 0) return;
   for (i=z->lastdigit; i>=0; i=i-1) z->digits[i+I]=z->digits[i];
   for (i=0; i<I; i+=1) z->digits[i]=0;
   z->lastdigit = I + z->lastdigit;
}

int bcd₋bigint₋compare(𝓵₋bigint * x₁, 𝓵₋bigint * x₂)
{ __builtin_int_t i;
   // if (x₁->signbit ^ x₂->signbit) { return x₂->signbit; }
   if (x₁->signbit == MINUS && x₂->signbit == PLUS) return PLUS;
   if (x₁->signbit == PLUS && x₂->signbit == MINUS) return MINUS;
   if (x₂->lastdigit > x₁->lastdigit) return PLUS * x₁->signbit;
   if (x₁->lastdigit > x₂->lastdigit) return MINUS * x₁->signbit;
   for (i=x₁->lastdigit; i>=0; i=i-1) {
      if (x₁->digits[i]>x₂->digits[i]) return MINUS * x₁->signbit;
      if (x₂->digits[i]>x₁->digits[i]) return PLUS * x₁->signbit;
   }
   return 0;
}

