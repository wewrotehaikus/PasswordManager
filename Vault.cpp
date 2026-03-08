#include "Vault.h"
#include <stdexcept>

// Constructor
Vault::Vault (const std::string& masterPassword)
    : m_masterPassword(masterPassword),
      m_locked(false)

{}

// Entry management
void Vault::addEntry(const PasswordEntry& entry){
    if (m_locked) return;
    m_entries.push_back(entry);
}

void Vault::removeEntry(int index) {
    if (m_locked) return;
    if (index < 0 || index >=(int)m_entries.size())
        throw std::out_of_range("Invalid entry index");
    m_entries.erase(m_entries.begin() + index);
}

PasswordEntry Vault::getEntry(int index) const {
    if (index < 0 || index >= (int)m_entries.size())
        throw std::out_of_range("Invalid entry index");
    return m_entries[index];
}

int Vault::entryCount() const {
    return (int)m_entries.size();
}

// Search
std::vector<PasswordEntry> Vault::search(const std::string& query) const {
    std::vector<PasswordEntry> results;
    for(const PasswordEntry& entry : m_entries) {
        if (entry.getTitle().find(query) != std::string::npos ||
            entry.getUsername().find(query) != std::string::npos) {
            results.push_back(entry);
        }
    }
    return results;
}

// Lock & Unlock
bool Vault::unlock(const std::string& masterPassword) {
    if (masterPassword == m_masterPassword) {
        m_locked = false;
        return true;
    }
    return false;
}

void Vault::lock() {
    m_locked = true;
}

bool Vault::isLocked() const {
    return m_locked;
}
