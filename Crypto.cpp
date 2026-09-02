#include <iostream>
#include "Crypto.h"
#include <stdexcept>
#include <sodium.h>

// libsodium constants for password hashing
// these control how "expensive" the hash is (memory& & time)
// higher == more secure but slower
static constexpr unsigned long long OPSLIMIT = crypto_pwhash_argon2i_OPSLIMIT_MODERATE;
static constexpr size_t MEMLIMIT = crypto_pwhash_argon2i_MEMLIMIT_MODERATE;

bool Crypto::initialize()
{
    //sodium_init() returns 0 when succhessful, -1 on failure, or if already initizialized
    // we're only looking that its not a fatal error
    int result = sodium_init();
    return result != -1;
}

std::string Crypto::hashPassword(const std::string &password)
{
    //allocate space for the hash
    char hash[crypto_pwhash_argon2i_STRBYTES];

    //Hash the psw with argon 2i
    //parameters: hash buffer, password, password length, opslimit, memlimit, algorithm
    int result = crypto_pwhash_argon2i_str(
        hash,
        password.c_str(),
        password.length(),
        OPSLIMIT,
        MEMLIMIT
    );

    if (result != 0) {
        throw std::runtime_error("Failed to hash password");
    }

    //return the hash as a C++ string
    return std::string(hash);
}

bool Crypto::verifyPassword(const std::string &password,
                            const std::string &hash)
{
    // Use constant-time comparison to prevent timing attacks
    // Returns 0 if password matches the hash, -1 otherwise
    int result = crypto_pwhash_argon2i_str_verify(
        hash.c_str(),
        password.c_str(),
        password.length()
    );

    return result == 0;
}

bool Crypto::deriveKey(const std::string &password,
                       const unsigned char *salt,
                       unsigned char *key)
{
    // Derive a 32-byte key using Argon2i
    // Parameters: key buffer, key size (32 bytes), password, password length, salt, opslimit, memlimit, algorithm
    int result = crypto_pwhash_argon2i(
        key,
        crypto_secretbox_KEYBYTES,
        password.c_str(),
        password.length(),
        salt,
        OPSLIMIT,
        MEMLIMIT,
        crypto_pwhash_ALG_DEFAULT  
    );

    return result == 0;
}

std::vector<unsigned char> Crypto::encrypt (const std::string& plaintext,
                                            const std::string& password)
{
    // Generate random salt (16 bytes)
    unsigned char salt[crypto_pwhash_SALTBYTES];
    randombytes_buf(salt, crypto_pwhash_SALTBYTES);
    // Derive the encryption key from password + salt
    unsigned char key [crypto_secretbox_KEYBYTES];
    deriveKey(password, salt, key);
    //Generate random nonce (24bytes)
    unsigned char nonce [crypto_secretbox_NONCEBYTES];
    randombytes_buf(nonce, crypto_secretbox_NONCEBYTES);
    //Encrypt the plaintext
    // Ciphertext will be plaintext length + 16 bytes for auth tag
    std::vector<unsigned char> ciphertext(plaintext.length() + crypto_secretbox_MACBYTES);
    crypto_secretbox_easy(ciphertext.data(),
                      reinterpret_cast<const unsigned char*>(plaintext.c_str()),
                      plaintext.length(),
                      nonce,
                      key);
// Pack: [salt (16 bytes)][nonce (24 bytes)][ciphertext]
std::vector<unsigned char> result;
result.reserve(crypto_pwhash_SALTBYTES + crypto_secretbox_NONCEBYTES + ciphertext.size());

result.insert(result.end(), salt, salt + crypto_pwhash_SALTBYTES);
result.insert(result.end(), nonce, nonce + crypto_secretbox_NONCEBYTES);
result.insert(result.end(), ciphertext.begin(), ciphertext.end());

return result;
}


