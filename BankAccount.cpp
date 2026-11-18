/*
 * File: BankAccount.cpp
 * Mo ta: Quan ly danh sach BankAccount (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 17/11/2026
 */
#include "BankAccount.h"
#include <sstream>
#include <iomanip>
#include <utility>

BankAccount::BankAccount(std::string id, const AccountType& type, std::string owner,
                         std::string number, double amount)
    : accountID(id), accountType(type), ownerName(owner),
      accountNumber(number), balance(amount) {}

const std::string& BankAccount::getAccountID() const { return accountID; }
const AccountType& BankAccount::getAccountType() const { return accountType; }
const std::string& BankAccount::getOwnerName() const { return ownerName; }
const std::string& BankAccount::getAccountNumber() const { return accountNumber; }
double BankAccount::getBalance() const { return balance; }

void BankAccount::setAccountType(const AccountType& value) { accountType = value; }
void BankAccount::setOwnerName(const std::string& value) { ownerName = value; }
void BankAccount::setAccountNumber(const std::string& value) { accountNumber = value; }
void BankAccount::setBalance(double value) { balance = value; }

std::string BankAccount::toString() const {
    std::ostringstream out;
    out << accountID << " | " << accountType.getTypeName() << " | " << ownerName
        << " | " << accountNumber << " | " << std::fixed << std::setprecision(2) << balance;
    return out.str();
}

int BankAccount::compareTo(const BankAccount& other) const {
    const int typeCompare = accountType.getTypeName().compare(other.accountType.getTypeName());
    if (typeCompare != 0) return typeCompare;
    return accountID.compare(other.accountID);
}

bool BankAccount::operator==(const BankAccount& other) const {
    return accountID == other.accountID;
}
