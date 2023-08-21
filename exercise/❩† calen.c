/*  ❩† calen.c | calendric alembics. */

#include "twinbeam.h"

CORRECT(calendar_tellus)
{
   Juliandaynumber day1=Tellus(10,15,1582),day2=Tellus(1,1,1970);
   print("juliandaynumber is ⬚ and ⬚.\n", ﹟d(day1), ﹟d(day2));
   ENSURE(day1==2299161 && day2==2440588, "error in `Tellus`.");
}

CORRECT(calendar_julian)
{ int32_t m1,d1,y1,m2,d2,y2;
   Juliandaynumber day1=2299161,day2=2440588;
   Julian(day1,&m1,&d1,&y1); Julian(day2,&m2,&d2,&y2);
   print("julian gives y1=⬚,m1=⬚,d1=⬚;y2=⬚,m2=⬚,d2=⬚.\n", 
    ﹟d(y1),﹟d(m1),﹟d(d1),﹟d(y2),﹟d(m2),﹟d(d2));
   ENSURE(y1==1582 && m1==10 && d1==15, "error in `Julian`");
   ENSURE(y2==1970 && m2==1 && d2==1, "error in `Julian`.");
}

CORRECT(calendar_reville_instant)
{ chronology₋instant v;
   int32_t parts[] = { 2023, 1, 31, 18, 01, 04 }; chronology₋UQ32 frac1=0;
   if (instant(parts,frac1,&v)) ENSURE(false,"error unformi.");
   union Ntp₋stomp ptn; ptn.bits=v;
   print("computed v from instant is ⬚.\n", ﹟d(ptn.since.seconds));
   int32_t h, m, s; chronology₋UQ32 frac2; Juliandaynumber day;
   if (reveille(v,&h,&m,&s)) ENSURE(false,"error reveille.");
   int32_t M,d,y;
   /* Juliandate(day,&M,&d,&y);
   print("⬚-(0)⬚-(0)⬚ (0)⬚:(0)⬚:(0)⬚.\n",﹟d(y),﹟d(M),﹟d(d),﹟d(h),﹟d(m),﹟d(s));
   /* ENSURE(day == 100, "instant error"); */
   print("day is ⬚.\n", ﹟d(day));
}

CORRECT(calendar_present_timestamp)
{ chronology₋instant v; int incl₋frac=0;
   uint8_t * material = (uint8_t *)U"2023-03-09 13:29:12 ";
   if (Timestamp(encoding₋unicode,19*4,material,&v)) ENSURE(false,"error in `Timestamp`.");
   present₋instant(v,incl₋frac,^(char digitHyphenColonPeriodOrSpace) {
    print("⬚", ﹟c7(digitHyphenColonPeriodOrSpace));
   });
   print(".\n");
}

