#include <iostream>
#include "Vault.h"
#include "Crypto.h"

/*int main() {
    PasswordEntry entry ("Gmail",
                         "john@example.com",
                         "supersecret123",
                         "https://gmail.com",
                         "Personal email");

    std::cout << "Title:     " << entry.getTitle()     << std::endl;
    std::cout << "Username:  " << entry.getUsername()  << std::endl;
    std::cout << "Password:  " << entry.getPassword()  << std::endl;
    std::cout << "URL:       " << entry.getUrl()       << std::endl;
    std::cout << "Notes:     " << entry.getNotes()     << std::endl;

    return 0;
}
*/

int main(){
    // Initialize libsodium first
        if (!Crypto::initialize())
    {
        std::cerr << "Failed to initialize libsodium\n";
        return 1;
    }

    //Create a Vault with a master password
    Vault vault("myMasterPassword123");

    //Add some entries
    vault.addEntry(PasswordEntry("Gmail", "john@gmail.com", "pass123", "https://gmail.com", "Personal"));
    vault.addEntry(PasswordEntry("GitHub", "john_dev", "devpass456", "https://github.com", "Work account"));
    vault.addEntry(PasswordEntry("Netflix", "john@gmail.com", "netflixpass", "https://netflix.com", ""));

    //Print entry count
    std::cout << "Total entries: " << vault.entryCount() << std::endl;

    //Retrieves and prints a specific entry
    PasswordEntry e = vault.getEntry(1);
    std::cout << "\nEntry at index 1:" << std::endl;
    std::cout << "  Title:     " << e.getTitle()    <<std::endl;
    std::cout << "  Username:  " << e.getUsername() <<std::endl;

    // Test Search
    std::vector<PasswordEntry> results = vault.search("john@gmail.com");
    std::cout << "\nSearch results for 'john@gmail.com': "
              << results.size() << " found" << std::endl;
    for (const PasswordEntry& r : results) {
        std::cout << "  - " << r.getTitle() << std::endl;
    }

    // Test Lock
    vault.lock();
    std::cout << "\nVault locked. Trying to add entry..." << std::endl;
    vault.addEntry(PasswordEntry("Spotify", "john", "spot123", "", ""));
    std::cout << "Total entries after attempted add: " << vault.entryCount() << std::endl;

    // Test encryption/decryption
std::string originalPassword = "MySecretPassword123!";
std::string masterPassword = "MasterPassphrase";

auto encrypted = Crypto::encrypt(originalPassword, masterPassword);
std::cout << "\nEncrypted data size: " << encrypted.size() << " bytes\n";

std::string decrypted = Crypto::decrypt(encrypted, masterPassword);
std::cout << "Original:  " << originalPassword << "\n";
std::cout << "Decrypted: " << decrypted << "\n";
std::cout << "Match: " << (originalPassword == decrypted ? "✓ YES" : "✗ NO") << "\n";

    return 0;
}
