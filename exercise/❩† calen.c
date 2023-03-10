/*  ❩† calen.c | calendric alembics. */

import Twinbeam;

typedef int32_t Juliandayno;

void JulianAndDate(Juliandayno day, int32_t * m, int32_t * d, int32_t * y);

Juliandayno Serial(int32_t m, int32_t d, int32_t y);

CORRECT(calendar_aparts1)
{
   Juliandayno day = Tellus(10,15,1582);
   print("day is ⬚ .\n", ﹟d(day));
}

CORRECT(calendar_aparts2)
{ int32_t m,d,y;
   Juliandayno day = 2299161;
  JulianAndDate(day,&m,&d,&y);
  print("y=⬚,m=⬚,d=⬚",﹟d(y),﹟d(m),﹟d(d));
}

CORRECT(calendar_pieces)
{ chronology₋instant v;
   int32_t parts[] = { 2023, 1, 31, 18, 01, 04 }; chronology₋UQ32 frac1=0;
   if (instant(parts,frac1,&v)) ENSURE(false,"form-instant");
   struct chronology₋day day = calendric(v);
   int32_t h, m, s; chronology₋UQ32 frac2;
   if (reveille(v,&h,&m,&s,&frac2)) ENSURE(false,"reveille");
   print("");
 //  ENSURE(day.y == 2023, "year");
}

CORRECT(calendar_atext)
{ chronology₋instant v;
   uint8_t * material = (uint8_t *)U"2023-03-09 13:29:12 ";
   if (Timestamp(encoding₋unicode,19*4,material,&v)) ENSURE(false,"timestamp");
}

