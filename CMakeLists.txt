cmake_minimum_required(VERSION 3.16)
project(BankAccountPrj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(BankAccountPrj
    src/main.cpp
    src/AccountType.cpp
    src/AccountTypeList.cpp
    src/BankAccount.cpp
    src/BankAccountList.cpp
    src/Menu.cpp
)
target_include_directories(BankAccountPrj PRIVATE include)
