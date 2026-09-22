#include <iostream>
#include "LoginWindow.h"
#include "Vault.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>


LoginWindow::LoginWindow() : QMainWindow() {
    // Create central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Create layout
    QVBoxLayout *layout = new QVBoxLayout();
    
    // Create widgets
    QLabel *titleLabel = new QLabel("Password Manager Login");
    passwordField = new QLineEdit();
    passwordField->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login");
    
    // Add to layout
    layout->addWidget(titleLabel);
    layout->addWidget(passwordField);
    layout->addWidget(loginButton);
    
    // Set layout on central widget
    centralWidget->setLayout(layout);
    
    // Connect button click to your slot
    connect(loginButton, &QPushButton::clicked, 
            this, &LoginWindow::onLoginButtonClicked);
    
    // Set window properties
    setWindowTitle("Password Manager");
    setGeometry(100, 100, 400, 200);
}

void LoginWindow::onLoginButtonClicked() {
    QString password = passwordField->text();

    // Creates a vault and tries to unlock it with pw
    Vault vault(password.toStdString());

    if (vault.unlock(password.toStdString())){
        std::cout << "Login Successful!" << std::endl;
        QMessageBox::information(this, "Success", "Login Successful!");
        // TO DO: Open main pw manager window
    } else {
        std::cout << "Login Failed. Incorrect password." << std::endl;
        QMessageBox::warning(this, "Error", "Incorrect password. Please try again.");
        passwordField->clear(); // clears pw to retry
        passwordField->setFocus(); // sets focus back to pw field for retry
    }
}
