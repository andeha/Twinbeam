/*  use.h a․𝘬․a båt | persisted in bronze, located elsewhere and measuring antagonist. */

struct achine {
ENCLAVED static 𝟽₋bitPath𝘖rBytes defaultIdentityFilepath;
ENCLAVED int readPKCS12(
  𝟽₋bitPath𝘖rBytes filepath = defaultIdentityFilepath, 
  bool forDecryptionAndSigningToo = false
);
ENCLAVED int createPKCS12(𝟽₋bitPath𝘖rBytes filepath);
ENCLAVED int changePassword(𝟽₋bitPath𝘖rBytes filepath);
ENCLAVED void scramblePrivate();
};

struct recollect { /* ⬷ a․𝘬․a 'telefunken'. */
ENCLAVED void addCertificate(uint8_t *stream, int bytes);
ENCLAVED void addCertificate(𝟽₋bitPath𝘖rBytes filepath);
ENCLAVED void removeCertificate(octa certserial);
};

struct scripttext {
ENCLAVED void rentaltoken(𝟽₋bitPath𝘖rBytes identifier, uint64_t seconds, 
 bool relaxed₋ending, void (^out)(𝟽₋bitPath𝘖rBytes identifier, 𝟽₋bitPath𝘖rBytes x509tokenrental, 𝟽₋bitPath𝘖rBytes keyprivatehash));
ENCLAVED int rentaltokenInsidePeriod(𝟽₋bitPath𝘖rBytes x509tokenrental, 𝟽₋bitPath𝘖rBytes keyprivatehash);
ENCLAVED int has₋expired(𝟽₋bitPath𝘖rBytes x509tokenrental);
enum Errorcode { periodic };
MACRO static void Error(Errorcode code) BLURTS {
  switch ((int)code) {
  case 1: break; /* majour */
  case 2: break; /* periodic */
  }
}
ENCLAVED int toggleExecutable(𝟽₋bitPath𝘖rBytes filepath);
ENCLAVED int has₋been₋revoked(𝟽₋bitPath𝘖rBytes filepath);
int decrypt(𝟽₋bitPath𝘖rBytes x509tokenrental, int count, __builtin_uint_t * stream, 
 void (^out)(int count, __builtin_uint_t * stream));
};