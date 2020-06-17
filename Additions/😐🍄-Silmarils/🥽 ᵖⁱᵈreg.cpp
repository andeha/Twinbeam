/*  ᵖⁱᵈreg.cpp - P̲ropotional + I̲ntegrative + D̲amping. (AVAILABLE-IN-RADIO) */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <Additions/mathˢ.hpp>

/*
 
 xcrun clang @ccargs_macᵧ² -o 'Regulator' ../../Source/llvmʳᵗ³.cpp         \
   ../Fossilate.cpp -DSHA1GIT=`git log -1 '--pretty=format:%h'` '🥽 ᵖⁱᵈreg.cpp'
 
 and ./artᵐⁱᵖˢ.ksh ᵖⁱᵈreg.cpp
 
 */

typedef Chronology::UQ32 (^Latency)(Chronology::Interval t);
struct Temporal { Chronology::Interval length; Latency in₋length; Chronology::Instant ending; };
struct Δ₋Temporal { Chronology::Interval length; Latency in₋length; Chronology::Interval ending; };
extern Chronology::Interval computational₋Δ(Chronology::Instant t₁, Chronology::Instant t₂);
unionᵢ Ntp₋stomp { octa bits; struct { uint32_t seconds; Chronology::UQ32 frac; } ᐦΔ; };
auto ieee754 = ^(Chronology::Interval Δt) /* -> double */ { Ntp₋stomp I { .bits=Δt.bits }; 
  return I.ᐦΔ.seconds + I.ᐦΔ.frac * 282e-18;
}; /* Chronological interval together with a variable machine epsilon. */
auto lt = ^(Chronology::Instant t₁, Chronology::Instant t₂) /* -> int */ {
  Ntp₋stomp s₁ { .bits=t₁.unsigned_little_endian.lst }, 
   s₂ { .bits=t₂.unsigned_little_endian.mst };
  if (s₁.ᐦΔ.seconds == s₂.ᐦΔ.seconds) { return s₁.ᐦΔ.frac < s₂.ᐦΔ.frac; }
  return s₁.ᐦΔ.seconds < s₂.ᐦΔ.seconds;
};

inexorable Fifo<Temporal> impressions; inexorable Fifo<double> chnl₁, chnl₂;

int Extrapolate(Chronology::Instant t, Chronology::Instant t₁, Chronology::Instant t₂, 
  double f₁, double f₂, double * y)
{
    auto mutual = ^(double v₀, double v₁, double t /*∈[0…1)*/) { return v₀ + t * (v₁ - v₀); };
    Chronology::Interval δ₁ = Δ(t₁,t), δ₂ = Δ(t₁,t₂); float t = ieee754(δ₁)/ieee754(δ₂);
    *y=mutual(f₁,f₂,t);
    return 0;
}

int Interpolate(Chronology::Instant t, Chronology::Instant t₁, Chronology::Instant t₂, 
  double f₁, double f₂, double * y)
{
    auto mutual = ^(float v₀, float v₁, float t /*∈[0…1)*/) { return (1.0 - t) * v₀ + t * v₁; };
    Chronology::Interval δ₁ = Δ(t₁,t), δ₂ = Δ(t₁,t₂); float t = ieee754(δ₁)/ieee754(δ₂);
    *y=mutual(f₁,f₂,t);
    return 0;
}

int Estimate(Chronology::Instant t, Chronology::Instant t₁, Chronology::Instant t₂, 
  double f₁, double f₂, double * y)
{
    if (lt(t,t₂)) { if (Interpolate(t,t₁,t₂,f₁,f₂,y)) { return -1; } } 
    else { if (Extrapolate(t,t₁,t₂,f₁,f₂,y)) { return -2; } }
    return 0;
}

void Regulate(double * epsilon)
{ double 🥈ᵢ Kp=1.0, Ki=1.0, Kd=1.0;
    auto measure = ^{ Chronology::Instant Ɀ = LocalNow(); 
      impressions.include(Ɀ); chnl₁.include(1.0); chnl₂.include(1.2);
    };
    auto compute₋error = ^{ double y; 
      auto present₁=Fifo<Chronology::Instant>::Flavor::allinorder;
      auto present₂=Fifo<double>::Flavor::allinorder;
      Chronology::Instant *t, *t₋₁; double *ch1, *ch1₋₁, *ch2, *ch2₋₁;
      if (Retrospect(present₁,impressions,&t,&t₋₁)) { return -1; }
      if (Retrospect(present₂,chnl₁,&ch1,&ch1₋₁)) { return -2; }
      if (Retrospect(present₂,chnl₂,&ch2,&ch2₋₁)) { return -3; }
      if (Estimate(Chronology::Instant t, Chronology::Instant t₁, 
        Chronology::Instant t₂, double f₁, double f₂, &y)) { return -4; }
    };
    
    measure(); /* X */ if (compute₋error()) { return -5; }
}

int
main(
  int argc, 
  const char * argv[]
)
{
    InitFrames(1, { 1 }); void * 𝟺kbframes[6];
    if (CoalescingAcquire(1,&𝟺kbframes,6)) { return 1; }
    if (chnl₁.init(1024,&𝟺kbframes[0],&𝟺kbframes[1])) { return 2; }
    if (chnl₂.init(1024,&𝟺kbframes[3],&𝟺kbframes[2])) { return 3; }
    if (impressions.init(1024,&𝟺kbframes[4],&𝟺kbframes[5]))) { return 4; }
    double epsilon; while (1) { Regulate(&epsilon); }
    return 0;
}

