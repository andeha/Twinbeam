//
//  Fossilate.cpp
//  Additions
//

#include <Twinbeam.h>
#include <Additions/System.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
auto Alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };
#ifdef  __mips__
#include <mips.hpp>
#include <pic32mz.hpp>
#include <pic32mzda.hpp>
#include <stable.hpp>
#include <rtcc.hpp>
#include <trng.hpp>
DISORDERABLE auto InteractivelySetClock = ^(unsigned& y, unsigned& M, unsigned& d,
  unsigned& h, unsigned& m, unsigned& s, uint32_t& key1, uint32_t& key2, bool&
  rollback) { y=2012; M=1; d=24; h=17; m=1; s=5; key1=PIC32MZDA_KEY1; key2=
  PIC32MZDA_KEY2; rollback = false; };
auto LocalNow = ^{ OptInitRTCC(false, ^(unsigned& y, unsigned& M, unsigned& d,
  unsigned& h, unsigned& m, unsigned& s, uint32_t& key1, uint32_t& key2, bool&
  rollback) { InteractivelySetClock(y, M, d, h, m, s, key1, key2, rollback); });
  int32_t t[6]; GetRTCC(&t[0], &t[1], &t[2], &t[3], &t[4], &t[5]);
  Chronology chronology = SystemCalendricChronology();
  uint32_t halfsec = 🎭𝑀𝑍𝐷𝐴(RTCCON, HALFSEC); Opt<Chronology::Instant> now = 
  chronology.timestamp(t, halfsec ? 0xBFFFffff : 0x3FFFFFFF); return *now; };
auto RandomInteger = ^(octa *out) { return TRNG(out); };
#elif defined __x86_64__
#include <time.h>
auto LocalNow = ^{
  time_t now = time(NULL);
  // The number of seconds between the NTP Epoch 1 January 1900,
  // 00:00:00 and 00:00:00 Coordinated Universal Time (UTC), Thursday, 1
  // January 1970.
  const uint32_t ntpToUnix = 2208988800U;
  uint32_t ta = uint32_t(now + ntpToUnix);
  Chronology::Instant res; res.octa = uint64_t(ta)<<32; // NTPTimestamp { ta, 0 }.bits;
  return res; };
#include <immintrin.h>
__attribute__((target("rdrnd"))) int RandomInteger(octa *x) { for (int i = 0; 
  i < 10; i++) { if (_rdrand64_step(&(x->octa))) return 0; } return 1; }
#include <stdio.h>
uint8_t getutf8() { return (uint8_t)getc(stdin); }
void putch(uint8_t utf8) { putchar(utf8); }
#define __debug_break __builtin_debugtrap(); // __builtin_trap()
#endif
namespace ContextualAwareness {
 auto Where = ^{ return EarthbasedSpatial { 0.0, 0.0, 0.0 }; };
 auto How = ^{ return Eulerangles {
   ^(Chronology::Instant t) { return 0.0; },
   ^(Chronology::Instant t) { return 0.0; },
   ^(Chronology::Instant t) { return 0.0; } }; };
 auto Temperature = ^(Chronology::Instant t) { return 0; };
 auto Pressure = ^(Chronology::Instant t) { return 0; };
 auto Magnetometer = ^{ return Eulerangles {
   ^(Chronology::Instant t) { return 0.0; },
   ^(Chronology::Instant t) { return 0.0; },
   ^(Chronology::Instant t) { return 0.0; } }; };
}
namespace Probing {
 auto DecentAstarboardAhead = ^(Chronology::Instant t) { return 0.0; };
 auto DecentAstarboardAft = ^(Chronology::Instant t) { return 0.0; };
 auto DecentAportAhead = ^(Chronology::Instant t) { return 0.0; }; 
 auto DecentAportAft = ^(Chronology::Instant t) { return 0.0; }; // Baseline - decent = landing, so to speak...
}
namespace Emotionals {
 // Topside located TDK's.
 auto VelocityAstarboardAhead = ^(Chronology::Instant t) { return Cartesian3d { 0, 0, 0 }; };
 auto VelocityAstarboardAft = ^(Chronology::Instant t) { return Cartesian3d { 0, 0, 0 }; };
 auto VelocityAportAhead = ^(Chronology::Instant t) { return Cartesian3d { 0, 0, 0 }; };
 auto VelocityAportAft = ^(Chronology::Instant t) { return Cartesian3d { 0, 0, 0 }; };
 // and the errata...
 auto TemperatureAmidships = ^(Chronology::Instant t) { return 0; };
}
DISORDERABLE auto Init = ^{ 
#ifdef  __mips__
    StartTRNG(); 
#endif
};
DISORDERABLE auto Putch = ^(char utf8) { putch(utf8); };
DISORDERABLE auto Getch = ^{ return getutf8(); };
DISORDERABLE auto Put = ^(char32_t unicode) { if (UnicodeToUtf8(unicode, ^(const uint8_t *p,
  int bytes) { for (int i = 0; i < bytes; i++) Putch(*(p + i)); })) {
  __debug_break(0x10); } };
DISORDERABLE auto SetPixelAA = ^(int x, int y, long err) { printf("x=%d, y=%d, e=%ld\n", x, y, err); };
#pragma clang diagnostic pop –