cmake_minimum_required(VERSION 3.16)
project(BankAccountPrj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ma nguon nam o thu muc goc (giong project Dev-C++ BankAccountPrj.dev)
add_executable(BankAccountPrj
    main.cpp
    BankAccountManager.cpp
    AccountType.cpp
    AccountTypeList.cpp
    BankAccount.cpp
    BankAccountList.cpp
    Menu.cpp
)
