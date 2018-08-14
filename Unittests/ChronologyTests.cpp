//
//  ChronologyTests.cpp
//  Twinbeam Tests
//

#include <Twinbeam.h>

#ifdef __x86_64__
#include <stdio.h>
#include <time.h>
auto LocalNow = ^{
  time_t now = time(NULL);
  // The number of seconds between the NTP Epoch 1 January 1900,
  // 00:00:00 and 00:00:00 Coordinated Universal Time (UTC), Thursday, 1
  // January 1970.
  const uint32_t NTPToUnixConversion = 2208988800U;
  uint32_t ta = uint32_t(now + NTPToUnixConversion);
  Chronology::Instant res; res.octa = uint64_t(ta)<<32; // NTPTimestamp { ta, 0 }.bits;
  return res;
};
#elif defined __mips__
#include <rtcc.hpp>
auto LocalNow = ^{ OptInitRTCC(false, ^(unsigned& y, unsigned& M, unsigned& d,
  unsigned& h, unsigned& m, unsigned& s, uint32_t& key1, uint32_t& key2, bool&
  rollback) { y=2012; M=1; d=24; h=17; m=1; s=5; key1=PIC32MZDA_KEY1; key2=
  PIC32MZDA_KEY2; }); int32_t t[6];
  GetRTCC(&t[0], &t[1], &t[2], &t[3], &t[4], &t[5]);
  Chronology chronology = SystemCalendricChronology();
  uint32_t halfsec = 🎭𝑀𝑍(RTCCON, HALFSEC);
  return *(chronology.timestamp(t, halfsec ? 0xBFFFffff : 0x3FFFFFFF)); };
#endif

UNITTEST(Chronology_localNow)
{
    Chronology chronology = SystemCalendricChronology();
	Chronology::Instant instant = LocalNow();
    if (InstantToText(chronology, instant, false, ^(char c) {
        printf("%c", c); } ))
    { ENSURE(false, "Error when ToString"); }
    ENSURE(instant.unsigned_little_endian.mst != 0 &&
      instant.unsigned_little_endian.lst != 0, "Error in LocalNow");
}

UNITTEST(Chronology_midnight)
{
    Chronology chronology = SystemCalendricChronology();
    int32_t parts[6] = { 1997, 1, 1, 12, 31, 32 };
    Opt<Chronology::Instant> instantOpt = chronology.timestamp(parts, 1);
    if (!instantOpt) { ENSURE(false, "Error when timestamp"); }
    Chronology::Instant instant = *instantOpt;
    printf("Timestamp is %lld and textually ", instant.octa);
    if (InstantToText(chronology, instant, false, ^(char c) {
        printf("%c", c);
    })) { ENSURE(false, "Error when TimestampToString"); } printf("\n");
    Tuple<int32_t, int32_t, int32_t, uint32_t> day =
      chronology.sinceMidnight(instant);
    printf("Since midnight is %lld, %lld, %lld. %lld\n",
      (__builtin_int_t)get<0>(day), (__builtin_int_t)get<1>(day),
      (__builtin_int_t)get<2>(day), (__builtin_int_t)get<3>(day));
}

UNITTEST(Chronology_increment)
{
    Chronology chronology = SystemCalendricChronology();
    int32_t parts[6] = { 1997, 1, 1, 12, 31, 32 };
    Opt<Chronology::Instant> instantOpt = chronology.timestamp(parts, 1);
    if (!instantOpt) { ENSURE(false, "Error when timestamp"); }
    Chronology::Instant instant = *instantOpt;
    printf("Timestamp is %lld and textually ", instant.octa);
    if (InstantToText(chronology, instant, false, ^(char c) {
        printf("%c", c);
    })) { ENSURE(false, "Error when TimestampToString"); } printf("\n");
    Chronology::Instant later = chronology.addSeconds(instant, 17);
    printf("Later is %lld and textually ", later.octa);
    if (InstantToText(chronology, later, false, ^(char c) {
        printf("%c", c);
    })) { ENSURE(false, "Error when TimestampToString"); } printf("\n");
    ENSURE(instant.octa != later.octa, "Error in addSeconds");
}

UNITTEST(Chronology_dayOfWeek)
{
    Chronology chronology = SystemCalendricChronology();
    Chronology::Instant instant = LocalNow();
    int weekday = chronology.dayofweek(instant);
    printf("Weekday is %lld", (__builtin_uint_t)weekday);
    auto weeknoToWeekday = ^(int weekday) {
        switch (weekday) {
            case 0: return "Sunday";
            case 1: return "Monday";
            case 2: return "Tuesday";
            case 3: return "Wednesday";
            case 4: return "Thursday";
            case 5: return "Friday";
            case 6: return "Saturday";
        }
        return "Unknown";
    };
    printf(" ...and in text %s.\n", weeknoToWeekday(weekday));
    ENSURE(weekday > 0 && weekday < 7, "Error in dayOfWeek");
}

UNITTEST(Chronology_TSAndBack)
{
    const char32_t *ts = U" 2012-01-24 12:00:00  ";
    __builtin_int_t tetras = UnicodesUntilNull(ts, BUILTIN_INT_MAX);
    Memoryregion region { (void *)ts, tetras<<2 };
    Memoryview datetime { &region, 0, region.bytes() };
    
    Chronology chronology = SystemCalendricChronology();
    if (Opt<Chronology::Instant> ts = TS(chronology, datetime)) {
        InstantToText(chronology, *ts, false, ^(char c) { printf("%c", c); });
    }
}

UNITTEST(Chronology_TS_withFrac_AndBack)
{
    const char32_t *ts = U" 2012-01-24 12:00:00.121  ";
    __builtin_int_t tetras = UnicodesUntilNull(ts, BUILTIN_INT_MAX);
    Memoryregion region { (void *)ts, tetras<<2 };
    Memoryview datetime { &region, 0, region.bytes() };
    
    Chronology chronology = SystemCalendricChronology();
    if (Opt<Chronology::Instant> ts = TS(chronology, datetime)) {
        InstantToText(chronology, *ts, true, ^(char c) { printf("%c", c); });
    }
}
