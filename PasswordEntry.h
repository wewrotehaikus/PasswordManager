#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H

#include <string>

class PasswordEntry {
public:
    // Constructor
    PasswordEntry (const std::string& title,
                   const std::string& username,
                   const std::string& password,
                   const std::string& url,
                   const std::string& notes);

    // Getters
    std::string getTitle()     const;
    std::string getUsername()  const;
    std::string getPassword()  const;
    std::string getUrl()       const;
    std::string getNotes()     const;

    // Setters
    void setTitle(const std::string& title);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setUrl(const std::string& url);
    void setNotes(const std::string& notes);

private:
    std::string m_title;
    std::string m_username;
    std::string m_password;
    std::string m_url;
    std::string m_notes;
};

#endif // PASSWORDENTRY_H
