#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H

#include <string>
#include <sstream>
#include <iomanip>

class AccountType {
private:
    std::string accountTypeID;
    std::string typeName;
    std::string currency;
    double interestRate;

public:
    AccountType() : accountTypeID(""), typeName(""), currency(""), interestRate(0.0) {}

    AccountType(std::string id, std::string name, std::string curr, double rate)
        : accountTypeID(id), typeName(name), currency(curr), interestRate(rate) {}

    // Getters
    std::string getAccountTypeID() const { return accountTypeID; }
    std::string getTypeName() const { return typeName; }
    std::string getCurrency() const { return currency; }
    double getInterestRate() const { return interestRate; }

    // Setters
    void setAccountTypeID(const std::string& id) { accountTypeID = id; }
    void setTypeName(const std::string& name) { typeName = name; }
    void setCurrency(const std::string& curr) { currency = curr; }
    void setInterestRate(double rate) { interestRate = rate; }

    // Chu?i xu?t ra file accounttypes.txt
    std::string toString() const {
        std::ostringstream oss;
        oss << accountTypeID << ", " << typeName << ", " << currency << ", " << interestRate;
        return oss.str();
    }
};

#endif