/*  Automata.cpp | input conversion, tokenization and parsing. */

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

int 🥈ᵢ MAX_TOKEN = 8192;

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

#pragma mark - Language translation: 'Token is a noun'

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
    __builtin_int_t utf8bytes, bool& stop)
)
{  __builtin_int_t i=0; bool stop=false; while (1) {
     if (i > bytes) { return -1; }
     if (i == bytes) { goto finished; }
     char8_t c = *(material + i);
     __builtin_int_t charbytes = 1 + Utf8Followers(c);
     if (charbytes == -1) return -2; /* Possibly non-utf8 byte. */
     char32_t unicode = Utf8ToUnicode(&c,charbytes);
     if (unicode == 0xFFFE || unicode == 0xFFFF) { return -3; }
     none𝘖rSeveral(i,unicode,charbytes,stop);
     if (stop) { return -4; }
     i += charbytes;
  }
finished:
  return 0;
} /* ⬷ called from --<Additions>--<Reflect.cpp>. */

#pragma mark - Incremental vs. toggling 

int Chess(const char * 𝟽alt𝟾₋bitstring, 
  void (^move)(int fromrow, int fromcol, int torow, int tocol)
) { return 0; }

/* lon and lat; unicode csv, money/optcurrency */

#pragma mark - Times and datestamps

Opt<Chronology::instant>
TS(
  Encoding encoding, 
  Chronology chronology, 
  memoryview datetime
) NEVERBLURTS
{ /* …or 'find chronology𝛥 and recursively parse l and r'. */
    
    𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 enum class State { init, y1_2, y2_3, y3_4, y_hyphen, hyphen_M, 
      M1_2, M2_hyphen, hyphen_d1, d1_2, date_time, h1_2, h2_colon, colon_m1, 
      m1_2, m2_colon, colon_s1, s1_2, s2_optfrac, dot_frac, time, error
    } state = State::init;
    
    auto digit = ^(char32_t u) { return (0x30 <= u && u < 0x40); };
    
    auto whitespace = ^(char32_t u) { return u == '\t' || u == ' ' || 
      u == 0xa || u == 0xd; };
    
    auto atoi = ^(char32_t u) { return u - '0'; };
    
    auto ws𝘖𝘳EOT = ^(char32_t u) { return u == END_OF_TRANSMISSION || whitespace(u); };
    
    uint32_t 🥈 iⁿbase₂[] = { 0, /* 0, 1/10, 1/100, ..., 1/10⁻32 in UQ32. */
      0x19999999,0x28f5c28,0x418937,0x68db8,0xa7c5,0x10c6,0x1ad,0x2a,0x4,0,
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; /* ⬷ see --<🥽 Alloca.cpp>. */
    auto augment = ^(short 𝟶to𝟿, unsigned 𝟷𝟶⁻ˣ, uint32_t frac) { return (𝟶to𝟿*frac)*iⁿbase₂[𝟷𝟶⁻ˣ]; };
    /* 1/10 = 1/16 + 1/32 + 1/256 + 1/512 enum Rounding { RoundNearestUnder, 
      RoundNearestOver, RoundNearestErrorSquared }; */
    uint32_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 acc=0; /* ⬷ e․𝘨 0.101₂ = 1×1/2 + 0×1/4 + 1×1/8 = 5/8․ */
    unsigned 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 𝟷𝟶⁻ˣ=1; int32_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 y=0, M=0, d=0, h=0, m=0, s=0;
    /* Also: ∑ f(k)/10⁻k = ∑f₁(k)/2⁻k - ∑f₂(k)/2⁻k */
    /* ...as a 'reduction': NP = P*NP [See also Abramowitz and Stegun]. */
    
    🧵(Error) {
      case Error: return Opt<Chronology::instant>::no();
    } /* ⬷ Note that we're exiting from inside a block using `confess`. ⤐ */
    
    auto process = ^(char32_t u) {
        switch (state) {
            case State::init: if (whitespace(u)) { /* do nothing */ }
                else if (digit(u)) { y += 1000*atoi(u); state = State::y1_2; }
                else { state = State::error; }
                break;
            case State::y1_2:
                if (digit(u)) { y += 100*atoi(u); state = State::y2_3; }
                else { state = State::error; }
                break;
            case State::y2_3:
                if (digit(u)) { y += 10*atoi(u); state = State::y3_4; }
                else { state = State::error; }
                break;
            case State::y3_4:
                if (digit(u)) { y += 1*atoi(u); state = State::y_hyphen; }
                else { state = State::error; }
                break;
            case State::y_hyphen:
                if (u == '-') { state = State::hyphen_M; }
                else { state = State::error; }
                break;
            case State::hyphen_M:
                if (digit(u)) { M += 10*atoi(u); state = State::M1_2; }
                else { state = State::error; }
                break;
            case State::M1_2:
                if (digit(u)) { M += 1*atoi(u); state = State::M2_hyphen; }
                else { state = State::error; }
                break;
            case State::M2_hyphen:
                if (u == '-') { state = State::hyphen_d1; }
                else { state = State::error; }
                break;
            case State::hyphen_d1:
                if (digit(u)) { d += 10*atoi(u); state = State::d1_2; }
                else { state = State::error; }
                break;
            case State::d1_2:
                if (digit(u)) { d += 1*atoi(u); state = State::date_time; }
                else { state = State::error; }
                break;
            case State::date_time:
                if (whitespace(u)) { /* do nothing */ }
                else if (digit(u)) { h += 10*atoi(u); state = State::h1_2; }
                else { state = State::error; }
                break;
            case State::h1_2:
                if (digit(u)) { h += 1*atoi(u); state = State::h2_colon; }
                else { state = State::error; }
                break;
            case State::h2_colon:
                if (u == ':') { state = State::colon_m1; }
                else { state = State::error; }
                break;
            case State::colon_m1:
                if (digit(u)) { m += 10*atoi(u); state = State::m1_2; }
                else { state = State::error; }
                break;
            case State::m1_2:
                if (digit(u)) { m += 1*atoi(u); state = State::m2_colon; }
                else { state = State::error; }
                break;
            case State::m2_colon:
                if (u == ':') { state = State::colon_s1; }
                else { state = State::error; }
                break;
            case State::colon_s1:
                if (digit(u)) { s += 10*atoi(u); state = State::s1_2; }
                else { state = State::error; }
                break;
            case State::s1_2:
                if (digit(u)) { s += 1*atoi(u); state = State::s2_optfrac; }
                else { state = State::error; }
                break;
            case State::s2_optfrac: /* ⬷ terminal. */
                if (u == '.') { state = State::dot_frac; }
                else if (ws𝘖𝘳EOT(u)) { state = State::time; }
                else { state = State::error; }
                break;
            case State::dot_frac:
                if (digit(u)) { uint32_t digit=atoi(u); acc=augment(digit,𝟷𝟶⁻ˣ,acc); 𝟷𝟶⁻ˣ++; }
                else if (whitespace(u)) { state = State::time; }
                else { state = State::error; }
                break;
            case State::time: /* ⬷ terminal. */
                if (ws𝘖𝘳EOT(u)) { /* do nothing */ }
                else { state = State::error; }
                break;
            case State::error: confess(Error);
        }
    }; /* Req: state, y, M, d, h, m, s, frac */
    
    __builtin_int_t beam=0; /* SemanticPointer<char32_t *> unicode =
       beam.unicodeLook(0, BinaryChoiceToRight); */
     if (TokenizeUtf8OrUnicode(encoding, datetime, beam, ^(char32_t unicode,
       __builtin_int_t byteOffset, bool& stop) { process(unicode); }))
     { return Opt<Chronology::instant>::no(); }
    
    if (state != State::time && state != State::s2_optfrac)
        return Opt<Chronology::instant>::no();
    
    int32_t t[6] = { y, M, d, h, m, s };
    
    return chronology.integers₋encode(t,acc);
}

