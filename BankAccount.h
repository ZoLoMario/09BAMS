/*
 * File: BankAccount.h
 * Mo ta: Quan ly danh sach AccountType (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 17/11/2026
 */
#pragma once
#include "AccountType.h"
#include <string>

class BankAccount {
private:
    std::string accountID;
    AccountType accountType;
    std::string ownerName;
    std::string accountNumber;
    double balance{0.0};

public:
    BankAccount() = default;
    BankAccount(std::string id, const AccountType& type, std::string owner,
                std::string number, double amount);

    const std::string& getAccountID() const;
    const AccountType& getAccountType() const;
    const std::string& getOwnerName() const;
    const std::string& getAccountNumber() const;
    double getBalance() const;

    void setAccountType(const AccountType& value);
    void setOwnerName(const std::string& value);
    void setAccountNumber(const std::string& value);
    void setBalance(double value);

    std::string toString() const;
    int compareTo(const BankAccount& other) const;
    bool operator==(const BankAccount& other) const;
};
