/*
 * File: BankAccountList.h
 * Mo ta: Quan ly danh sach BankAccountList (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 17/11/2026
 */
#pragma once
#include "BankAccount.h"
#include "AccountTypeList.h"
#include <string>
#include <vector>

class BankAccountList {
private:
    std::vector<BankAccount> bankAccounts;
    const AccountTypeList& accountTypeList;
    void sortAccounts();

public:
    explicit BankAccountList(const AccountTypeList& types);
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    int searchID(const std::string& id) const;
    void addBankAccount(const BankAccount& account);
    bool removeBankAccount(const std::string& id);
    bool updateBankAccount(const std::string& id, const BankAccount& updated);
    void listBankAccounts() const;
    void printBasedAccountTypeName(const std::string& typeName) const;
};
