/*  Rasterizer.h | Pixelation given an .otf-file font definition. */

#ifndef __RASTERIZER_H
#define __RASTERIZER_H

#include <Twinbeam.h>

struct Pixelation {
    
    Pixelation(int horiz₋dpi, int vert₋dpi);
    
    ~Pixelation();
    
    struct Bounds { signed long xMin, yMin, xMax, yMax; };
    
    int renderMonocrome(int width, int height, uint8_t * otf₋font, int bytes₋otf₋font, 
      Unicodes text, void (^bitmap)(int width, int rows, uint8_t * buffer, 
      int pitch, int horz₋kern));
    
    int renderAA256(int width, int height, uint8_t * otf₋font, int bytes₋otf₋font, 
      Unicodes text, void (^bitmap)(int width, int rows, uint8_t * buffer, 
      int pitch, int horz₋kern));
    
    int renderOutline(int width, int height, uint8_t * otf₋font, int bytes₋otf₋font, 
      Unicodes text, void (^outline)(Bounds box, int horz₋kern));
    
😐;

#endif /* See Fig~302 in [Knuth, A Potpourri of Puzzles] for an example font. */
