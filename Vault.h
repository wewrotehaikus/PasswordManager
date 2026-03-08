#ifndef VAULT_H
#define VAULT_H

#include <string>
#include <vector>
#include "PasswordEntry.h"


class Vault {
public:
    //Constructor
    Vault(const std::string& masterPassword);

    // Entry Management
    void addEntry(const PasswordEntry& entry);
    void removeEntry(int index);
    PasswordEntry getEntry(int index) const;
    int entryCount() const;

    //Search
    std::vector<PasswordEntry> search(const std::string& query) const;

    //Lock/Unlock
    bool unlock (const std::string& masterPassword);
    void lock();
    bool isLocked() const;

private:
    std::vector<PasswordEntry> m_entries;
    std::string m_masterPassword;
    bool m_locked;

};

#endif // VAULT_H
