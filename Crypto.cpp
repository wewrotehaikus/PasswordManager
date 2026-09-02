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