/*  steganograph.h₍pp₎ a․𝘬․a '⳻⩻≟⩼⳺' | for disjunct and ¿non-disjunct? machines. */

struct Steganographics {
  void appendToJournal(Unicodes ucs);
};

struct n₋steganograph₋machine { int shelf₋stock; 
  
  struct { Kiddle token₋keyfile; ˢKnots𝟷ᵈ<Kiddle::Nonabsolute> keyfileindex; } para[3][3];
  
  /* ⤐ for cryptoanalysis later: */
  void * token₋map; /* ⬷ a․𝘬․a Map<0-255,Kiddle::Nonabsolute> at 'i φ'; also keyspace as structure for countinous operation. */
  /* f⬷ or cryptoanalysis before. */
  
  struct abelian₋steganographic { } sect₋₁[3][3];
/* ✁ until ✂️ and store --<shoebox>{steganographics} */
/* ✂️ */
  
  int Speciale(const char * keytext₋path, short ﹟, void (^line)(const char * fineprint));
  
  int load(int count, const char * keytext₋path[], void (^line)(const char * fineprint));
  
  int to₋text(int count, uint8_t bytes[], void (^finally)(utf8₋text text));
  
  int from₋text(utf8₋text text, void (^finally)(int count, uint8_t bytes[]));
  
};

#pragma mark Sixtyfour- and 32 bits linear congruence double-padding (i.𝘦 material-nondirect and for later 128-bits a․𝘬․a CSPRNG generators)

struct symmetric₋Cipher {
  
  uint64_t 🥈 MMIX₋A=6364136223846793005ul, MMIX₋C=1442695040888963407ul;
  
  uint64_t previous₋X; 
  
  inline uint64_t linear₋recurrence₋big(const uint64_t& a, uint64_t Xᵢ, const uint64_t& c) /* -> Xᵢ₊₁ */ { return (a*Xᵢ + c) /* mod 2^64 */ ; }
  inline uint32_t linear₋recurrence₋small(const uint32_t& a, uint32_t Xᵢ, const uint32_t& c) /* -> Xᵢ₊₁ */ { return (a*Xᵢ + c) /* mod 2^32 */; }
  /* auto combining₋recurrence₋bytes = ^(byte a, byte Xᵢ₋₁, byte b, byte X₁, byte c) /‌* -> Xᵢ₊₁ *‌/ { return (a*Xᵢ₋₁ + b*X₁ + __builtin_uint_t(c)) % 256; };
  auto linear₋recurrence₋natural = ^(uint16_t a, uint16_t Xᵢ₋₁, uint16_t c) /‌* -> Xᵢ₊₁ *‌/ { return (a*Xᵢ + __builtin_uint_t(c)) % 65536; }; */
  
  FOCAL int byte₋encrypt(int count, uint8_t * plaintext, 
    void (^finally)(int count, uint8_t * cipherbytes));
  
  int byte₋decrypt(int count, uint8_t * cipherbytes, void (^finally)(int count, 
   uint8_t * plaintext)) { return byte₋encrypt(count,cipherbytes,finally); }
  
#if defined 𝟷𝟸𝟾₋bit₋integers
  void re₋salt(uint32_t lo, uint32_t hi, __uint128_t iv);
#endif
  /* ⬷ a․𝘬․a 'salt', 'iv' and somtimes 'pin-code'/'encrypted-symmetric-key'. 
    iv is often sixteen network-ordered bytes. */
  
}; /* ⬷ a․𝘬․a 
  --<Pinecone>--<Additions>--<Security.h> and 
  --<CPUTests>--<FEFoundation>--<Security.h>. 
  
  also 'kerberos - dog - hades - 3 and --<Projects>--<🥽⋆imposture.cpp>'.
  
     🔭😐: 𝜙^n + 1/𝜙^n ∈ N ∧ 𝜙^n – 1/𝜙^n ∈ N
  
*/

