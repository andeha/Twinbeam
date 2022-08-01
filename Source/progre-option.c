/*  progre-option.c | ieee754 formatting functions. */

import Twinbeam;

inexorable void ieee754﹟2₋to₋base10(
  double ℝ, char * fiftysix₋ten₋base, int decimal
)
{
   
}

#include <stdio.h>

void
ieee754₋Scandinavian₋Monetary₋Rendition(
  double ℝ, char * fiftysix₋ten₋base, int * letters
)
{
   int y = snprintf(fiftysix₋ten₋base, 56, "%#.3lf", ℝ);
   *letters = y;
}

void
ieee754₋Saturn₋Rendition(
  double ℝ, char * fiftysix₋ten₋base, int * letters
)
{
   int y = snprintf(fiftysix₋ten₋base, 56, "%#12lf", ℝ); /* twelve letters zeroes from right crossed. */
   *letters = y;
}

void
ieee754₋Scientific₋Rendition(
  double ℝ, char * fiftysix₋ten₋base, int * letters
)
{
   int y = snprintf(fiftysix₋ten₋base, 56, "%lg", ℝ);
   *letters = y;
}

void
ieee754₋Monetary₋Rendition(
  double ℝ, char * fiftysix₋ten₋base, int * letters
)
{
   int y = snprintf(fiftysix₋ten₋base, 56, "%#.2lf", ℝ);
   *letters = y;
}

