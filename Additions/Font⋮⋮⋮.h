/*  Rasterizer.h | Pixelation given an .otf-file font definition. */

#ifndef __RASTERIZER_H
#define __RASTERIZER_H

#include <Twinbeam.h>

struct Pixelation {
    
    Pixelation(int horiz₋dpi, int vert₋dpi);
    
    ~Pixelation();
    
    typedef struct Boundingbox { signed long xMin, yMin, xMax, yMax; } BBox;
    
    int renderMonocrome(int width, int height, Memoryview otfFont, char32_t 
      (^text)(int index), void (^bitmap)(int width, int rows, uint8_t *buffer, 
      int pitch, int horzKern));
    
    int renderAA256(int width, int height, Memoryview otfFont, char32_t 
      (^text)(int index), void (^bitmap)(int width, int rows, uint8_t *buffer, 
      int pitch, int horzKern));
    
    int renderOutline(int width, int height, Memoryview otfFont, char32_t 
      (^text)(int index), void (^outline)(Boundingbox box, int horzKern));
    
😐;

#endif /* See Fig~302 in [Knuth, A Potpourri of Puzzles] for an example font. */
