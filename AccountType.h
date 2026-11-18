/*
 * File: AccountType.h
 * Mo ta: Quan ly danh sach AccountType (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 */
#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H

#include <string>

class AccountType {
private:
    std::string accountTypeID;
    std::string typeName;
    std::string currency;
    double interestRate;

public:
    AccountType(std::string id, std::string name,
                std::string curr, double rate);

    const std::string& getAccountTypeID() const;
    const std::string& getTypeName() const;
    const std::string& getCurrency() const;
    double getInterestRate() const;

    void setTypeName(const std::string& value);
    void setCurrency(const std::string& value);
    void setInterestRate(double value);

    std::string toString() const;
    int compareTo(const AccountType& other) const;
};

#endif
