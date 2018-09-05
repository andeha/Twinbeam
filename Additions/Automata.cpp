//
//  Automata.cpp
//  Additions
//

#include <Twinbeam.h>

Opt<__builtin_int_t>
CastToInt(
  CastToIntOpinion (^feeder)(unsigned short& digit)
)
{ __builtin_int_t val = 0; __block unsigned short zero_to_nine; int sgn = 1;
    while (1) {
       CastToIntOpinion opinion = feeder(zero_to_nine);
       switch (opinion) {
         case CastToIntOpinion::accept: val *= 10; val += sgn*zero_to_nine; break;
         case CastToIntOpinion::rejecting: continue;
         case CastToIntOpinion::negate: sgn *= -1; break;
         case CastToIntOpinion::commit: return Opt<__builtin_int_t>(val);
         case CastToIntOpinion::annul: return Opt<__builtin_int_t>::no();
        }
     }
}

const int MAX_TOKEN = 8192;

int
ReadUtf8(
  Readlineopinion (^feeder)(char& utf8byte),
  Inputcontrol (^line)(char * line)
)
{ char utf8bytes[MAX_TOKEN]; int pos = 0;
    while (1) { if (pos >= MAX_TOKEN) return -1;
       Readlineopinion hypothesis = feeder(*(utf8bytes + pos));
       switch (hypothesis) {
          case Readlineopinion::accept: pos++; break;
          case Readlineopinion::rejecting: continue;
          case Readlineopinion::commit: if (line(utf8bytes) ==
            Inputcontrol::quit) return 0; pos=0; break;
          case Readlineopinion::quit: return -1;
        }
    }
}

int
ReadUnicode(
  Readlineopinion (^feeder)(char32_t& unicode),
  Inputcontrol (^line)(char32_t * line)
)
{ char32_t unicodes[MAX_TOKEN]; int pos = 0;
    while (1) { if (pos >= MAX_TOKEN) return -1;
       Readlineopinion hypothesis = feeder(*(unicodes + pos));
       switch (hypothesis) {
          case Readlineopinion::accept: pos++; break;
          case Readlineopinion::rejecting: continue;
          case Readlineopinion::commit: if (line(unicodes) ==
            Inputcontrol::quit) return 0; pos=0; break;
          case Readlineopinion::quit: return -1;
        }
    }
}

int
Tokenize(
  Tokenizefact (^feeder)(char32_t& unicode),
  Inputcontrol (^symbol)(char32_t * unicodes, __builtin_int_t count),
  Inputcontrol (^token)(char32_t * unicodes, __builtin_int_t count)
)
{ char32_t unicodes[MAX_TOKEN]; int pos = 0; char32_t u; bool eaten = true;
      bool stop = false;
    while (1) { if (pos >= MAX_TOKEN) return -1;
       Tokenizefact postulate = feeder(u);
       switch (postulate) {
          case Tokenizefact::fragment: *(unicodes + pos++) = u; if
            (symbol(unicodes, pos) == Inputcontrol::quit) return 0; eaten =
            false; break;
          case Tokenizefact::rejecting: continue;
          case Tokenizefact::eol:
          case Tokenizefact::separator: if (!eaten) { stop = (token(unicodes,
            pos) == Inputcontrol::quit); eaten = true; } if (stop || postulate
            == Tokenizefact::eol) return 0; pos = 0; continue;
          case Tokenizefact::error: return -1;
        }
    }
}

