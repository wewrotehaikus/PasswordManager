cmake_minimum_required(VERSION 3.10)

project(PasswordManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

add_executable(PasswordManager
    main.cpp
    PasswordEntry.h
    PasswordEntry.cpp
    Vault.h
    Vault.cpp
    Crypto.h
    Crypto.cpp
)

target_include_directories(PasswordManager PRIVATE ${SODIUM_INCLUDE_DIRS})
target_link_libraries(PasswordManager PRIVATE ${SODIUM_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS PasswordManager
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)