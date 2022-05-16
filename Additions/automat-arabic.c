/*  automat-arabic.c | input conversion, tokenization and parsing. */

import Twinbeam;

Opt<__builtin_int_t>
CastTˣᵗToInt(
  CastToIntOpinion (^feeder)(unsigned short &digit)
)
{ __builtin_int_t val = 0; __block unsigned short zero_to_nine; int sgn = 1;
   while (1) {
      CastToIntOpinion opinion = feeder(zero_to_nine);
      /* In C++20: 'using enum CastToIntOpinion;' */
      switch (opinion) {
       case CastToIntOpinion::accept: val *= 10; val += sgn*zero_to_nine; break;
       case CastToIntOpinion::rejecting: continue;
       case CastToIntOpinion::negate: sgn *= -1; break;
       case CastToIntOpinion::commit: return Opt<__builtin_int_t>(val);
       case CastToIntOpinion::annul: return Opt<__builtin_int_t>::no();
      }
   }
}

#define MAX_TOKEN 8192

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
         case Tokenizefact::fragment: *(unicodes + pos++) = u;
           if (symbol(unicodes, pos) == Inputcontrol::quit) return 0;
           eaten = false; break;
         case Tokenizefact::rejecting: continue;
         case Tokenizefact::eol:
         case Tokenizefact::separator: if (!eaten) { stop = (token(unicodes,
           pos) == Inputcontrol::quit); eaten = true; } if (stop || postulate
           == Tokenizefact::eol) return 0; pos = 0; continue;
         case Tokenizefact::error: return -1;
        }
    }
}

#pragma recto Language translation: 'Token is a noun'

int
TokenizeUtf8OrUnicode(
  Encoding encoding,
  memoryview content,
  __builtin_int_t& beam,
  void (^none𝘖rSeveral)(char32_t unicode, __builtin_int_t byteOffset, bool& stop)
)
{    __builtin_int_t bytes=content.bytecount, i=beam; Bits bits { content.scatter };
    while (i < bytes) { /* disjunct/sediment/segments */
       __builtin_int_t charBytes=4; bool stop=false;
       if (encoding == Encoding::utf8) {
          char8_t c = bits.operator[](i);
          charBytes = Utf8Followers(c) + 1;
          if (charBytes == -1) return -1; /* Possibly non-utf8 byte. */
          char32_t unicode = Utf8ToUnicode(&c,charBytes);
          if (unicode == 0xFFFE || unicode == 0xFFFF) { return -2; }
          none𝘖rSeveral(unicode,i,stop);
       } else {
          uint32_t unicode = bits.mips𝟷ᵈ(i, 0, Sentinel::bound, bytes<<2);
          none𝘖rSeveral(unicode,i,stop); }
       i += charBytes; beam=i;
       if (stop) break;
    }
    return 0;
}

int TokenizeUtf8ToUnicode(uint8_t * material, short bytes, 
  void (^none𝘖rSeveral)(__builtin_int_t byteOffset, char32_t unicode, 
    __builtin_int_t utf8bytes, int * stop)
)
{  __builtin_int_t i=0; int stop=false; while (1) {
     if (i > bytes) { return -1; }
     if (i == bytes) { goto finished; }
     char8_t c = *(material + i);
     __builtin_int_t charbytes = 1 + Utf8Followers(c);
     if (charbytes == -1) return -2; /* Possibly non-utf8 byte. */
     char32_t unicode = Utf8ToUnicode(&c,charbytes);
     if (unicode == 0xFFFE || unicode == 0xFFFF) { return -3; }
     none𝘖rSeveral(i,unicode,charbytes,&stop);
     if (stop) { return -4; }
     i += charbytes;
  }
finished:
  return 0;
} /* ⬷ called from --<Additions>--<Reflect.cpp>. */

#pragma recto Incremental vs. toggling 

int Chess(const char * 𝟽alt𝟾₋bitstring, 
  void (^move)(int fromrow, int fromcol, int torow, int tocol)
) { return 0; }

/* lon and lat; unicode csv, money/optcurrency */

