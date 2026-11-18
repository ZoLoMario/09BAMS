/*
 * File: AccountTypeList.h
 * Mo ta: Quan ly danh sach AccountTypeList (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 */
#pragma once
#include "AccountType.h"
#include <string>
#include <vector>

class AccountTypeList {
private:
    std::vector<AccountType> accountTypes;

public:
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    int searchID(const std::string& id) const;
    AccountType* findByID(const std::string& id);
    const AccountType* findByID(const std::string& id) const;
    AccountType getUserChoice() const;
    void addAccountType(const AccountType& type);
    bool updateAccountType(const std::string& id, const AccountType& updated);
    void listAccountTypes() const;
    const std::vector<AccountType>& getAll() const;
};
