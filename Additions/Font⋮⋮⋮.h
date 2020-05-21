/*  Rasterizer.h | Additions. */

#ifndef __RASTERIZER_H
#define __RASTERIZER_H

#include <Twinbeam.h>

struct FontRasterizer {
    
    FontRasterizer(int horizDPI, int vertDPI);
    
    ~FontRasterizer();
    
    typedef struct BoundingBox { signed long xMin, yMin, xMax, yMax; } BBox;
    
    int renderMonocrome(int width, int height, Memoryview otfFont, char32_t 
      (^text)(int index), void (^bitmap)(int width, int rows, uint8_t *buffer, 
      int pitch, int horzKern));
    
    int renderAA256(int width, int height, Memoryview otfFont, char32_t 
      (^text)(int index), void (^bitmap)(int width, int rows, uint8_t *buffer, 
      int pitch, int horzKern));
    
    int renderOutline(int width, int height, Memoryview otfFont, char32_t 
      (^text)(int index), void (^outline)(BoundingBox boundingBox, int 
      horzKern));
    
😐;

#endif /* An example font is defined in Fig~302, [Knuth, A Potpourri of Puzzles]. */
