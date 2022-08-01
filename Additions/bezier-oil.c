/*  oil-bezier.c | for additions. */

import Twinbeam;

fostrat₋defi { simd_tᵦ z₁, z₂, z₃, z₄; } Bezierᵦ;
fostrat₋defi { simd_tᵦ xy₋p₋₁OrZero, xy₋p, chromin₋and₋lumin; } Rendition₋Bezier;

void Render(double⁺ʳ t, Bezierᵦ C, /* fostrat₋param */ Rendition₋Bezier * stream)
{
    double t²=t*t,drive=(1-t),tt1mt=3*drive;
    simd_tᵦ c₁=simd_initᵦ(drive*drive*drive), c₂=simd_initᵦ(tt1mt*t²), 
      c₃=simd_initᵦ(t*t²), z11 = __builtin_simd_mulᵦ(c₁,c.z₁), 
       z12 = __builtin_simd_mulᵦ(c₂,c.z₂), 
     z1112 = __builtin_simd_addᵦ(z11,z12), 
       z43 = __builtin_simd_mulᵦ(c₂,c.z₃), 
       z33 = __builtin_simd_mulᵦ(c₃,c.z₄), 
     z3343 = __builtin_simd_addᵦ(z33,z43), 
         z = __builtin_simd_addᵦ(z1112,z3343);
    stream->xy₋p₋₁OrZero=stream->xy₋p;
    stream->xy₋p = z;
} /*  a․𝘬․a 'Bezier' and 'Bilinear'. */

extern void SetPixel(int x, int y, long err);

void Plotline₋apparat(simd_tᵦ xy₀, simd_tᵦ xy₁)
{ simd_tᵦ sxy,dxy,delta;
   simd_tᵦ delta = __builtin_simd_subᵦ(xy₁,xy₀);
   simd_tᵦ dxy = __builtin_simd_abs(delta);
   simd_tᵦ sxy = __builtin_simd_sg₍n₎(xy₀,xy₁);
   int err = dxy[0]+dxy[1];
   while (1) {
     SetPixel(xy₀,err*err);
   }
   /* err,err2,err*err,klippt-compar,kors-similar. */
}

void PlotLine₋scalar(int x₀, int y₀, int x₁, int y₁)
{
   int dx=abs(x₁-x₀), sx=x₀<x₁ ? 1 : -1;
   int dy=abs(y₁-y₀), sy=y₀<y₁ ? 1 : -1;
   int err=dx+dy,err2;
   while (1) {
     SetPixel(x₀,y₀,err*err);
     err2=2*err;
     if (err2 >= dy) { if (x₀==x₁) break; err+=dy, x₀+=sx; }
     if (err2 <= dx) { if (y₀==y₁) break; err+=dx, y₀+=sy; }
   }
}

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
