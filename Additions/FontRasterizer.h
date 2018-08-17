//
//  FontRasterizer.h
//  Twinbeam Additions
//

#ifndef __FONTRASTERIZER_H
#define __FONTRASTERIZER_H

#include <Twinbeam.h>

struct FontRasterizer {
    
    FontRasterizer(int horizRes, int vertRes);
    
    ~FontRasterizer();
    
    typedef struct BoundingBox { signed long xMin, yMin, xMax, yMax; } BBox;
    
    int renderMonocrome(int width, int height,
        Memoryview otfFont,
        char32_t (^text)(int index),
        void (^bitmap)(int width, int rows, uint8_t *buffer, int pitch, int
          horzKern));
    
    int renderAA256(int width, int height,
        Memoryview otfFont,
        char32_t (^text)(int index),
        void (^bitmap)(int width, int rows, uint8_t *buffer, int pitch, int
          horzKern));
    
    int renderOutline(int width, int height,
        Memoryview otfFont,
        char32_t (^text)(int index),
        void (^outline)(BoundingBox boundingBox, int horzKern));
    
😐;

#endif
