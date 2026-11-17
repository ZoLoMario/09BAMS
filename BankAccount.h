#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <sstream>
#include <iomanip>
#include "AccountType.h"
#include "Utils.h"

class BankAccount {
private:
    std::string accountID;
    AccountType accountType;
    std::string ownerName;
    std::string accountNumber;
    double balance;

public:
    BankAccount() : accountID(""), accountType(), ownerName(""), accountNumber(""), balance(0.0) {}

    BankAccount(std::string id, AccountType type, std::string owner, std::string accNum, double bal)
        : accountID(id), accountType(type), ownerName(owner), accountNumber(accNum), balance(bal) {}

    // Getters
    std::string getAccountID() const { return accountID; }
    AccountType getAccountType() const { return accountType; }
    std::string getOwnerName() const { return ownerName; }
    std::string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    // Setters
    void setAccountID(const std::string& id) { accountID = id; }
    void setAccountType(const AccountType& type) { accountType = type; }
    void setOwnerName(const std::string& owner) { ownerName = owner; }
    void setAccountNumber(const std::string& accNum) { accountNumber = accNum; }
    void setBalance(double bal) { balance = bal; }

    // Chuỗi xuất ra file bankaccounts.txt
    std::string toString() const {
        std::ostringstream oss;
        oss << accountID << ", "
            << accountType.getAccountTypeID() << ", "
            << ownerName << ", "
            << accountNumber << ", "
            << std::fixed << std::setprecision(0) << balance;
        return oss.str();
    }

    // Chuỗi định dạng hiển thị trên màn hình Console
    std::string screenString() const {
        std::ostringstream oss;
        oss << std::left
            << std::setw(8)  << accountID
            << std::setw(14) << accountType.getTypeName()
            << std::setw(22) << ownerName
            << std::setw(15) << accountNumber
            << std::right << std::setw(15) << std::fixed << std::setprecision(2) << balance
            << " " << accountType.getCurrency();
        return oss.str();
    }

    // So sánh tăng dần theo typeName (không phân biệt hoa/thường), nếu trùng thì so sánh accountID
    bool operator<(const BankAccount& other) const {
        std::string thisType = Utils::toLower(this->accountType.getTypeName());
        std::string otherType = Utils::toLower(other.accountType.getTypeName());
        if (thisType != otherType) {
            return thisType < otherType;
        }
        return Utils::toLower(this->accountID) < Utils::toLower(other.accountID);
    }
};

#endif