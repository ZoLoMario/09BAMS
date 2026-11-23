/*
 * File: BankAccount.h
 * Mo ta: Khai bao class BankAccount - mot tai khoan ngan hang, lien ket toi mot AccountType.
 *        Sap xep theo typeName, trung thi theo accountID (operator<).
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong (khung .h: K26DTCN089 - Vu Trong Hanh)
 * Ngay viet: 17/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 * Ngay duyet:
 */
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

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
    BankAccount(const std::string& id, const AccountType& type, const std::string& owner,
                const std::string& number, double amount);

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
    std::string screenString() const;
    static std::string screenHeader();
    int compareTo(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator==(const BankAccount& other) const;
};

#endif