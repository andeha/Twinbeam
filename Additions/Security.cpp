//
//  Security.cpp
//  Helixstore
//
//  Created by Anders Hansson on 28/10/15.
//  Copyright © 2015 Anders Hansson. All rights reserved.
//

#include <Helixstore/Security.h>
#include <FEFoundation/Base64.h>
#include <FEFoundation/Compression.h>
#include <FEFoundation/System.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/pkcs12.h>
#include <openssl/x509.h>
#include <openssl/cms.h>
#include <openssl/ssl.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <random>

#pragma recto Security::SecurityImp Declaration

INNER_CLASS
class Security::Implementation {
    
    ALWAYS_INLINE
    Implementation(
        bool allowSelfsignedIdentity,
        std::function<void (std::string)> progress
    );
    
public:
    
    ALWAYS_INLINE
    Implementation(
        bool allowSelfsignedIdentity,
        std::function<std::string (std::string, bool)> input,
        std::function<void (std::string)> progress
    );
    
    ALWAYS_INLINE
    Implementation(
        bool allowSelfsignedIdentity,
        std::string certificateAsPEM,
        std::function<void (std::string)> progress
    );
    
    ALWAYS_INLINE
    ~Implementation();
    
#pragma recto PKCS#12
    
    ALWAYS_INLINE
    bool
    readPKCS12(
        std::string filePath,
        bool forDecryptionAndSigningAlso
    );
    
    ALWAYS_INLINE
    bool
    createPKCS12(
        std::string filePath
    );
    
    ALWAYS_INLINE
    bool
    changePassword(
        std::string filePath
    );
    
    ALWAYS_INLINE void wipePrivateKey();
    
    // TODO: Consider implications in in the introduction of an optional
    // (clearly communicated) private key posting.
    
    // The following API may be used to create associative copies of the
    // private key and should require entry of old password and an alternative.
    
    // openssl pkcs12 -in pkcs12.pfx -nocerts -nodes  | openssl rsa > id_rsa
    // openssl pkcs12 -in pkcs12.pfx -clcerts -nokeys | openssl x509 -pubkey
    // -noout | ssh-keygen -f /dev/stdin -i -m PKCS8
    
    // bool
    // duplicatePrivateKey(
    //    std::string filePath
    //);
    
#pragma recto Encryption/Decryption
    
    ALWAYS_INLINE
    void
    encryptData(
        std::function<int (unsigned char *, int)> input,
        std::function<void (unsigned char *, int, unsigned char *, int)> header,
        std::function<void (unsigned char *, int)> data
    );
    
    ALWAYS_INLINE
    void
    decryptData(
        unsigned int encryptedKeyLength,
        unsigned char * ek,
        unsigned char * iv,
        std::function<int (unsigned char *, int)> input,
        std::function<void (unsigned char *, int)> output
    );
    
#pragma recto Cipher Context
    
    ALWAYS_INLINE CipherContext * createCipherContext();
    
#pragma recto Pointer Encryption
    
    ALWAYS_INLINE
    void *
    encryptPointer(
        void * ptr,
        CipherContext ** cipherContext
    );

    ALWAYS_INLINE
    void *
    decryptPointer(
        void * ptr,
        CipherContext * cipherContext
    );

#pragma recto String Encryption/Decryption
    
    ALWAYS_INLINE
    void
    encryptString(
        const std::string& plainText,
        bool ensureAppendPossible,
        CipherContext ** cipherContext,
        std::function<void (const std::string& block)> callback
    );
    
    ALWAYS_INLINE
    void
    decryptString(
        const std::string& cipherText,
        CipherContext * cipherContext,
        std::function<void (const std::string& block)> callback
    );
    
#pragma recto Memory Overwrite Encryption
    
    ALWAYS_INLINE
    void
    encrypt(
        unsigned char * ptr,
        uint64_t length,
        CipherContext ** cipherContext
    );
    
    ALWAYS_INLINE
    void
    decrypt(
        unsigned char * ptr,
        uint64_t length,
        CipherContext * cipherContext
    );
    
#pragma recto Low-Level Signing and Validation
    
    ALWAYS_INLINE
    bool
    sign(
        unsigned char * ptr,
        uint64_t bytes,
        unsigned char ** signature,
        unsigned int * signatureLength
    ) const;
    
    ALWAYS_INLINE
    bool
    validateSignature(
        unsigned char * message,
        int             messageLength,
        unsigned char * signature,
        int             signatureLength
    ) const;
    
#pragma recto Fingerprinting
    
    ALWAYS_INLINE std::string getFingerprint()      const;
    
    ALWAYS_INLINE std::string getCertificateAsPEM() const;
    
#pragma recto Certificate Store
    
    ALWAYS_INLINE
    void
    addCertificate(
        unsigned char * data,
        int length
    );
    
    ALWAYS_INLINE
    void
    addCertificate(
        std::string filePath
    );
    
    ALWAYS_INLINE
    void
    removeCertificate(
        unsigned int certSerial
    );

#pragma recto Boost ASIO Credentials

    ALWAYS_INLINE
    bool
    verifyConnection(
        X509_STORE_CTX * context
    );
    
    ALWAYS_INLINE
    void
    addCertchainAndKeyToContext(
        SSL_CTX * context
    );
    
private:
    
    typedef unsigned long ScalarType;
    
    ALWAYS_INLINE void addRootCertificates();
    
    ALWAYS_INLINE EVP_PKEY * getPublicKey() const;
    
    ALWAYS_INLINE void computeFingerprint();
    
private:
    
    // TODO: For improved security, consider implications of randomly permuting
    // the member variables here. (Or an encrypting base class.)
    
    bool                                            allowSelfsignedIdentity_;
    
    std::function<std::string (std::string, bool)>  input_;
    
    std::function<void (std::string)>               progress_;
    
    EVP_PKEY *                                      privateKey_;

    // The following variable contains the public key.
    
    X509 *                                          certificate_;
    
    // The following string contains can be used to validate that a
    // key pair matches.
    
    std::string                                     fingerprint_;
    
    // Certificate store holding CA certificates.
    
    X509_STORE *                                    certStore_;
    
    // Timer that releases the primary key from primary memory.
    
    unsigned int                                    privateKeyHoldout_;
    
};

typedef void cstyle_function_ptr(std::string);

// Since we're using GCM, plaintext and ciphertext are of identical length.
// Intel has recently added the PCLMULQDQ instruction to the ia64 platform.

#define kEncryptionAlgorithm EVP_aes_128_gcm()

#pragma recto - PKCS#12

ALWAYS_INLINE
static
bool
readPKCS12(
    FILE * pkcs12_file,
    bool forDecryptionAndSigningAlso,
    bool allowSelfsignedIdentity,
    std::function<std::string (std::string, bool)> passphrase,
    std::function<void (std::string)> progress,
    std::function<void (EVP_PKEY *, X509 *, STACK_OF(X509)*)> completion
)
{
    PKCS12 * p12 = d2i_PKCS12_fp(pkcs12_file, NULL);
    
    std::string password = "";
    
    if (forDecryptionAndSigningAlso          &&
        PKCS12_verify_mac(p12, "", 0)   == 0 &&
        PKCS12_verify_mac(p12, NULL, 0) == 0) {
        
        password = passphrase("Password ", true);
        
    }
    
    EVP_PKEY        * key       = NULL;
    X509            * cert      = NULL;
    STACK_OF(X509)  * ca_certs  = NULL;
    
//    if (forDecryptionAndSigningAlso) {
        
        if (PKCS12_parse(p12, password.c_str(), &key, &cert, &ca_certs) == 0) {
        
            throw SecurityError("Unable to parse PKCS#12 file");
                
        }
    
        if (key == NULL || cert == NULL) {
        
            progress("PKCS#12 file does not contain a key and a certificate");
        
            return false;
        }
 /*   }
    
    else {
        
        if (experimental_PKCS12_parse(p12, &cert, &ca_certs) == 0) {
            
            throw SecurityError("Unable to parse PKCS#12 file");
            
        }
        
        if (cert == NULL) {
            
            progress("PKCS#12 file does not contain a certificate");
            
            return false;
        }
    }
*/    
    if (ca_certs == NULL) {
        
        progress("PKCS#12 file is self-signed");
        
    }
        
    completion(key, cert, ca_certs);
    
    // Deallocate allocated objects
    
    //EVP_PKEY_free(key);
    
    //X509_free(cert);
    
    //sk_X509_free(ca_certs);
    
    PKCS12_free(p12);
    
    return true;
}

ALWAYS_INLINE
static
bool
writePKCS12(
    PKCS12 * p12,
    FILE * outfile,
    std::function<void (std::string)> progress
)
{
    if (i2d_PKCS12_fp(outfile, p12) == 0) {
        
        progress("Could not write PKCS#12 file");
        
    }
    
    return true;
}

ALWAYS_INLINE
static
void
makeCertCallback(
    int p,
    int n,
    void * arg
)
{
    if (arg) {
        
        cstyle_function_ptr * progress =
            reinterpret_cast<cstyle_function_ptr *>(arg);
        
        progress("*");
    }
}

ALWAYS_INLINE
static
bool
makeCertificate(
    int bits,
    int serial,
    int days,
    std::string country,
    std::string commonName,
    std::function<void (std::string)> progress,
    X509 **x509,
    EVP_PKEY **privKey
)
{
    EVP_PKEY * pk;
    if ((privKey == NULL) || (*privKey == NULL)) {
        
        if ((pk = EVP_PKEY_new()) == NULL) {
            
            progress("Could not create private RSA key");
            
            return false;
        }
    }
    else {
        
        pk = *privKey;
        
    }
    
    X509 * x;
    if ((x509 == NULL) || (*x509 == NULL)) {
        
        if ((x = X509_new()) == NULL) {
            
            progress("Could not create X509 certificate");
            
            return false;
        }
    }
    else {
        
        x = *x509;
        
    }
    
    cstyle_function_ptr * ptr_fun = progress.target<cstyle_function_ptr>();
    
    RSA * rsa = RSA_generate_key(bits, RSA_F4, makeCertCallback,
        (void *)ptr_fun);
    
    if (!EVP_PKEY_assign_RSA(pk, rsa)) {
        
        progress("Could not assign RSA keys");
        
        return false;
    }
    
    rsa = NULL;
    
    if (X509_set_version(x, 2) == 0) {
        
        progress("Could not assign version");
        
        return false;
    }
    
    if (ASN1_INTEGER_set(X509_get_serialNumber(x), serial) == 0) {
        
        progress("Could not set serial number");
        
        return false;
    }
    
    X509_gmtime_adj(X509_get_notBefore(x), 0);
    
    // The certificate is valid for 236.71 years
    X509_gmtime_adj(X509_get_notAfter(x), (long)60*60*24*days);
    
    if (X509_set_pubkey(x, pk) == 0) {
        
        progress("Could not set public key");
        
        return false;
    }
    
    X509_NAME * name = X509_get_subject_name(x);
    
    /*
     * This function creates and adds the entry, working out the
     * correct string type and performing checks on its length.
     * Normally we'd check the return value for errors...
     */
    
    if (X509_NAME_add_entry_by_txt(name, "C", MBSTRING_ASC,
            (const unsigned char *)country.c_str(), -1, -1, 0) == 0) {
        
        progress("Could not add C entry");
        
        return false;
    }
    
    if (X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC,
            (const unsigned char *)commonName.c_str(), -1, -1, 0) == 0) {
        
        progress("Could not add CN entry");
        
        return false;
    }
    
    /*
     * The certificate is self signed so set the issuer name to be the same as
     * the subject.
     */
    
    if (X509_set_issuer_name(x, name) == 0) {
        
        progress("Could not set issuer name");
        
        return false;
    }
    
    if (!X509_sign(x, pk, EVP_sha1())) {
        
        progress("Could not sign X509 certificate");
        
        return false;
    }
    
    *x509 = x;
    
    *privKey = pk;
    
    return true;
}

ALWAYS_INLINE
static
bool
createPKCS12(
    std::string name,
    std::string country,
    std::string commonName,
    std::function<std::string (std::string, bool)> passphrase,
    std::function<void (std::string)> progress,
    PKCS12 ** p12
)
{
    X509     * x509 = NULL;
    EVP_PKEY * pkey = NULL;
    
    std::string pass = passphrase("Password: ", true);
    
    // TODO: Increase key length to 2048.
    makeCertificate(1024 /*512*/, 6, 365, country.c_str(),
                    commonName.c_str(), progress, &x509, &pkey);
    
    *p12 = PKCS12_create((char *)pass.c_str(), (char *)name.c_str(),
                  pkey, x509, NULL, 0, 0, 0, PKCS12_DEFAULT_ITER, 0);
    
    if (!p12) {
        
        progress("Error creating PKCS#12 container");
        
        return false;
    }
    
    return true;
}

ALWAYS_INLINE
static
bool
changePassword(
    FILE * pkcs12_file,
    std::string oldPassword,
    std::string newPassword,
    std::function<void (std::string)> progress
)
{
    PKCS12 * p12 = d2i_PKCS12_fp(pkcs12_file, NULL);
    
    if (PKCS12_newpass(p12,  (char *)oldPassword.c_str(),
                       (char *)newPassword.c_str()) == 0) {
        
        progress("Could not change password on PKCS#12 file");
        
        return false;
    }
    
    fseek(pkcs12_file, 0, SEEK_SET);
    
    if (!::writePKCS12(p12, pkcs12_file, progress)) {
     
        return false;
    }
    
    return true;
}

#pragma recto - SHA1 Fingerprinting

ALWAYS_INLINE
std::string
sha1(
     void * ptr,
     unsigned int bytes
)
{
    unsigned char * ibuf = (unsigned char *)ptr;
    
    unsigned char obuf[20];
    
    SHA1(ibuf, bytes, obuf);
    
    char buffer[40]; buffer[39] = 0;
    
#pragma unroll 20
    for (int i = 0; i < 20; i++) {
        
        sprintf(&buffer[2*i], "%02X", obuf[i]);
        
    }
    
    return std::string(buffer);
}

#pragma recto - Low-Level Signing and Verification

ALWAYS_INLINE
static
bool
Sign(
    EVP_PKEY * privateKey,
    unsigned char * ptr,
    uint64_t bytes,
    unsigned char ** signature,
    unsigned int * signatureLength
)
{
    EVP_MD_CTX md_ctx;
    EVP_SignInit(&md_ctx, EVP_sha1());
    EVP_SignUpdate(&md_ctx, ptr, bytes);
    
    *signatureLength = EVP_PKEY_size(privateKey);
    *signature = (unsigned char *)malloc(*signatureLength);
    
    int err = EVP_SignFinal(&md_ctx, *signature, signatureLength, privateKey);
    
    if (err != 1) {
        ERR_print_errors_fp(stderr);
        return false;
    }
    
    return true;
}

ALWAYS_INLINE
static
bool
ValidateSignature(
    EVP_PKEY * publicKey,
    unsigned char * message,
    int             messageLength,
    unsigned char * signature,
    int             signatureLength
)
{
    EVP_MD_CTX md_ctx;
    EVP_VerifyInit(&md_ctx, EVP_sha1());
    
    EVP_VerifyUpdate(&md_ctx, message, messageLength);
    
    int err =
        EVP_VerifyFinal(
            &md_ctx,
            (const unsigned char *)signature,
            signatureLength,
            publicKey
        );
    
    if (err != 1) {
        ERR_print_errors_fp(stderr);
        return false;
    }
    
    // printf("Signature Verified Ok.\n");
    
    return true;
}

#pragma recto - Cipher Context

ALWAYS_INLINE
static
int
getIVLength()
{
    return EVP_CIPHER_iv_length(kEncryptionAlgorithm);
}

ALWAYS_INLINE
static
void
initCipherContext(
    EVP_PKEY * publicKey,
    EVP_CIPHER_CTX * ctx,
    Security::CipherContext * cipherContext
)
{
    unsigned char *ek = NULL;
    int eklen;
    
    EVP_CIPHER_CTX_init(ctx);
    ek = (unsigned char *)malloc(EVP_PKEY_size(publicKey));
    
    if (!EVP_SealInit(ctx, kEncryptionAlgorithm, &ek, &eklen, cipherContext->iv,
                      &publicKey, 1))
    {
        free(ek);

        throw SecurityError("EVP_SealInit failed");
    }
    
    /* 
     * First we write out the encrypted key length, then the encrypted key,
     * then the iv (the IV length is fixed by the cipher we have chosen).
     */
    
    cipherContext->encryptedKey         = ek;
    cipherContext->encryptedKeyLength   = eklen;
    cipherContext->ivLength             = getIVLength();
}

ALWAYS_INLINE
static
EVP_CIPHER_CTX *
nativeHandle(
    Security::CipherContext * cipherContext
)
{
    return (EVP_CIPHER_CTX *)cipherContext->nativeHandle;
}

ALWAYS_INLINE
static
void
wipeCipherContext(
    Security::CipherContext * cipherContext
)
{
    free(cipherContext->encryptedKey);
    free(cipherContext->nativeHandle);
}

#pragma recto - Encryption

ALWAYS_INLINE
static
void
encryptData(
    EVP_CIPHER_CTX * ctx,
    std::function<int (unsigned char *, int)> input, // Number of bytes written (0 means EOF), buffer and max buffer.
    std::function<void (unsigned char *, int)> data
)
{
    // BufferLength must be a multiple of three since we may Base-64 encode
    // the encrypted content and later append additional encoded strings.
    
    const unsigned int bufferLength = 3078;
    
    unsigned char buffer_in[bufferLength], buffer_out[bufferLength];
    int len_in, len_out;

    while ((len_in = (int)input(buffer_in, sizeof buffer_in)) > 0) {
        
        if (!EVP_SealUpdate(ctx, buffer_out, &len_out, buffer_in, len_in)) {
            
            throw SecurityError("EVP_SealUpdate failed");
        
        }
        
        if (len_out > 0) data(buffer_out, len_out);
    }

    // Note: The EVP_SealFinal is currently considered superfluous with the
    // introduction of the Galois Field Mode.
}

ALWAYS_INLINE
static
void
encryptData(
    EVP_PKEY * publicKey,
    std::function<int (unsigned char *, int)> input,                            // Number of bytes written (0 means eof), buffer and max buffer.
    std::function<void (unsigned char *, int, unsigned char *, int)> header,    // The encrypted key, number of bytes, iv length.
    std::function<void (unsigned char *, int)> data                             // Encrypted data and number of bytes.
)
{
    EVP_CIPHER_CTX ctx;
    Security::CipherContext cipherContext;
    
    initCipherContext(publicKey, &ctx, &cipherContext);
    
    header(cipherContext.encryptedKey,
           cipherContext.encryptedKeyLength,
           cipherContext.iv, cipherContext.ivLength);
    
    encryptData(&ctx, input, data);
}

#pragma recto - Decryption

ALWAYS_INLINE
static
void
decryptData(
    EVP_PKEY * privateKey,
    unsigned int keyLength,
    unsigned char * ek,
    unsigned char * iv,
    std::function<int (unsigned char *, int)> input, // Number of bytes written (0 means EOF), buffer and max buffer
    std::function<void (unsigned char *, int)> output
)
{
    EVP_CIPHER_CTX ctx;
    unsigned char buffer_in[3078];
    unsigned char buffer_out[4096 + EVP_MAX_IV_LENGTH];
    int len_in;
    int len_out;
    
    EVP_CIPHER_CTX_init(&ctx);
    
    if (keyLength > EVP_PKEY_size(privateKey)) {
        
        throw SecurityError(
            "Bad encrypted key length (" + std::to_string(keyLength) + " > " +
            std::to_string(EVP_PKEY_size(privateKey)));

    }

    if (!EVP_OpenInit(&ctx, kEncryptionAlgorithm, ek, keyLength, iv, privateKey)) {
        
        throw SecurityError("EVP_OpenInit failed");

    }
    
    while ((len_in = (int)input(buffer_in, sizeof buffer_in)) > 0) {
        
        if (!EVP_OpenUpdate(&ctx, buffer_out, &len_out, buffer_in, len_in)) {
            
            throw SecurityError("EVP_OpenUpdate failed");

        }
        
        if (len_out > 0) output(buffer_out, len_out);
        
    }
    
    if (!EVP_OpenFinal(&ctx, buffer_out, &len_out)) {
        
        // When decrypting the return value of EVP_DecryptFinal() or
        // EVP_CipherFinal() indicates if the operation was successful. If it
        // does not indicate success the authentication operation has failed and
        // any output data MUST NOT be used as it is corrupted.
        
        ;
        //  throw SecurityError("EVP_OpenFinal failed");

    }
    
    output(buffer_out, len_out);
}

#pragma recto - Implementation Class

Security::Implementation::Implementation(
    bool allowSelfsignedIdentity,
    std::function<void (std::string)> progress

)
{
    OpenSSL_add_all_algorithms();
    //OpenSSL_add_all_digests();
    ERR_load_crypto_strings();
    
    allowSelfsignedIdentity_    = allowSelfsignedIdentity;

    progress_                   = progress;
    
    privateKey_                 = NULL;
    
    certificate_                = NULL;
    
    certStore_                  = X509_STORE_new();
    
    addRootCertificates();
}

Security::Implementation::Implementation(
    bool allowSelfsignedIdentity,
    std::function<std::string (std::string, bool)> input,
    std::function<void (std::string)> progress
)
    : Implementation(allowSelfsignedIdentity, progress)
{
    input_ = input;
}

Security::Implementation::Implementation(
    bool allowSelfsignedIdentity,
    std::string certificateAsPEM,
    std::function<void (std::string)> progress
)
    : Implementation(allowSelfsignedIdentity, progress)
{
    BIO * bio = BIO_new_mem_buf((void *)certificateAsPEM.c_str(),
                    (int)certificateAsPEM.size());
    
    if (!PEM_read_bio_X509(bio, &certificate_, NULL, NULL)) {
        
        throw FundamentalError(
            "Unable to import certificate in PEM format"
        );
        
    }

    BIO_free(bio);
    
    computeFingerprint();
}

Security::Implementation::~Implementation()
{
    if (privateKey_)    { EVP_PKEY_free(privateKey_);   privateKey_  = NULL;   }
    
    if (certificate_)   { X509_free(certificate_);      certificate_ = NULL;   }
    
    if (certStore_)     { X509_STORE_free(certStore_);  certStore_   = NULL;   }
}

#pragma recto Private Stuff

EVP_PKEY * Security::Implementation::getPublicKey() const
{
    return X509_get_pubkey(certificate_);
}

void Security::Implementation::computeFingerprint()
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    
    X509_pubkey_digest(certificate_, EVP_sha1(), hash, NULL);
    
    unsigned long length =
        StringLengthIfBase64Encoded(SHA_DIGEST_LENGTH, false);

    char * buffer = new char[length];
    
    Base64Encode(buffer, (const char *)hash, SHA_DIGEST_LENGTH, NULL);
    
    fingerprint_ = std::string(buffer, length);
    
    delete [] buffer;
}

#pragma recto PKCS#12

bool
Security::Implementation::readPKCS12(
    std::string filePath,
    bool forDecryptionAndSigningAlso
)
{
    FILE * file = fopen(filePath.c_str(), "rb");
    
    if (!file) { throw SecurityError("Unable to open '" + filePath + "'"); }

    bool result =
        ::readPKCS12(file,
            forDecryptionAndSigningAlso,
            allowSelfsignedIdentity_,
            input_,
            progress_,
            [ this ]
            (EVP_PKEY * privKey, X509 * cert, STACK_OF(X509) * ca_certs) {
                
                auto cacert_count = sk_X509_num(ca_certs);
                
                if (cacert_count <= 0) {
                    
                    if (!allowSelfsignedIdentity_) {
                    
                        progress_("PKCS#12 file is self-signed");

                        goto error;
                        
                    }
                    
                    // TODO: Note the security problem here.
                    
                }
                else {
                    
                    // Attempt to validate the certificates in the PCS#12 file.
                    
                    if (certStore_ == NULL) {
                        
                        progress_("Could not create certificate store");
                        
                        goto error;
                        
                    }
                    
                    X509_STORE_CTX * ctx = X509_STORE_CTX_new();
                    
                    if (X509_STORE_CTX_init(ctx, certStore_, cert, ca_certs) == 0) {
                        
                        progress_("Error in X509_STORE_CTX_init");
                        
                        goto error;
                    }

                    if (X509_verify_cert(ctx) != 1) {
                        
                        progress_("Invalid certificate chain");
                        
                        goto error;
                        
                    }
                }
                
                privateKey_     = privKey;
                
                certificate_    = cert;
                
                computeFingerprint();
                
                return;
                
            error:
                
                privateKey_     = NULL;
                
                certificate_    = NULL;
                
            }
        );
    
    fclose(file);
    
    return result;
}

bool
Security::Implementation::createPKCS12(
    std::string filePath
)
{
    PKCS12 * p12 = NULL;
    
    std::string n = input_("Name: ", false);
    
    std::string c = input_("Country: ", false);
    
    std::string cn = input_("Common name: ", false);
    
    if (!::createPKCS12(n, c, cn, input_, progress_, &p12)) { return false; }
    
    FILE * file = fopen(filePath.c_str(), "wb");

    if (!::writePKCS12(p12, file, progress_)) { return false; }
   
    fclose(file);
        
    return true;
}

bool
Security::Implementation::changePassword(
    std::string filePath
)
{
    FILE * file = fopen(filePath.c_str(), "rb");
    
    std::string oldPassword = input_("Old password: ", true);

    std::string newPassword = input_("New password: ", true);

    bool result = ::changePassword(file, oldPassword, newPassword, progress_);
    
    fclose(file);
    
    return result;
}

void
Security::Implementation::wipePrivateKey()
{
    memset(privateKey_, 0, sizeof(EVP_PKEY));

    privateKey_ = NULL;
}

#pragma recto Encryption/Decryption

void
Security::Implementation::encryptData(
    std::function<int (unsigned char *, int)> input,
    std::function<void (unsigned char *, int, unsigned char *, int)> header,
    std::function<void (unsigned char *, int)> data
)
{
    ::encryptData(getPublicKey(), input, header, data);
}

void
Security::Implementation::decryptData(
    unsigned int encryptedKeyLength,
    unsigned char * ek,
    unsigned char * iv,
    std::function<int (unsigned char *, int)> input,
    std::function<void (unsigned char *, int)> output
)
{
    ::decryptData(privateKey_, encryptedKeyLength, ek, iv, input, output);
}

#pragma recto CipherContext 

Security::CipherContext *
Security::Implementation::createCipherContext()
{
    EVP_CIPHER_CTX * ctx = new EVP_CIPHER_CTX;
    
    Security::CipherContext * cipherContext = new Security::CipherContext;
    
    // Sample the public key currently loaded in the security object and use to
    // create a context usable for encryption.
    
    ::initCipherContext(getPublicKey(), ctx, cipherContext);
    
    cipherContext->nativeHandle = ctx;
    
    return cipherContext;
}

#pragma recto Pointer Encryption

void *
Security::Implementation::encryptPointer(
    void * ptr,
    CipherContext ** cipherContext
)
{
    void * result = NULL;
    
    if (!*cipherContext) { *cipherContext = createCipherContext(); }
        
    EVP_CIPHER_CTX * ctx = nativeHandle(*cipherContext);
    
    // We want to encrypt a pointer and keep the size of the pointer without
    // risking to overwrite consecutive memory locations.
    
    // Since we want the encrypted pointer to be of the same size as the
    // plain text pointer, we use the GCM encryption mode.

    bool done = false;
    
    std::size_t len = sizeof(ScalarType);
    
    ::encryptData(ctx,
                    
        [ &ptr, &done, &len ] (unsigned char * plainBuffer, int maxSize) -> int {
            
            if (done) return 0;
            
            ScalarType value = (ScalarType)ptr;
            
            memcpy(plainBuffer, &value, len);
            
            done = true;
            
            return (int)len;
        },
                    
        [ &result, &len ] (unsigned char * cipherBuffer, int length) {
            
            ScalarType value = 0;

            memcpy(&value, cipherBuffer, len);

            result = (void *)value;

        }
                  
    );
    
    return result;
}

void *
Security::Implementation::decryptPointer(
    void * ptr,
    CipherContext * cipherContext
)
{
    void * result = NULL;
    
    bool done = false;
    
    std::size_t len = sizeof(ScalarType);

    ::decryptData(privateKey_,
        cipherContext->encryptedKeyLength,
        cipherContext->encryptedKey,
        cipherContext->iv,
                  
        [ &ptr, &done, &len ] (unsigned char * cipherBuffer, int maxSize) -> int {
            
            if (done) return 0;
            
            ScalarType value = (ScalarType)ptr;
            
            memcpy(cipherBuffer, &value, len);
            
            done = true;
            
            return (int)len;
        },
                  
        [ &result, &len ] (unsigned char * plainBuffer, int length) {
            
            ScalarType value = 0;
            
            memcpy(&value, plainBuffer, len);
            
            result = (void *)value;

        }
    );
    
    return result;
}

#pragma recto String Encryption/Decryption

void
Security::Implementation::encryptString(
    const std::string& plainText,
    bool ensureAppendPossible,
    CipherContext ** cipherContext,
    std::function<void (const std::string& block)> callback
)
{
    std::string innerPlainText = plainText;
    
    // Assure that plainText length is a multiple of three so that no padding
    // is included after Base64 encoding the content.
    
    if (ensureAppendPossible) {
        
        unsigned int modulus = innerPlainText.size() % 3;
        
        if (modulus) {

            int paddingLength = 3 - modulus;
            
            static std::mt19937_64 generator;
            
            uint64_t value = generator();
            
            for (int i = 0; i < paddingLength; i++) {
                
                innerPlainText += value & 1<<i ? '\t' : ' ';
                
            }

        }

    }

    if (!*cipherContext) { *cipherContext = createCipherContext(); }
    
    EVP_CIPHER_CTX * ctx = nativeHandle(*cipherContext);
    
    int first = 0;
    
    unsigned int count = 0;
    
    ::encryptData(ctx,
                  
        [ &first, &innerPlainText ]
        (unsigned char * plainBuffer, int maxSize) -> int {
        
            int last = (int)innerPlainText.size();
            
            if (first >= last) { return 0; }
            
            std::size_t rest = last - first;
            
            std::size_t len = std::min((int)rest, maxSize);
            
            innerPlainText.copy((char *)plainBuffer, len, first);
            
            first += len;
            
            return (int)len;
            
        },
                  
        [ &count, &callback ] (unsigned char * cipherBuffer, int length) {
            
#ifdef abc
            count = 0; // Note that the enabling of this assignment operation implies an increased probability of a breach with a particular percent. Elaborate.
#endif
            
            std::string part = Base64Encode((void *)cipherBuffer, length, &count);
            
            callback(part);
            
        }
                  
    );
}

void
Security::Implementation::decryptString(
    const std::string& cipherText,
    CipherContext * cipherContext,
    std::function<void (const std::string& block)> callback
)
{
    const void * ct;
    unsigned long ct_len;
    std::tie(ct, ct_len) = Base64Decode(cipherText);
    
    int firstByte = 0; std::string result = "";
    
    ::decryptData(privateKey_,
        cipherContext->encryptedKeyLength,
        cipherContext->encryptedKey,
        cipherContext->iv,
                      
        [ &firstByte, &ct, &ct_len ]
        (unsigned char * cipherBuffer, int maxSize) -> int {
                          
            if (firstByte < ct_len) {
                              
                std::size_t rest = ct_len - firstByte;
                              
                std::size_t len = std::min((int)rest, maxSize);
                    
                memcpy(cipherBuffer, ((unsigned char *)ct + firstByte), len);

                firstByte += len;
                              
                return (int)len;
            }
            
            return 0;
                          
        },
            
        [ &callback ] (unsigned char * plainBuffer, int length) {
            
            std::string block((char *)plainBuffer, length);
            
            callback(block);
            
        }
    );
    
   // free(ct);

}

#pragma recto Memory Overwrite Encryption

void
Security::Implementation::encrypt(
    unsigned char * ptr,
    uint64_t length,
    CipherContext ** cipherContext
)
{
    if (!*cipherContext) { *cipherContext = createCipherContext(); }
    
    EVP_CIPHER_CTX * ctx = nativeHandle(*cipherContext);
    
    // We want to encrypt a memory area and overwrite that memory area with
    // encrypted content. Since we want the encrypted content to be of the same
    // size as the plain text content, we use the GCM encryption mode.

    int eFirst = 0, dFirst = 0;
    
    auto overwrite =
        [ &ptr, &dFirst ]
        (unsigned char * cipherBuffer, int length) -> int {
        
            memcpy(ptr + dFirst, cipherBuffer, length);
        
            return length;

        };
    
    ::encryptData(ctx,
                  
        [ &ptr, &length, &eFirst ]
        (unsigned char * plainBuffer, int maxSize) -> int {
            
            if (eFirst >= length) { return 0; }
            
            std::size_t rest = length - eFirst;
            
            std::size_t len = std::min((int)rest, maxSize);
            
            memcpy(plainBuffer, ptr + eFirst, len);

            eFirst += len;
        
            return (int)len;
            
        },
                  
        [ &dFirst, &overwrite ] (unsigned char * cipherBuffer, int length) {
            
            dFirst += overwrite(cipherBuffer, length);
            
        }
                  
    );
}

void
Security::Implementation::decrypt(
    unsigned char * ptr,
    uint64_t length,
    CipherContext * cipherContext
)
{
    int dFirst = 0, eFirst = 0;
    
    ::decryptData(privateKey_,
        cipherContext->encryptedKeyLength,
        cipherContext->encryptedKey,
        cipherContext->iv,
                  
        [ &ptr, &length, &dFirst ]
        (unsigned char * cipherBuffer, int maxSize) -> int {
                
            if (dFirst >= length) { return 0; }
                
            std::size_t rest = length - dFirst;
                
            std::size_t len = std::min((int)rest, maxSize);
                
            memcpy(cipherBuffer, ptr + dFirst, len);
                
            dFirst += len;
                
            return (int)len;
                      
        },
                  
        [ &ptr, &eFirst ]
        (unsigned char * plainBuffer, int length) {
                
            if (eFirst >= length) { return 0; }
                
            std::size_t rest = length - eFirst;
                
            std::size_t len = std::min((int)rest, length);
                
            memcpy(ptr + eFirst, plainBuffer, len);
                
            eFirst += len;
                
            return (int)len;
                      
        }
    );
}

/*
#pragma recto Experimental OpenSSL S/MIME Encryption, Signing and Verification

void
Security::SecurityImp::signAndEncrypt(
    const std::string& plainTextFilePath,
    const std::string& cipherTextFilePath,
    const bool& compressBeforeEncryption
)
{
    X509     * recipient    = certificate_;
    EVP_PKEY * privSignKey  = privateKey_;
    X509     * pubSignKey   = certificate_;
    
    ::signAndEncrypt(privSignKey, recipient, pubSignKey,
        plainTextFilePath, cipherTextFilePath, progress_);
}

void
Security::SecurityImp::decryptAndVerify(
    const std::string& cipherTextFilePath,
    const std::string& plainTextFilePath,
    const bool& decompressAfterDecryption
)
{
    X509 * pubSignKey = certificate_;
    
    ::decryptAndVerify(privateKey_, certificate_, pubSignKey, certStore_,
        cipherTextFilePath, plainTextFilePath, progress_);
}
*/

#pragma recto Low-Level Signing and Validation

bool
Security::Implementation::sign(
    unsigned char * ptr,
    uint64_t bytes,
    unsigned char ** signature,
    unsigned int * signatureLength
) const
{
    return ::Sign(privateKey_, ptr, bytes, signature, signatureLength);
}

bool
Security::Implementation::validateSignature(
    unsigned char * message,
    int             messageLength,
    unsigned char * signature,
    int             signatureLength
) const
{
    return ::ValidateSignature(getPublicKey(), message, messageLength,
        signature, signatureLength);
}

#pragma recto Fingerprinting

std::string
Security::Implementation::getFingerprint() const
{
    return fingerprint_;
}

std::string
Security::Implementation::getCertificateAsPEM() const
{
    using BIO_MEM_ptr = std::unique_ptr<BIO, decltype(&::BIO_free)>;
    
    BIO_MEM_ptr bio(BIO_new(BIO_s_mem()), ::BIO_free);

    if (!PEM_write_bio_X509(bio.get(), certificate_)) {
        
        throw FundamentalError(
            "Unable to retrieve certificate when exporting as PEM"
        );

    }
    
    BUF_MEM * mem = NULL;
    BIO_get_mem_ptr(bio.get(), &mem);
    
    if (!mem || !mem->data || !mem->length) {
        
        throw FundamentalError(
            "Unable to convert certificate to a string"
        );
        
    }
    
    return std::string(mem->data, mem->length);
}

#pragma recto Administration (Note the sensitivity in this section)

void Security::Implementation::addRootCertificates()
{
    RootCertificates(
        [ this ]
        (const unsigned char * certData, int length, const char * name) {
            
            X509 * c = d2i_X509(NULL, &certData, length);
            
            if (!X509_STORE_add_cert(certStore_, c)) {
                
                progress_(
                    "Unable to add certificate '" + std::string(name) + "'"
                );
                
            }
        }
    );
}

void
Security::Implementation::addCertificate(
    unsigned char * data,
    int length
)
{
    BIO * mem = BIO_new_mem_buf(data, length);
    
    X509 * rootCertificate = NULL;
    PEM_read_bio_X509(mem, &rootCertificate, NULL, NULL);
    
    if (!X509_STORE_add_cert(certStore_, rootCertificate)) {
        
        progress_("Unable to add root certificate");
        
        goto err;
    }
    
err:
    
    ;
    
}

void
Security::Implementation::addCertificate(
    std::string filePath
)
{
    FILE * file = fopen(filePath.c_str(), "rb");
    
    X509 * rootCertificate = NULL;
    PEM_read_X509(file, &rootCertificate, NULL, NULL);
    
    if (!X509_STORE_add_cert(certStore_, rootCertificate)) {
        
        progress_("Unable to add root certificate '" + filePath + "'");
        
        goto err;
    }

err:
    
    ;
    
}

void
Security::Implementation::removeCertificate(
    unsigned int certSerial
)
{
    // OpenSSL doesn't support removal of certificates from a certificate
    // store. The library does however supports OCSP.
    // [See #include <openssl/ocsp.h>]
    
    // TODO: Think why.
}
    
#pragma recto SSL/TLS Web Server API
    
bool
Security::Implementation::verifyConnection(
    X509_STORE_CTX * context
)
{
    X509 * cert = X509_STORE_CTX_get_current_cert(context);
    
    char subjectName[256];
    X509_NAME_oneline(X509_get_subject_name(cert), subjectName, 256);
    
    std::cout << "Verifying " << subjectName << "\n";
    
    // TODO: Merge the stores in primary memory and validate.
    
    return true;
}
    
void
Security::Implementation::addCertchainAndKeyToContext(
    SSL_CTX * context
)
{
    // TODO: Note that we're adding all available root certs here for the
    // moment.
    
    SSL_CTX_set_cert_store(context, certStore_);

    if (::SSL_CTX_use_PrivateKey(context, privateKey_) != 1) {
        
        throw SecurityError("Unable to attach private key to SSL context");
        
    }
}

#pragma recto - C++ Outer Layer

Security::Security(
    bool allowSelfsignedIdentity,
    std::function<std::string (std::string, bool)> input,
    std::function<void (std::string)> progress
)
    :  implementation_ {
            new Implementation(allowSelfsignedIdentity, input, progress)
       }
{
}

Security::Security(
    bool allowSelfsignedIdentity,
    std::string certificateAsPEM,
    std::function<void (std::string)> progress
)
    :  implementation_ {
            new Implementation(allowSelfsignedIdentity,
                               certificateAsPEM, progress)
       }
{
}

Security::~Security()
{
}

#pragma recto PKCS#12

bool
Security::readPKCS12(
    std::string filePath,
    bool forDecryptionAndSigningAlso
)
{
    return implementation_->readPKCS12(filePath, forDecryptionAndSigningAlso);
}

bool
Security::createPKCS12(
    std::string filePath
)
{
    return implementation_->createPKCS12(filePath);
}

bool
Security::changePassword(
    std::string filePath
)
{
    return implementation_->changePassword(filePath);
}

void Security::wipePrivateKey() const
{
    implementation_->wipePrivateKey();
}

#pragma recto Buffer Encryption/Decryption

void
Security::encryptData(
    std::function<int (unsigned char *, int)> input,
    std::function<void (unsigned char *, int, unsigned char *, int)> header,
    std::function<void (unsigned char *, int)> data
)
{
    implementation_->encryptData(input, header, data);
}

void
Security::decryptData(
    uint32_t encryptedKeyLength,
    unsigned char * ek,
    unsigned char * iv,
    std::function<int (unsigned char *, int)> input,
    std::function<void (unsigned char *, int)> output
)
{
    implementation_->decryptData(encryptedKeyLength, ek, iv, input, output);
}

#pragma recto CipherContext Serialization/Deserialization

void
Security::CipherContext::serialize(
    std::ostream& os
)
{
    if (os.good()) {
        uint32_t keyLength = htonl(encryptedKeyLength);
        os.write((char *)&keyLength, sizeof(keyLength));
        os.write((char *)&encryptedKey, encryptedKeyLength);
        os.write((char *)&iv, maxIVLength);
    }
}

Security::CipherContext
Security::CipherContext::deserialize(
    std::istream& is
)
{
    CipherContext result;
    
    if (is.good()) {
        uint32_t keyLength;
        is.read((char *)&keyLength, sizeof(keyLength));
        result.encryptedKeyLength = ntohl(keyLength);
        is.read((char *)&result.encryptedKey, result.encryptedKeyLength);
        is.read((char *)&result.iv, result.maxIVLength);
        
        result.ivLength = getIVLength();
    }
    
    if (is.fail()) {
        
        throw std::runtime_error(
            "Deserialization of CipherContext failed"
        );
        
    }
    
    return result;
}

#pragma recto CipherContext

Security::CipherContext *
Security::createCipherContext() const
{
    return implementation_->createCipherContext();
}

void
Security::wipeCipherContext(
    Security::CipherContext * cipherContext
)
{
    ::wipeCipherContext(cipherContext);
}

#pragma recto Pointer Encryption

void *
Security::encryptVoidPointer(
    void * ptr,
    CipherContext ** cipherContext
)
{
    return implementation_->encryptPointer(ptr, cipherContext);
}

bool
Security::isValidPointer(
    void * encyptedPtr,
    CipherContext * cipherContext
)
{
    // Note that many operating systems have a particular way to mark that a
    // memory address is protected. The property can be used in reverse
    // so that user-space programs can flag an encrypted pointer as valid.
    
    // TODO: Implement according to discussion above.
    
    return true;
}

void *
Security::decryptVoidPointer(
    void * encryptedPtr,
    CipherContext * cipherContext
)
{
    if (isValidPointer(encryptedPtr, cipherContext)) {
        
        void * decryptedPtr =
            implementation_->decryptPointer(encryptedPtr, cipherContext);
        
        // TODO: Consider implications if adding signing to the encrypted
        // pointer.
        
        return decryptedPtr;
    }
    
    return NULL;
}

#pragma recto String Encryption/Decryption

void
Security::encryptString(
    const std::string& plainText,
    bool ensureAppendPossible,
    CipherContext ** cipherContext,
    std::function<void (const std::string& block)> callback
)
{
    implementation_->encryptString(plainText,
        ensureAppendPossible, cipherContext, callback);
}

void
Security::decryptString(
    const std::string& cipherText,
    CipherContext * cipherContext,
    std::function<void (const std::string& block)> callback
)
{
    implementation_->decryptString(cipherText, cipherContext, callback);
}

void
Security::encrypt(
    void * ptr,
    uint64_t bytes,
    CipherContext ** cipherContext
) const
{
    implementation_->encrypt((unsigned char *)ptr, bytes, cipherContext);
}

void
Security::decrypt(
    void * ptr,
    uint64_t bytes,
    CipherContext * cipherContext
) const
{
    implementation_->decrypt((unsigned char *)ptr, bytes, cipherContext);
}

#pragma recto Low-Level Signing and Validation

bool
Security::sign(
    void * data,
    uint64_t bytes,
    unsigned char ** signature,
    unsigned int * signatureLength
) const
{
    return implementation_->sign(
        (unsigned char *)data, bytes, signature, signatureLength
    );
}

bool
Security::validateSignature(
    void * data,
    uint64_t bytes,
    void * signature,
    uint64_t signatureLength
) const
{
    return implementation_->validateSignature(
        (unsigned char *)data, (int)bytes, (unsigned char *)signature,
                                           (int)signatureLength
    );
}

#pragma reto Fingerprinting

std::string
Security::getFingerprint() const
{
    return implementation_->getFingerprint();
}

std::string
Security::getCertificateAsPEM() const
{
    return implementation_->getCertificateAsPEM();
}

#pragma recto Certificate Store

void
Security::addCertificate(
    unsigned char * data,
    int length
)
{
    implementation_->addCertificate(data, length);
}

void
Security::addCertificate(
    std::string filePath
)
{
    implementation_->addCertificate(filePath);
}

#pragma recto SSL/TLS Web Server API (or Boost ASIO Credentials)

bool
Security::verifyConnection(
    void * context
)
{
    return implementation_->verifyConnection((X509_STORE_CTX *)context);
}

void
Security::applyIdentity(
    void * context
)
{
    implementation_->addCertchainAndKeyToContext((SSL_CTX *)context);
}

#pragma recto - SecurityError Exception Specialization

SecurityError::SecurityError(
    const std::string& description
)
    : FundamentalError(description)
{
}

#pragma recto - Enveloping

using Box = std::function<MemoryRegion (const MemoryRegion& in,
                                        const Security& security)>;

using Pipeline = std::vector<Box>;
    
static auto evaluate = [] (const MemoryRegion& in, const Pipeline& pipeline,
                           const Security& security) -> MemoryRegion {
    
    MemoryRegion tmp = in;
    
    for (auto& box : pipeline) { tmp = box(tmp, security); }
    
    return tmp;
    
};

std::string
Wrap(
    const Security& security, /*
    EVP_PKEY * privateSignKey,
    X509 * recipientPublicKey,
    X509 * publicSignKey, */
    MemoryRegion plainText,
    std::function<void (std::string)> progress
)
{
    auto signMemoryRegion = [] (const MemoryRegion& message,
                                const Security& security) -> MemoryRegion {
        
        unsigned char * s = NULL;
        unsigned int    l = 0;
        
        if (!security.sign(message.pointer(), message.length(), &s, &l)) {
            
            throw SecurityError("Unable to sign");
            
        }

        // Note that the function call above leads to a linked list that
        // may or may not be concaternated.
        
        uint32_t signatureLength = htonl(l);

        MemoryRegion signLen(&signatureLength, sizeof(signatureLength));

        MemoryRegion signature(s, l);
        
        MemoryRegion result = SecureConcaternation(signLen, signature, message,
            [] (uint64_t len) -> void * { return malloc(len); }
        );
       
        return result;
        
    };
    
    unsigned int currentWidth = 0;
    
    std::string fingerprint; // Fixed size of 40 8-bit characters.

    std::vector<Box> SMIMEEncryptionPipe = {
      
        [] (const MemoryRegion& in, const Security&) -> MemoryRegion {
 
            // Non-destructive editing (Remove semantically empty symbols.)
            // The inverse must have time complexity of O(1 + maxlen(dict)).
 
            return in;
 
        },

        [] (const MemoryRegion& in, const Security&) -> MemoryRegion {
 
            uint8_t * ptr; unsigned long len;
            
            std::tie(ptr, len) =
                Compress((uint8_t *)in.pointer(), in.length(),
                    [] (uint64_t compressedByteLength) -> void * {
                        
                        return (uint8_t *)malloc(compressedByteLength + 4) + 4;
                        
                    }
                );
            
            uint32_t uncompressLength = htonl((uint32_t)len);

            MemoryRegion result(ptr - 4, len + 4);
            
            *((uint32_t *)result.pointer()) = uncompressLength;
            
            return result;
            
        },
        
        [ &signMemoryRegion ] (const MemoryRegion& in,
                               const Security& security) -> MemoryRegion {
            
            return signMemoryRegion(in, security);                              // Private key must be in primary memory
        
        },
   
        [ &fingerprint ]
        (const MemoryRegion& in, const Security& security) -> MemoryRegion {
            
            Security::CipherContext * cipherContext =                           // Here we retrieve a reference to the encrypted private keys.
                security.createCipherContext();
            
            fingerprint = security.getFingerprint();

            security.encrypt(in.pointer(), in.length(), &cipherContext);
            
            // BEWARE: In OpenSSL, multiple keys can be used in the encryption
            // phase.

            return in;
            
        },
        
        [ &signMemoryRegion, &fingerprint ]
        (const MemoryRegion& in, const Security& security) -> MemoryRegion {
            
            MemoryRegion padding(NULL, 0);
            
            MemoryRegion fp((void *)fingerprint.c_str(), fingerprint.length());
            
            MemoryRegion out =
                SecureConcaternation(fp, padding, in,
                    [] (uint64_t len) -> void * { return malloc(len); }
                );

            return signMemoryRegion(out, security);                             // Private key can now be wiped from primary memory.
            
        },
        
        [ &currentWidth ]
        (const MemoryRegion& in, const Security&) -> MemoryRegion {
            
            unsigned long presumedNumberOfEncodedBytes =
                StringLengthIfBase64Encoded(in.length(), true);
            
            char * encoded = (char *)malloc(presumedNumberOfEncodedBytes);
            
            int actualNumberOfEncodedBytes = Base64Encode(encoded,
                in.pointer(), in.length(), &currentWidth
            );
                        
            return MemoryRegion(encoded, (uint64_t)currentWidth);
            
        }
    };

    MemoryRegion content = evaluate(plainText, SMIMEEncryptionPipe, security);
    
    std::string result((char *)content.pointer(), content.length());

    return result;
}

MemoryRegion
Unwrap(
    const Security& security, /*
    EVP_PKEY * recipentPrivateKey,
    X509 * recipientPublicKey,
    X509 * publicSignKey,
    X509_STORE * certStore, */
    MemoryRegion cipherText,
    std::function<void (std::string)> progress
)
{
    auto validateSignature =
        [] (const MemoryRegion& in, const Security& security,
            std::function<void ()> invalidCallback) -> MemoryRegion {
            
            // Validate signature for encrypted message.
            
            const int signatureByteSize = 4;
            
            if (in.length() < signatureByteSize)
                throw FundamentalError("No content to output");
            
            uint32_t signatureLength = ntohl(*((uint32_t *)in.pointer()));
            
            if (1024 <= signatureLength && signatureLength < 1024*8)
                throw FundamentalError("Invalid content");
            
            MemoryRegion signature((uint8_t *)in.pointer() + signatureByteSize,
                                   signatureLength);
            
            uint64_t messageLength = in.length() - signatureLength - 4;
            
            MemoryRegion message((uint8_t *)in.pointer() + 4 + signatureLength,
                                 messageLength);
            
            if (!security.validateSignature(
                 message.pointer(), message.length(),
                 signature.pointer(), signature.length())) {
                
                invalidCallback();
                
                throw FundamentalError("Invalid signature");
                
            }
            
            return message;
    };
    
    uint64_t upperBoundedBufferSize = cipherText.length();
    
    std::vector<Box> SMIMEDecryptionPipe = {
        
        [ &upperBoundedBufferSize ] (const MemoryRegion& in,
                         const Security& security) -> MemoryRegion {
            
            char * bufplain = (char *)malloc(upperBoundedBufferSize);
            
            // Beware of infinite loops.
            
            int bytesActuallyDecoded = Base64Decode(bufplain, in.pointer());
            
            return MemoryRegion(bufplain, bytesActuallyDecoded);
            
        },
        
        [ &validateSignature ]
        (const MemoryRegion& in, const Security& security) -> MemoryRegion {
            
            return validateSignature(in, security, [] () {                      // The following function call requires a public key.
                
                throw FundamentalError("Invalid signature");

            });
            
        },
        
        [ ] (const MemoryRegion& in, const Security& security) -> MemoryRegion {
            
            // The integrity of the fingerprint has been established and we're
            // ready to verify that the fingerprint is identical to the original
            // author.

            if (in.length() < 40) throw SecurityError("Fingerprint too short");
            
            // Retrieve the 40-character wide fingerprint and end prematurely
            // if the fingerprint is not identical to the stored fingerprint.

            MemoryRegion storedFingerprint(in.pointer(), 40);
            
            std::string currentFingerprint = security.getFingerprint();         // Here we're vulnerable to injection attack. This statement and the next one should reside in HW.
            
            if (memcmp(storedFingerprint.pointer(),
                       currentFingerprint.c_str(), 40)) {
                
                throw SecurityError("Authorization failure");
                
            }
            
            MemoryRegion content((uint8_t*)in.pointer() + 40, in.length() - 40);
            
            if (content.length() == 0) throw SecurityError("No content");

            Security::CipherContext * cipherContext =                           // The following function call should require a private key.
                security.createCipherContext();
            
            security.decrypt(in.pointer(), in.length(), cipherContext);
            
            return in;

        },
                
        [ &validateSignature ]
        (const MemoryRegion& in, const Security& security) -> MemoryRegion {
             
             // Validate message for decrypted message
             
            return validateSignature(in, security, [ &in ] () {                 // The following function call requires a public key.
                 
                 SecureOverwrite(in);
                 
                 throw FundamentalError("Invalid signature");
                 
             });

        },
                 
        [ ] (const MemoryRegion& in, const Security&) -> MemoryRegion {
            
            const int lengthByteSize = 4;

            if (in.length() < lengthByteSize)
                throw FundamentalError("No content to uncompress");

            MemoryRegion lengthBlock(in.pointer(), 4);
            
            uint32_t length = ntohl(*((uint32_t *)in.pointer()));
            
            // We limit ourselves to 512 MB for the moment since we're
            // keeping the length of the uncompressed data in a 32 bit
            // unsigned integer.
            
            if (length >= 1024*1024*512)
                throw FundamentalError("Invalid content");

            MemoryRegion message((uint8_t *)in.pointer() + 4, in.length() - 4);

            uint8_t * data =
                Decompress((uint8_t *)in.pointer(), in.length(), length);
            
            return MemoryRegion(data, length);
        }

    };
    
    MemoryRegion result = evaluate(cipherText, SMIMEDecryptionPipe, security);
    
    return result;
    
}

void
AppendWrap(
    const Security& security,
    const MappedFile& mappedFile,
    void ** head,
    std::string plainText,
    std::function<void (std::string)> progress
)
{
    mappedFile.explore(*head, (uint64_t)plainText.length());
    
    MemoryRegion memoryRegion((void *)plainText.c_str(),
                              (uint64_t)plainText.length());
    
    std::string cipherText = Wrap(security, memoryRegion, progress);
    
    std::string::size_type length = cipherText.length();
    
    memcpy(*head, cipherText.c_str(), length);
    
    *head = (void *)((uint8_t *)(*head) + length);
    
    mappedFile.sync();
}

