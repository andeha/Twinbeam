/*  impres-ion.h | composition, a palette, the file₋ber and god plenty. */

fostrat₋defi
{
  
  int scanlines, columns, pixelsize; int is₋unpurged;
  
  union {
/* 1 */ struct RGB { uchar *R, *G, *B, *A; } dispersiveP3;
/* 2 */ struct Radio { uchar *L, *U, *V, *A, *D, *ºC; } dispersiveLUVADIr; /*  opt. 'depth' and 'IR'. */
/* 3 */ struct Print { uchar *C, *M, *Y, *K, *A; } dispersiveCMYK;
/* 4 */ struct Halftone { uchar *runs; } black﹠white; /*  a․𝘬․a 'pdf', 'png', 'kryptonit' and 'vanilla'. */
/* 5 */ struct Planetarian { structure ccw, cw; } galaxy; /*  a․𝘬․a 'two-escape'. */
/* 6 */ struct PngRGBA8Pixel { uint8_t R, G, B, A; } *pngRgba8; /*  c𝘧․ 'scatter'. */
/* 7 */ struct Nautilus { structure tiles; } irreversibly; /*  a․𝘬․a 'one-escape'. */
/* 8 */ struct Passivetranspa { byte * scanlines₋gray; } crominant₋luminant; 
  } material; int kind; /* ∈[1,7] */
}
  
} ortogonal₋image;

fostrat₋defi 
{
  ortogonal₋image uncropped;
  double left₋clip, right₋clip, top₋clip, bottom₋clip;
} cropped₋image;

#define Imagekind₋P3 1 /* and LUVADIr, CMYK, BW, GALAX, PNGrgba8, NAUTILUS. */
#define Imagekind₋GRIVE 2

FOCAL
inline
int
Release(
  Image & image,
  bool secure
)
{
   if (!image.unpurged) { return -1; }
   switch (image.kind) {
    case Image::Kind::P3: break;
    case Image::Kind::LUVADIr: break;
    case Image::Kind::PNGrgba8: break;
   }
   image.unpurged=false;
   return 0;
} /*  releases image encasing also material. */

inline
int
Snapshot(
  const Image& original, Image& pristine
) {
   if (&original == &pristine) { return -1; }
   /* __builtin_int_t count = original.impl_->ᵖᵍcount⁻ᵚ();
   for (__builtin_int_t i=0; i<count; i++) {
     pristine.impl_->at(i) = original.impl_->at(i);
   }
   pristine.impl_->set﹟Pages(count); */
   return -1;
}

inline
__builtin_int_t
bytes₋required(
  Image::Kind type, int scanlines, int cols, __builtin_int_t * bytes
)
{
   typedef __builtin_int_t (^Requirement)(short chnls);
   Requirement requirement = ^(short chnls) { return scanlines*cols*chnls; };
   switch (type) {
   case Image::Kind::P3: *bytes=requirement(4); return 0;
   case Image::Kind::LUVADIr: *bytes=requirement(5); return 0;
   case Image::Kind::PNGrgba8: *bytes=requirement(5); return 0;
   }
   return 0;
}

FOCAL inline int CreateNative(unsigned expeditionary, int scanlines, int cols, ortogonal₋image **image)
{  __builtin_int_t bytes,modula,﹟;
   if (bytes₋required(Image::PNGrgba8,scanlines,cols,&bytes)) { return -1; }
   auto reqs = ^(__builtin_int_t bytes, __builtin_int_t * modula) {
     __builtin_int_t ﹟ = 𝟺𝟶𝟿𝟼₋aligned₋frame(bytes,modula);
     return ﹟ + (modula == 0 ? 0 : 1); };
   ﹟ = reqs(bytes,&modula); void * 𝟺kbframes[﹟];
   if (CoalescingAcquire(expeditionary,𝟺kbframes,﹟)) { return -2; }
   image->unpurged=true;
   return 0;
}

#pragma recto composition

fostrat₋defi Plate
{

  Croppedimage image;
  
  int init(double left₋inset, double right₋inset, double top₋inset, double bottom₋inset);
  
};

