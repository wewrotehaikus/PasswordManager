#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <vector>
#include <sodium.h>

class Crypto
{
public:
    // Must be called once at program startup
    static bool initialize();

    // Hashes a password for storage/comparison
    static std::string hashPassword(const std::string &password);

    // Verifies a password against a stored hash
    static bool verifyPassword(const std::string &password,
                               const std::string &hash);

    // Encrypts plaintext data, returns ciphertext
    static std::vector<unsigned char> encrypt(const std::string &plaintext,
                                              const std::string &password);

    // Decrypts ciphertext data, returns plaintext
    static std::string decrypt(const std::vector<unsigned char> &ciphertext,
                               const std::string &password);

private:
    // Derives an encryption key from a password and salt
    static bool deriveKey(const std::string &password,
                          const unsigned char *salt,
                          unsigned char *key);
};
#endif // CRYPTO_H