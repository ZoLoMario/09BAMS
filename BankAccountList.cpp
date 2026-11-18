/*
 * File: BankAccountList.cpp
 * Mo ta: Quan ly danh sach BankAccountList (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 17/11/2026
 */
#include "BankAccountList.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {
std::string trimAccount(const std::string& s) {
    const auto first = s.find_first_not_of(" \\t\\r\\n");
    if (first == std::string::npos) return "";
    const auto last = s.find_last_not_of(" \\t\\r\\n");
    return s.substr(first, last - first + 1);
}
}

BankAccountList::BankAccountList(const AccountTypeList& types) : accountTypeList(types) {}

void BankAccountList::sortAccounts() {
    std::sort(bankAccounts.begin(), bankAccounts.end(),
        [](const BankAccount& a, const BankAccount& b) { return a.compareTo(b) < 0; });
}

bool BankAccountList::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;
    bankAccounts.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (trimAccount(line).empty() || trimAccount(line)[0] == '#') continue;
        std::stringstream ss(line);
        std::string id, typeID, owner, number, balanceText;
        if (!std::getline(ss, id, '|') || !std::getline(ss, typeID, '|') ||
            !std::getline(ss, owner, '|') || !std::getline(ss, number, '|') ||
            !std::getline(ss, balanceText)) continue;

        // Resolve AccountType ID only after accounttypes.txt has been loaded.
        const AccountType* type = accountTypeList.findByID(trimAccount(typeID));
        if (!type) {
            std::cerr << "Bo qua tai khoan co AccountType ID khong ton tai: " << line << '\n';
            continue;
        }
        try {
            bankAccounts.emplace_back(trimAccount(id), *type, trimAccount(owner),
                trimAccount(number), std::stod(trimAccount(balanceText)));
        } catch (...) {
            std::cerr << "Bo qua dong bank account khong hop le: " << line << '\n';
        }
    }
    sortAccounts();
    return true;
}

bool BankAccountList::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    for (const auto& a : bankAccounts)
        out << a.getAccountID() << " | " << a.getAccountType().getAccountTypeID()
            << " | " << a.getOwnerName() << " | " << a.getAccountNumber()
            << " | " << a.getBalance() << '\n';
    return true;
}

int BankAccountList::searchID(const std::string& id) const {
    for (std::size_t i = 0; i < bankAccounts.size(); ++i)
        if (bankAccounts[i].getAccountID() == id) return static_cast<int>(i);
    return -1;
}

void BankAccountList::addBankAccount(const BankAccount& account) {
    if (searchID(account.getAccountID()) >= 0)
        throw std::invalid_argument("BankAccount ID da ton tai.");
    if (!accountTypeList.findByID(account.getAccountType().getAccountTypeID()))
        throw std::invalid_argument("AccountType khong ton tai.");
    bankAccounts.push_back(account);
    sortAccounts();
}

bool BankAccountList::removeBankAccount(const std::string& id) {
    const int i = searchID(id);
    if (i < 0) return false;
    bankAccounts.erase(bankAccounts.begin() + i);
    return true;
}

bool BankAccountList::updateBankAccount(const std::string& id, const BankAccount& updated) {
    const int i = searchID(id);
    if (i < 0 || (updated.getAccountID() != id && searchID(updated.getAccountID()) >= 0))
        return false;
    if (!accountTypeList.findByID(updated.getAccountType().getAccountTypeID())) return false;
    bankAccounts[static_cast<std::size_t>(i)] = updated;
    sortAccounts();
    return true;
}

void BankAccountList::listBankAccounts() const {
    for (const auto& a : bankAccounts) std::cout << a.toString() << '\n';
}

void BankAccountList::printBasedAccountTypeName(const std::string& typeName) const {
    for (const auto& a : bankAccounts)
        if (a.getAccountType().getTypeName() == typeName) std::cout << a.toString() << '\n';
}
