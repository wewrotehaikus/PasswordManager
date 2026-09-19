cmake_minimum_required(VERSION 3.10)

project(PasswordManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#QT 6 addons

#qt6 autotoolin
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# fin qt6 and libsodium
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

# Create executable with files
add_executable(PasswordManager
    main.cpp
    LoginWindow.h        
    LoginWindow.cpp 
    PasswordEntry.h
    PasswordEntry.cpp
    Vault.h
    Vault.cpp
    Crypto.h
    Crypto.cpp
    # NEW: Add Qt UI files here later (LoginWindow.h, LoginWindow.cpp, etc.)
)

#include directories for Qt and libsodium
target_include_directories(PasswordManager PRIVATE 
    ${SODIUM_INCLUDE_DIRS}
    /opt/homebrew/include
)

# Link directories
target_link_directories(PasswordManager PRIVATE
    /opt/homebrew/lib
)

#link libraries
target_link_libraries(PasswordManager PRIVATE 
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    ${SODIUM_LIBRARIES}
    sodium
)