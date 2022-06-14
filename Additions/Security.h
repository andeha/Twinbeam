//
//  Security.h
//  Helixstore
//
//  Created  on 28/10/15.
//

#ifndef __SECURITY_H_
#define __SECURITY_H_

#include <FEFoundation/Attributes.h>
#include <FEFoundation/MemoryRegion.h>
#include <FEFoundation/MappedFile.h>
#include <FEFoundation/FundamentalError.h>
#include <string>
#include <functional>

/** 
 
    The @c Security class handles tasks related to identity management,
    pointer/string/memory block encryption/decryption, S/MIME management,
    signing/validation, fingerprinting, SSL web server private key/certificate
	handling, and SSL request authentication.
 
    The default behaviour is that a PKCS#12 identity file is assumed to be 
    located on a USB stick plugged into the computer.
 
    Run-time errors results in @c SecurityError exceptions.
 
    This source module also contains Base64 encoding/decoding functions.
    (Base32 encoding/decoding is available in @c FEFoundation/System.h)
 
    When created, an instance of the @c Security class is loaded with the root
    certificates preloaded inside the host operating system.
 
    Note that on Mac OS X, even if we import a new CA root certificate via
    @c Keychain.app, we still has to manually flip the newly imported 
    certificates' trust switch. If we add the certificate using one of the two 
    @c addCertificate API's, we can validate sub certificates without forcing 
    the user to interact with the keychain application.
 
    All encryption and decryption routines may throw a @c SecurityException 
    in-case something goes wrong.

 */

class Security {
public:
    
#pragma recto Constructors and Destructors 
    
    /**

        Creates a new @c Security object optionally allowing self-signed
        certificates.
        
        @param allowSelfsignedIdentity If set to true, this instance allows 
            parsing of non-rooted certificates.
     
        @param input Lambda function called when the class needs input from
            a human.
     
        @param progress Lambda function that is called when an instance of the 
            class outputs progress.
     
     */
    
    ALWAYS_INLINE
    Security(
        bool allowSelfsignedIdentity,
        std::function<std::string (std::string prompt, bool secure)> input,
        std::function<void (std::string msg)> progress
    );
    
    /**
     
        Constructor useful when creating a @c Security object for 
        encryption-only.
     
        @param allowSelfsignedIdentity Allow the certificate to be non-rooted. 
     
        @param certificateAsPEM A string containing a certificate in PEM.
     
     */
    
    ALWAYS_INLINE
    Security(
        bool allowSelfsignedIdentity,
        std::string certificateAsPEM,
        std::function<void (std::string)> progress
    );
    
    ALWAYS_INLINE
    ~Security();
    
#pragma recto PKCS#12
    
    /**
     
        File path to @c .p12 file on removable media (USB stick).
    
     */
    
    static
    constexpr auto defaultIdentityFilePath = "/Volumes/HELIXID/Identity.p12";
    
    /**
     
        Parses a PKCS#12 file and throw an @c SecurityException in case an
        error occurs.
     
        This function call may throw a @c SecurityError if:
     
        - The PKCS#12 file can not be parsed.
     
        - Does not contain a private key and a certificate.
        
        @param filePath Optional path to the PKCS#12 file containing the
            asymmetric key-pair that is the identity.
     
        @param forDecryptionAndSigningAlso Reserved for future use.
     
        @return false if the operation succeeded, true if the operation failed.
     
     */
    
    ALWAYS_INLINE
    bool
    readPKCS12(
        std::string filePath = defaultIdentityFilePath,
        // Note that disabling the following switch currently breaks the
        // reading procedure since the PKCS#12 files created by openssl stores
        // the public key and the certificate chain inside a shrouded bag (an
        // encrypted bag).
        bool forDecryptionAndSigningAlso = true
    );
    
    /**
     
        Interactively creates a new PKCS#12 file and saves the file in
        non-volatile memory.
        
        @param filePath The path to the newly created file. 
     
        @return false if the operation succeeded, true if the operation failed.

     */
    
    ALWAYS_INLINE
    bool
    createPKCS12(
        std::string filePath
    );
    
    /**
     
        Changes the passphrase on a previously created PKCS#12 file.
     
        @param filePath The file path to the PKCS#12 file to alter.
     
        @return false if the operation succeeded, true if the operation failed.
     
     */

    ALWAYS_INLINE
    bool
    changePassword(
        std::string filePath
    );
    
    /**
     
        Remove private keys from primary memory. Consider the implications of 
        the following API.
     
     */
    
    ALWAYS_INLINE void wipePrivateKey() const;
        
#pragma recto Buffer Encryption/Decryption
    
    /**
     
        Encrypts content in memory buffer with the encryption parameters 
        returned via the lambda function given in header.
     
        @param input Lambda function that is called when the encryption routine
            needs plain text. 
     
        @param header Lambda function that is called when encryption starts. 
     
        @pararm data Lambda function that is called multiple times when 
            encrypting content.
     
        Encryption ends when the input lambda returns 0.
     
     */
    
    ALWAYS_INLINE
    void
    encryptData(
        std::function<int (unsigned char * plainBuffer, int maxSize)> input,
        std::function<void (unsigned char * encryptedKey,
            int encryptedKeyLength, unsigned char * iv, int ivLength)> header,
        std::function<void (unsigned char * cipherBuffer, int length)> data
    );
    
    /**
     
        Decrypts content stored in a memory buffer using an encrypted symmetric
        key and an initialization vector. 
     
        @param encryptedeyLength The length of the asymmetrical encrypted 
            symmetric key.
     
        @param ek The asymmetrical encrypted symmetric key. 
     
        @param iv Initialization vector having a fixed 16 bytes. 
     
        @param input Lambda function that called when the decryption routine
            needs cipher text. 
     
        @param output Lambda function that contains the plain text. 
     
     */
    
    ALWAYS_INLINE
    void
    decryptData(
        unsigned int encryptedKeyLength,
        unsigned char * ek,
        unsigned char * iv,
        std::function<int (unsigned char * cipherBuffer, int maxSize)> input,
        std::function<void (unsigned char * plainBuffer, int length)> output
    );
    
#pragma recto Cipher Context
    
    /**
     
        The @c CipherContext structure contains the initial values neccessary 
        to decrypt content and an opaque pointer to something we do not have to
        reverse engineer.
     
     */
     
    struct CipherContext {
        
        static const int maxIVLength = 16;

        unsigned char * encryptedKey;
        int             encryptedKeyLength;
        unsigned char   iv[maxIVLength];
        int             ivLength;
        void *          nativeHandle;
        
        /**
         
            Store a @c CipherContext into a stream.
         
         */
        
        void serialize(std::ostream& os);
        
        /**
         
            Recreates a @c CipherContext from a previously serialized
            stream. 
         
         */
        
        static CipherContext deserialize(std::istream& is);
    
    };
    
    /**
     
        Creates a new cipher context or throws a @c SecurityException in case
        something goes wrong.
     
     */
    
    ALWAYS_INLINE CipherContext * createCipherContext() const;
    
    /**
     
        Deallocates a cipher context previously allocated with 
        createCipherContext.
     
     */
    
    ALWAYS_INLINE
    void
    wipeCipherContext(
        CipherContext * cipherContext
    );
    
#pragma recto Pointer Encryption
    
    /** 
     
        Encrypts a pointer while retaining the type of the pointer using a new 
        or previously created @c cipherContext.
     
        @param ptr The pointer to encrypt.
     
        @param cipherContext The inital values neccessary for encryption.
     
        @return An encrypted pointer of the same size as the plain text pointer.
     
        If @c *cipherContext points to NULL, a new @c cipherContext is created
        otherwise the pointer is assumed to point to a valid @c CipherContext.

     */
    
    template <typename T>
    ALWAYS_INLINE
    T *
    encryptPointer(
        T * ptr,
        CipherContext ** cipherContext
    );
  
    /**
     
        Decrypts a pointer while retaining the type of the pointer using a
        previously created @c cipherContext.
     
        @param encryptedPtr The previously encrypted pointer.
     
        @param cipherContext The inital values neccessary for decryption.
     
        @return A plain text pointer.
     
     */
    
    template <typename T>
    ALWAYS_INLINE
    T *
    decryptPointer(
        T * encryptedPtr,
        CipherContext * cipherContext
    );

#pragma recto String Encryption/Decryption

    /**
     
        Encrypt and Base-64 encode a string using a new or previously created
        @c cipherContext. If @c ensureAppendPossible is set to true, the
        resulting encoded cipherText can be used as a prefix to later 
        encryptions.

        @param plainText The plain text string to encrypt and encode.
     
        @param ensureAppendPossible Pad with a random plain-text whitespace 
            padding.
     
        @param cipherContext The initial values neccessary for decryption.
     
        @param callback Callback called when a block been encrypted and encoded.
     
        @return encrypted and encoded text string.
     
        If @c *cipherContext points to @c NULL, a new @c cipherContext is 
        created otherwise the pointer is assumed to point to a valid 
        @c CipherContext.
     
     */
    
    ALWAYS_INLINE
    void
    encryptString(
        const std::string& plainText,
        bool ensureAppendPossible,
        CipherContext ** cipherContext,
        std::function<void (const std::string& block)> callback
    );
    
    /**
     
        Base-64 decode and decrypt a string using a previously created
        @c cipherContext.
     
        @param cipherText The cipher text to decode and decrypt.
     
        @param cipherContext The initial values neccessary for decryption.
     
        @param callback Callback called when block been decoded and decrypted.
     
        @return decoded and decrypted text string.
     
     */
    
    ALWAYS_INLINE
    void
    decryptString(
        const std::string& cipherText,
        CipherContext * cipherContext,
        std::function<void (const std::string& block)> callback
    );
    
#pragma recto Memory Overwrite Encryption
    
    /** 
     
        Encrypts a primary memory region while simultaneously overwrite the
        plain text.
     
        @param ptr Pointer to a plain text memory block to encrypt.
     
        @param bytes The number of bytes to encrypt. 
     
        @param cipherContext The initial values neccessary for encryption.
     
        If @c *cipherContext points to @c NULL, a new @c cipherContext is 
        created otherwise the pointer is assumed to point to a valid 
        @c CipherContext.

     */
    
    ALWAYS_INLINE
    void
    encrypt(
        void * ptr,
        uint64_t bytes,
        CipherContext ** cipherContext
    ) const;
    
    /**
     
        Decrypts a primary memory region.
     
        @param ptr Pointer to a cipher text memory block to decrypt. 
     
        @param bytes The number of bytes to decrypt.
     
        @param cipherContext The initial values neccessary for decryption.
     
     */
    
    ALWAYS_INLINE
    void
    decrypt(
        void * ptr,
        uint64_t bytes,
        CipherContext * cipherContext
    ) const;

#pragma recto Low-Level Signing and Validation
    
    /**
     
        Traverse the bytes in data and outputs a cryptographically valid 
        signature.
     
        @param data Pointer to the bytes to sign. 
     
        @param bytes The number of bytes following the data pointer to visit.
     
        @param signature Pointer to a memory block allocated by the function
            that holds the resulting signature.
     
        @param signatureLength The number of bytes following the signature 
            pointer that has been allocated to hold the signature.
     
        @return false if the operation succeeded, true if the operation failed.

     */
    
    ALWAYS_INLINE
    bool
    sign(
        void * data,
        uint64_t bytes,
        unsigned char ** signature,
        unsigned int * signatureLength
    ) const;
    
    /**
     
        Traverse the bytes in data and validates that signature is 
        cryptographically correct.
     
        @param data Pointer to the bytes to validate.
     
        @param bytes The number of bytes following the data pointer to visit 
            when validating the signature. 
     
        @param signature Pointer to a memory block that holds the signature. 
     
        @param signatureLength The number of bytes following the signature 
            pointer that holds the signature.
     
        @return false if the operation succeeded, true if the operation failed.

     */
    
    ALWAYS_INLINE
    bool
    validateSignature(
        void * data,
        uint64_t bytes,
        void * signature,
        uint64_t signatureLength
    ) const;
    
#pragma recto Fingerprinting
    
    /**
     
        Return a presumable non-reversable hash value from the public key.
        
     
        @return A Base-64 encoded string that allows us to compare public keys.
     
     */
    
    ALWAYS_INLINE std::string getFingerprint() const;
    
    /**
     
        Return the current public key as a string containing a portable PEM
        file.
    
     */
    
    ALWAYS_INLINE std::string getCertificateAsPEM() const;
    
#pragma recto Certificate Store
    
    /**
     
        Adds a PEM-formatted certificate stored in primary memory to the
        certificate store.
     
        @param data Pointer to a PEM formatted certificate. 
     
        @param length The length of the certificate. 
     
     */
    
    ALWAYS_INLINE
    void
    addCertificate(
        unsigned char * data,
        int length
    );
   
    /**
     
        Adds a PEM-formatted certificate stored in a file to the certificate 
        store.
     
        @param filePath File path to a .pem file.
     
     */
    
    ALWAYS_INLINE
    void
    addCertificate(
        std::string filePath
    );
    
    /**
     
        Removes a certificate from the certificate store. Neccesary for OCSP 
        when a certificate appears to be revoked.
     
     */
    
    ALWAYS_INLINE
    void
    removeCertificate(
        unsigned int certSerial
    );
    
#pragma recto SSL/TLS Web Server and Client API (also Boost ASIO credentials)
    
    /**
     
        Validates the certificate chain in an OpenSSL SSL context or an ASIO SSL
        context. Useful when building an SSL client.
     
        @param context A opaque pointer (to a X509_STORE_CTX).
     
        @return false if the operation succeeded, true if the operation failed.
     
     */
    
    ALWAYS_INLINE
    bool
    verifyConnection(
        void * context
    );
    
    /**
     
        Updates a @c boost::asio::ssl::context or an OpenSSL SSL context with a
        certificate chain and a private key. Useful when building an SSL server.
     
        @param context A opaque pointer (to a SSL_CTX).
     
        If the function is unable to attach a private key to the context, a 
        SecurityError is thrown.
     
     */
    
    ALWAYS_INLINE
    void
    applyIdentity(
        void * context
    );
    
#pragma recto - Convenient Encapsulation before Creating a Security Instance.
    
    /**
     
        The context struct encapsulates the information neccessary for 
        creating a @c Security object.
     
     */
    
    struct Context {
        std::string pkcs12FilePath;
        bool allowSelfsignedIdentity;
        std::string password;
    };
    
private:
    
    ALWAYS_INLINE
    void *
    encryptVoidPointer(
        void * ptr,
        CipherContext ** cipherContext
    );

    ALWAYS_INLINE
    bool
    isValidPointer(
        void * encyptedPtr,
        CipherContext * cipherContext
    );
    
    ALWAYS_INLINE
    void *
    decryptVoidPointer(
        void * ptr,
        CipherContext * cipherContext
    );

    class Implementation;
    
    const std::unique_ptr<Implementation> implementation_;
    
};

#pragma recto - SHA1 Fingerprinting

/**
 
    SHA1 Fingerprinting a block of data. 
 
    @param ptr Pointer to the memory block to fingerprint. 
 
    @parma bytes The nubmer of bytes following the pointer the fingerprint 
        should be based on. 
 
    @return The SHA-1 fingerprint. 
 
 */

ALWAYS_INLINE
std::string
sha1(
     void * ptr,
     unsigned int bytes
);

#pragma recto - Template-Based Typesafe Pointer Encryption/Decryption

template <typename T>
ALWAYS_INLINE
T *
Security::encryptPointer(
    T * ptr,
    CipherContext ** cipherContext
)
{
    return (T *)encryptVoidPointer(ptr, cipherContext);
}

template <typename T>
ALWAYS_INLINE
T *
Security::decryptPointer(
    T * encryptedPtr,
    CipherContext * cipherContext
)
{
    return (T *)decryptVoidPointer(encryptedPtr, cipherContext);
}

#pragma recto - SecurityError Exception Specialization

class SecurityError : public FundamentalError {
public:
    
    SecurityError(
        const std::string& description
    );
    
};

#pragma recto - Enveloping and Temporal Flow

/*
 
    The following routines performs something similar to S/MIME file wrapping/
    unwrapping.
 
    According to rfc3851, It is up to the implementation and the user to
    choose the order. When signing first, the signatories are then securely
    obscured by the enveloping. When enveloping first the signatories are
    exposed (at least the signatories fingerprint), but it is possible to
    verify signatures without removing the enveloping.
 
    Further, a recipient of a message that is encrypted and then signed can
    validate that the encrypted block was unaltered, but cannot determine
    any relationship between the signer and the unencrypted contents of the
    message.  A recipient of a message that is signed-then-encrypted can
    assume that the signed message itself has not been altered, but that a
    careful attacker could have changed the unauthenticated portions of the
    encrypted message.
 
 */

/**
 
    Helper function that wraps content onto a string.
 
    @param security A reference to a @c Security object.
 
    @param plainText The plain-text content to @c Wrap.
 
    @param progress Callback that may report progress.

    @return A string containing Base-64 encoded ciphered content and a 
        signature.
 
 */

ALWAYS_INLINE
std::string
Wrap(
    const Security& security,
    MemoryRegion plainText,
    std::function<void (std::string)> progress
);

/**
    
    Helper function that unwraps content stored in a memory region and 
    retrieves an alternative
 
    @param security A reference to a @c Security object.
 
    @param cipherText A @c MemoryRegion containing the unwrapped content.
 
    @param progress Callback that may report progress.
 
    @return A @c MemoryRegion containing the unwrapped content.

 */

ALWAYS_INLINE
MemoryRegion
Unwrap(
    const Security& security,
    MemoryRegion cipherText,
    std::function<void (std::string)> progress
);

/**
 
    Adds a block of plain text to a mapped file. 
 
    @param security A reference to a @c Security object.

    @param mappedFile Underlying file used to persist content.
 
    @param head The first non-occupied location.

    @param plainText The plain text to add.
 
    @param progress Callback that may report progress.

 */

ALWAYS_INLINE
void
AppendWrap(
    const Security& security,
    const MappedFile& mappedFile,
    void ** head,
    std::string plainText,
    std::function<void (std::string)> progress
);

#endif
