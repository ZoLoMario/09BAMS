/*
 * File: AccountType.cpp
 * Mo ta: Quan ly danh sach AccountType (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 */

#include "AccountType.h"
#include <sstream>
#include <iomanip>
#include <utility>

AccountType::AccountType(std::string id, std::string name, std::string curr, double rate)
    : accountTypeID(std::move(id)), typeName(std::move(name)),
      currency(std::move(curr)), interestRate(rate) {}

const std::string& AccountType::getAccountTypeID() const { return accountTypeID; }
const std::string& AccountType::getTypeName() const { return typeName; }
const std::string& AccountType::getCurrency() const { return currency; }
double AccountType::getInterestRate() const { return interestRate; }

void AccountType::setTypeName(const std::string& value) { typeName = value; }
void AccountType::setCurrency(const std::string& value) { currency = value; }
void AccountType::setInterestRate(double value) { interestRate = value; }

std::string AccountType::toString() const {
    std::ostringstream out;
    out << accountTypeID << " | " << typeName << " | " << currency
        << " | " << std::fixed << std::setprecision(2) << interestRate;
    return out.str();
}

int AccountType::compareTo(const AccountType& other) const {
    if (typeName < other.typeName) return -1;
    if (typeName > other.typeName) return 1;
    return accountTypeID.compare(other.accountTypeID);
}
