/*  clock for Twinbeam. */

#include <Twinbeam.h>
#include <mips.hpp>
#include <pic32mz.hpp>
#include <pic32mzda.hpp>
#include <stable.hpp>
#include <rtcc.hpp>
#include <trng.hpp>
#include <System.h>

auto Putch = ^(char utf8) { putch(utf8); };
auto Getch = ^{ return getutf8(); };
auto Alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };
auto Put = ^(char32_t unicode) { if (UnicodeToUtf8(unicode, ^(const uint8_t *p,
  int bytes) { for (int i = 0; i < bytes; i++) Putch(*(p + i)); })) {
  __debug_break(0x10); } };
auto LocalNow = ^{ OptInitRTCC(false, ^(unsigned& y, unsigned& M, unsigned& d,
  unsigned& h, unsigned& m, unsigned& s, uint32_t& key1, uint32_t& key2, bool&
  rollback) { y=2012; M=1; d=24; h=17; m=1; s=5; key1=PIC32MZDA_KEY1; key2=
  PIC32MZDA_KEY2; }); int32_t t[6];
  GetRTCC(&t[0], &t[1], &t[2], &t[3], &t[4], &t[5]);
  Chronology chronology = SystemCalendricChronology();
  uint32_t halfsec = PIC32MZDA_RTCCON_HALFSEC & 🔎𝑀𝑍𝐷𝐴(RCON);
  return *(chronology.timestamp(t, halfsec ? 0xBFFFffff : 0x3FFFFFFF)); };
auto RandomInteger = ^(octa *out) { return TRNG(out); };
auto Where = ^{ return EarthbasedSpatial { 0.0, 0.0, 0.0 }; };
auto How = ^{ return Eulerangles {
  ^(Chronology::Instant t) { return 0.0; },
  ^(Chronology::Instant t) { return 0.0; },
  ^(Chronology::Instant t) { return 0.0; } }; };
auto x = ^(Chronology::Instant t) { return 1.0; };
auto y = ^(Chronology::Instant t) { return 1.0; };
auto z = ^(Chronology::Instant t) { return 1.0; };
auto VelocityEye1 = ^(Chronology::Instant t) { return Cartesian3D { x, y, z }; }; // Acceleration?
auto VelocityEye2 = ^(Chronology::Instant t) { return Cartesian3D { x, y, z }; };
auto 𝛳 = ^(Chronology::Instant t) { return 0.0; };
auto 𝛹 = ^(Chronology::Instant t) { return 0.0; };
auto 𝛷 = ^(Chronology::Instant t) { return 0.0; };
auto Head = ^(Chronology::Instant t) { return Eulerangles { 𝛳, 𝛹, 𝛷 }; };
auto EyeballsGradient = ^(Chronology::Instant t) { return Cartesian3D { x, y, z }; };
auto Milieu = ^(double radii, void (^enter)(Tuple<Cartesian3D, Cartesian3D,
  bool> ell), void (^exit)(Tuple<Cartesian3D, Cartesian3D> coords), void
  (^max)(double radii), void (^min)(double radii)) {
      // Flat or rounnd? Another round. Found gradient?
      // Cartesian2D c1 = ComputeCircleCenter(Cartesian2D a, Cartesian2D b, Cartesian2D c);
      // Cartesian2D c2 = ComputeCircleCenter(Cartesian2D a, Cartesian2D b, Cartesian2D c);
      // double 𝛥R = ..;
      // double v = ...;
  };

extern "C" void Isr() { }

extern "C" void mips_general_exception() { }

int
main(
  int argc,
  const char *argv[]
)
{
    if (PIC32MZDA_RCON_VBAT & 🔎𝑀𝑍𝐷𝐴(RCON)) {
        printf("Woke up from VBAT.\n");
        🔧0𝑀𝑍𝐷𝐴(RCON,VBAT); /* Clear VBAT. */
    }
    
    InitMZDAStarterBoard();
    
    🎭𝑀𝑍(OSCTUN, TUN, ^(__builtin_uint_t& shifted) { shifted = 0x1; });
    
    Chronology::Instant instant = LocalNow();
    
    Termlog << "Clock (Rev. " << SHA1GIT << ") is ";
    
    Chronology chronology = SystemCalendricChronology();
    
    if (InstantToText(chronology, instant, 0, ^(char digit) { Putch(digit); }))
    { Termlog << "Error when InstantToText" << eol; }
    
    Termlog << eol;
    
    for (;;);
    
    return 0;
}