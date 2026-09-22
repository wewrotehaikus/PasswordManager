#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QString>

class LoginWindow : public QMainWindow {
    Q_OBJECT // MOC processes this

public:
    LoginWindow();    

private:
    QPushButton *loginButton; // Need these declarations
    QLineEdit *passwordField; // So we can use them in .cpp

private slots: // the correct keyword for Qt slots
    void onLoginButtonClicked(); // This calls vault.unlock()
};

#endif // LOGINWINDOW_H
