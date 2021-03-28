/*  Bezier.cpp | for additions. */

#include <Twinbeam.h>
#include <Additions/Additions.h>
/* #include <Additions/Artclasses.h> */

struct Bezierᵦ { simd_tᵦ z₁, z₂, z₃, z₄; };

void
Render(double⁺ʳ t, Bezierᵦ c, 
  void (^stream)(simd_tᵦ &xy, simd_tᵦ * 𝗽₋₁𝘖rNULL)
)
{ /* Also: Fifo<> + 🥽 Bilinear.cpp instead. */
    static simd_tᵦ prev=simd_initᵦ(0), *p=&prev;
    double t²=t*t,drive=(1-t),tt1mt=3*drive;
    simd_tᵦ c₁=simd_initᵦ(drive*drive*drive), c₂=simd_initᵦ(tt1mt*t²), 
      c₃=simd_initᵦ(t*t²), z11 = __builtin_simd_mulᵦ(c₁,c.z₁), 
       z12 = __builtin_simd_mulᵦ(c₂,c.z₂), 
     z1112 = __builtin_simd_addᵦ(z11,z12), 
       z43 = __builtin_simd_mulᵦ(c₂,c.z₃), 
       z33 = __builtin_simd_mulᵦ(c₃,c.z₄), 
     z3343 = __builtin_simd_addᵦ(z33,z43), 
         z = __builtin_simd_addᵦ(z1112,z3343);
    stream(z,p); prev=z;
} /* ⬷ a․𝘬․a 'Bezier'. */

extern void (*SetPixel)(int x, int y, long err);

void Antialias(int x0, int y0, int x1, int y1)
{
    int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1, x2;
    long dx=abs64i₂(x1-x0), dy=abs64i₂(y1-y0), err=dx*dx+dy*dy;
    long e2 = err == 0 ? 1 : 0xffff7fl/sqrt(err);      /* multiplication factor */
    
    dx *= e2; dy *= e2; err = dx-dy;                        /* error value e_xy */
    for ( ; ; ){                                                  /* pixel loop */
        SetPixel(x0,y0,abs64i₂(err-dx+dy)>>16);
        e2 = err; x2 = x0;
        if (2*e2 >= -dx) {                                            /* x step */
            if (x0 == x1) break;
            if (e2+dy < 0xff0000l) SetPixel(x0,y0+sy,(e2+dy)>>16);
            err -= dy; x0 += sx;
        }
        if (2*e2 <= dy) {                                             /* y step */
            if (y0 == y1) break;
            if (dx-e2 < 0xff0000l) SetPixel(x2+sx,y0,(dx-e2)>>16);
            err += dx; y0 += sy;
        }
    }
}
