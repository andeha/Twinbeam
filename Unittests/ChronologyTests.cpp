//
//  ChronologyTests.cpp
//  Twinbeam Tests
//

#include <Twinbeam.h>
#include <stdio.h>

UNITTEST(Chronology_localNow)
{
    Chronology chronology = SystemCalendricChronology();
    Chronology::Instant instant = chronology.localNow(0);
    if (InstantToText(chronology, instant, false, ^(char c) {
        printf("%c", c); } ))
    { ENSURE(false, "Error when ToString"); }
    ENSURE(instant.unsigned_little_endian.mst != 0 &&
      instant.unsigned_little_endian.lst != 0, "Error in localNow");
}

UNITTEST(Chronology_midnight)
{
    Chronology chronology = SystemCalendricChronology();
    int32_t parts[6] = { 1997, 1, 1, 12, 31, 32 };
    Chronology::Instant instant = chronology.timestamp(parts, 1);
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
    Chronology::Instant instant = chronology.timestamp(parts, 1);
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
    Chronology::Instant instant = chronology.localNow(0);
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
