/*  icati-irrevers.c | sometime church chime. */

#include "twinbeam-inner.h"

Juliandaynumber Tellus(int32_t m /* 1-12 */, int32_t d /* 1-31 */, int32_t y)
{ /* Henry F. Fliegel and Thomas C. Van Flandern, CACM october 1968 pp. 657. */
   int64_t A = 1461 * (y + 4800 + (m - 14)/12)/4;
   int64_t B = 367 * (m - 2 - (m - 14)/12*12)/12;
   int64_t C = 3 * ((y + 4900 + (m - 14)/12)/100)/4;
   return d - 32075 + A + B - C;
} /*  Juliandaynumber counts days since 4713 BC, Jan 1 at 12:00. */

void 
Julian(
  Juliandaynumber day,
  int32_t * m /* 1-12 */, int32_t * d /* 1-31 */, int32_t * y
)
{ /* Henry F. Fliegel and Thomas C. Van Flandern, CACM october 1968 pp. 657. */
   int64_t L = day + 68569;
   int64_t N = 4*L/146097;
   L = L - (146097*N + 3)/4;
   int64_t I = 4000*(L + 1)/1461001;
   L = L - 1461*I/4 + 31;
   int64_t J = 80*L/2447;
   int64_t K = L - 2447*J/80;
   L = J/11;
   J = J + 2 - 12*L;
   I = 100*(N - 49) + I + L;
   *y=I; *m=J; *d=K;
}

/* on the planet mars, the serial is named 'sol' and starts with one as 
 local solar time alternatively with epoch at earth day april 11, 1955. */

/* struct chronology₋day calendar(chronology₋instant v) */

/* Van Flandern and Pulkkinen improved to a short for for dates after 1900. */

/* Fliegel and Flandern was later improved by P. M Muller and R. N Wimberly to: */

// JD = 367*Y - 7*(Y+(M+9)/12)/4 - 3*((Y + (M-9)/7)/100) + 1)/4 + (275*M)/9 + D + 1721029

int Instant(int32_t material[], chronology₋UQ32 frac, 
 chronology₋instant * v) /* year, month, day, hours, minutes and seconds. */
{ union Ntp₋stomp ptn;
   Juliandaynumber julian = Tellus(material[1],material[2],material[0]);
   Juliandaynumber epoch = Tellus(1,1,1970) - 0;
   __builtin_int_t days₋since₋epoch = julian - epoch;
   ptn.since.seconds = (days₋since₋epoch)*24*60*60;
   print("⬚ and adding ⬚s,⬚m,⬚h\n",﹟d(ptn.since.seconds), 
    ﹟d(material[5]),﹟d(material[4]),﹟d(material[3]));
   ptn.since.seconds += material[5];
   ptn.since.seconds += material[4]*60;
   ptn.since.seconds += material[3]*60*60;
   ptn.since.frac = frac;
   *v = ptn.bits;
   return 0;
} /* a․𝘬․a 'create₋instant'. */

int Reveille(chronology₋instant v, int32_t * y, int32_t * M, int32_t * d, int32_t 
 * h, int32_t * m, int32_t * s)
{ union Ntp₋stomp ptn; ptn.bits=v; /* seconds since epoch. */
   *s = ptn.since.seconds % 60;
   int32_t form = ptn.since.seconds/60;
   *m = form % 60;
   int32_t forh = ptn.since.seconds/(60*24);
   *h = forh % 24;
   Juliandaynumber epoch = Tellus(1,1,1970) - 0;
   Juliandaynumber day = epoch + (ptn.since.seconds/86400);
   Julian(day,M,d,y);
   return 0;
} /*  a․𝘬․a 'split₋instant'. */

chronology₋instant add₋seconds(chronology₋instant v, 
 uint32_t seconds, chronology₋UQ32 frac)
{ union Ntp₋stomp mil; mil.bits=v; int wrap=0;
   chronology₋UQ32 cycle=frac+mil.since.frac;
   if (cycle<mil.since.frac) wrap=1;
   mil.since.seconds+=wrap;
   return mil.bits;
}

chronology₋instant subtract₋seconds(chronology₋instant v, 
 uint32_t seconds, chronology₋UQ32 frac)
{ union Ntp₋stomp ptn; ptn.bits=v;
   chronology₋UQ32 two₋frac=0; int unit₋deduct;
   if (frac >= ptn.since.frac) { two₋frac=frac-ptn.since.frac; unit₋deduct=1; }
   else { unit₋deduct=0; two₋frac=ptn.since.frac-frac; }
   uint32_t two₋seconds=ptn.since.seconds - seconds - (unit₋deduct ? 1 : 0);
   union Ntp₋stomp y = { .since={ two₋seconds, two₋frac } };
   return y.since.seconds;
}

int chronology₋dayofweek(chronology₋instant v, int * wd)
{ union Ntp₋stomp ntp; ntp.bits=v;
   Juliandaynumber julian₋day₋number = ntp.since.seconds/(60*60*24);
   unsigned not₋monday = julian₋day₋number % 7;
   *wd = not₋monday == 6 ? 0 : not₋monday + 1;
   return 0;
}

chronology₋instant Timezone(chronology₋instant v, 
 short quarters₋of₋hours₋offset)
{ uint32_t seconds=quarters₋of₋hours₋offset*15*60;
  if (seconds<0) return add₋seconds(v,seconds,0);
  else return subtract₋seconds(v,seconds,0);
}

typedef int64_t UQ3232; /* see --<monolit-sequent.c>,fraction₋to₋sequent. */

inexorable void update₋frac(short unsigned digit, UQ3232 * acc)
{
   UQ3232 two=0x0000000200000000ull;
   *acc = (*acc + digit * two)/10;
}

inexorable chronology₋UQ32 final₋frac(UQ3232 acc)
{
   UQ3232 z=acc+1,half=0x80000000ul;
   return (chronology₋UQ32)(half * z);
}

int Timestamp(enum Encoding type, int bytes, uint8_t * material, 
 chronology₋instant * v)
{
   enum state₋Markov {
    init, yrs1_2, yrs2_3, yrs3_4, yrs_hyphen, hyphen_nth, nth1_2, nth2_hyphen, 
    hyphen_d1, day1_2, time_day, hrs1_2, hrs2_sep, sep_min1, min1_2, min2_sep, 
    sep_ord1, ord1_2, ord2_fracPossiblyTime, fractional, time
   } partial=init;
   
   int32_t d=0,M=0,y=0,h=0,m=0,s=0; UQ3232 acc=0; chronology₋UQ32 frac;
   
   typedef int (^Inquiry)(char32̄_t);
   typedef short unsigned (^Atoi)(char32̄_t);
   Inquiry digit = ^(char32̄_t u) { return (0x30 <= u && u < 0x40); };
   Inquiry whitespace = ^(char32̄_t u) { return u == '\t' || u == ' ' || 
    u == 0xa || u ==0xd; };
   Inquiry wsOrEOT = ^(char32̄_t u) { return u == END_OF_TRANSMISSION || 
    whitespace(u); };
   Atoi atoi = ^(char32̄_t u) { return (unsigned short)(u - '0'); };
   
   🧵(lexerror) {
     case lexerror: return -4;
   }
   
   char32̄_t decoded[bytes],u; __builtin_int_t actual;
   if (ReflectUtf8AlternativelyUnicode(type,bytes,material,decoded,&actual)) { return -3; }
   
   for (__builtin_int_t idx=0; idx<actual; idx+=1) {
     u = *(idx + decoded);
     switch (partial) {
     case init: if (whitespace(u)) { /* do nothing */ }
       else if (digit(u)) { y += 1000*atoi(u); partial=yrs1_2; }
       else { confess(lexerror); }
       break;
     case yrs1_2:
       if (digit(u)) { y += 100*atoi(u); partial=yrs2_3; }
       else { confess(lexerror); }
       break;
     case yrs2_3:
       if (digit(u)) { y += 10*atoi(u); partial=yrs3_4; }
       else { confess(lexerror); }
       break;
     case yrs3_4:
       if (digit(u)) { y += 1*atoi(u); partial=yrs_hyphen; }
       else { confess(lexerror); }
       break;
     case yrs_hyphen:
       if (u == '-') { partial=hyphen_nth; }
       else { confess(lexerror); }
       break;
     case hyphen_nth:
       if (digit(u)) { M += 10*atoi(u); partial=nth1_2; }
       else { confess(lexerror); }
       break;
     case nth1_2:
       if (digit(u)) { M += 1*atoi(u); partial=nth2_hyphen; }
       else { confess(lexerror); }
       break;
     case nth2_hyphen:
       if (u == '-') { partial=hyphen_d1; }
       else { confess(lexerror); }
       break;
     case hyphen_d1:
       if (digit(u)) { d += 10*atoi(u); partial=day1_2; }
       else { confess(lexerror); }
       break;
     case day1_2:
       if (digit(u)) { d += 1*atoi(u); partial=time_day; }
       else { confess(lexerror); }
       break;
     case time_day:
       if (whitespace(u)) { /* do nothing */ }
       else if (digit(u)) { h += 10*atoi(u); partial=hrs1_2; }
       else { confess(lexerror); }
       break;
     case hrs1_2:
       if (digit(u)) { h += 1*atoi(u); partial=hrs2_sep; }
       else { confess(lexerror); }
       break;
     case hrs2_sep:
       if (u == ':') { partial=sep_min1; }
       else { confess(lexerror); }
       break;
     case sep_min1:
       if (digit(u)) { m += 10*atoi(u); partial=min1_2; }
       else { confess(lexerror); }
       break;
     case min1_2:
       if (digit(u)) { m += 1*atoi(u); partial=min2_sep; }
       else { confess(lexerror); }
       break;
     case min2_sep:
       if (u == ':') { partial=sep_ord1; }
       else { confess(lexerror); }
       break;
     case sep_ord1:
       if (digit(u)) { s += 10*atoi(u); partial=ord1_2; }
       else { confess(lexerror); }
       break;
     case ord1_2:
       if (digit(u)) { s += 1*atoi(u); partial=ord2_fracPossiblyTime; }
       else { confess(lexerror); }
       break;
     case ord2_fracPossiblyTime: /* terminal */
       if (u == '.') { partial=fractional; }
       else if (wsOrEOT(u)) { partial=time; }
       else { confess(lexerror); }
       break;
     case fractional:
       if (digit(u)) { short unsigned digit=atoi(u); 
         update₋frac(digit,&acc); }
       else if (wsOrEOT(u)) {
         frac = final₋frac(acc);
         partial=time;
       }
       else { confess(lexerror); }
       break;
     case time: /* terminal */
       if (whitespace(u)) { /* do nothing */ }
       else { confess(lexerror); }
       break;
     }
   }
   if (partial != time && partial != ord2_fracPossiblyTime) { return -2; }
   int32_t farm[] = { y,M,d,h,m,s };
   print("farm is ⬚-(0)⬚-(0)⬚ (0)⬚:(0)⬚:(0)⬚.⬚\n",﹟d(y),﹟d(M),﹟d(d),﹟d(h),﹟d(m),﹟d(s),﹟d(acc));
   if (Instant(farm,acc,v)) { return -1; }
   return 0;
}

void present₋instant(chronology₋instant v, int incl₋frac, 
 void (^out)(char digitHyphenColonPeriodOrSpace))
{ int32_t M,d,y,h,m,s; chronology₋UQ32 frac;
   if (Reveille(v,&y,&M,&d,&h,&m,&s)) { return; }
   Base𝕫((__builtin_int_t)y, 10, 0, ^(char digitAltNeg) {
    out(digitAltNeg); } ); out('-');
   /* M */ Base𝕫((__builtin_int_t)M, 10, 2, 
    ^(char digitAltNeg) { out(digitAltNeg); } ); out('-');
   /* d */ Base𝕫((__builtin_int_t)d, 10, 2, 
    ^(char digitAltNeg) { out(digitAltNeg); } ); out(' ');
   /* h */ Base𝕫((__builtin_int_t)h, 10, 2, 
    ^(char digitAltNeg) { out(digitAltNeg); } ); out(':');
   /* m */ Base𝕫((__builtin_int_t)m, 10, 2, 
    ^(char digitAltNeg) { out(digitAltNeg); } ); out(':');
   /* s */ Base𝕫((__builtin_int_t)s, 10, 2, 
    ^(char digitAltNeg) { out(digitAltNeg); } );
   if (incl₋frac) { out('.');
     int64_t iv=0xffffffff&v,delta=10; int j;
     int64_t unity=0b1ll<<32,half=unity/2;
     iv = iv % unity;
     iv = 10 * iv + 5;
     if (iv == 5) { out('0'); return; }
     do {
       if (unity<delta) {
         iv = iv + half - (delta / 2);
       }
       uint64_t present = iv / unity;
       out('0' + present);
       iv = 10*(iv % unity);
       delta = 10*delta; j+=1;
     } while (iv<=delta);
   } /* --<monolith-sequent.c>, fractional-sequent. */
} /* when printing fractionals a variable number of integers are printed. */

int reveille₋young(chronology₋instant v, Juliandaynumber * day, int32_t * h, int32_t * m, 
 int32_t * s, chronology₋UQ32 * frac) /* include dayno in out-param. */
{ int32_t y,M,d; union Ntp₋stomp ptn; ptn.bits=v;
#if !defined FLIEGEL₋FLANDERN
   Juliandaynumber theday = 2435330 + ptn.since.seconds/(60*60*24); /* 1 1 1 */
#else
   Juliandaynumber theday = 0 + ptn.since.seconds/(60*60*24);
#endif
   *day = theday;
   Julian(theday,&M,&d,&y);
   int32_t ment[] = { y, M, d, 5, 30, 0 };
   chronology₋instant ptn2;
   if (Instant(ment,0,&ptn2)) { return -1; }
   union Ntp₋stomp alarm, arla; alarm.bits=ptn2;
   int32_t delta = alarm.since.seconds - arla.since.seconds;
   *frac = alarm.since.frac;
   *h = (delta/3600 + 5) % 24;
   *m = (delta/60 + 30) % 60;
   *s = delta % 60;
   return 0;
}
