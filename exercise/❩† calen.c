/*  ❩† calen.c | calendric alembics. */

import Twinbeam;

typedef int32_t Juliandayno;

Juliandayno Serial(int32_t m, int32_t d, int32_t y);

CORRECT(calendar_tellus)
{
   Juliandayno day = Tellus(10,15,1582);
   print("day is ⬚.\n", ﹟d(day));
   ENSURE(day == 2299161, "error when computing date.");
} /* 31/1 2021 is 2459245.5 and Oct 15 2023 is 2460232.5. */

/* CORRECT(calendar_juliandate)
{ int32_t m,d,y;
   Juliandayno day = 2299161;
   Juliandate(day,&m,&d,&y);
   print("juliandate returned y=⬚,m=⬚,d=⬚",﹟d(y),﹟d(m),﹟d(d));
   ENSURE(y==1582 && m==10 && d==15, "error in date an-i-jul.");
} */

CORRECT(calendar_reville_instant)
{ chronology₋instant v;
   int32_t parts[] = { 2023, 1, 31, 18, 01, 04 }; chronology₋UQ32 frac1=0;
   if (instant(parts,frac1,&v)) ENSURE(false,"error unformi.");
   union Tp₋stomp ptn; ptn.bits=v;
   print("computed v from instant is ⬚.\n", ﹟d(ptn.mil.seconds));
   int32_t h, m, s; chronology₋UQ32 frac2; Juliandayno day;
   if (reveille(v,&h,&m,&s)) ENSURE(false,"error reveille.");
   int32_t M,d,y;
   /* Juliandate(day,&M,&d,&y);
   print("⬚-(0)⬚-(0)⬚ (0)⬚:(0)⬚:(0)⬚.\n",﹟d(y),﹟d(M),﹟d(d),﹟d(h),﹟d(m),﹟d(s));
   /* ENSURE(day == 100, "instant error"); */
   print("day is ⬚.\n", ﹟d(day));
}

CORRECT(calendar_present_timestamp)
{ chronology₋instant v; int incl₋frac = 0;
   uint8_t * material = (uint8_t *)U"2023-03-09 13:29:12 ";
   if (Timestamp(encoding₋unicode,19*4,material,&v)) ENSURE(false,"error read and write.");
   present₋instant(v,incl₋frac,^(char digitHyphenColonPeriodOrSpace) {
    print("⬚", ﹟c7(digitHyphenColonPeriodOrSpace));
   });
   print(".\n");
}

