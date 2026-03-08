#include "PasswordEntry.h"

// Constructor
PasswordEntry::PasswordEntry(const std::string& title,
                             const std::string& username,
                             const std::string& password,
                             const std::string& url,
                             const std::string& notes)
    : m_title(title),
      m_username(username),
      m_password(password),
      m_url(url),
      m_notes(notes)
{}

//Getters
std::string PasswordEntry::getTitle()    const { return m_title; }
std::string PasswordEntry::getUsername() const { return m_username;}
std::string PasswordEntry::getPassword() const { return m_password; }
std::string PasswordEntry::getUrl()      const { return m_url; }
std::string PasswordEntry::getNotes()    const { return m_notes; }

//Setters
void PasswordEntry::setTitle(const std::string& title)       { m_title = title; }
void PasswordEntry::setUsername(const std::string& username) { m_username = username; }
void PasswordEntry::setPassword(const std::string& password) { m_password = password; }
void PasswordEntry::setUrl(const std::string& url)           { m_url = url; }
void PasswordEntry::setNotes(const std::string& notes)       { m_notes = notes; }
