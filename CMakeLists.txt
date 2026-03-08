cmake_minimum_required(VERSION 3.5)

project(PasswordManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PasswordManager main.cpp
    PasswordEntry.h
    PasswordEntry.cpp
    Vault.h
    Vault.cpp)

include(GNUInstallDirs)
install(TARGETS PasswordManager
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
