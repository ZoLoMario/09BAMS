/*
 * File: AccountTypeList.cpp
 * Mo ta: Quan ly danh sach AccountTypeList (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 */
#include "AccountType.h"
#include <fstream>
#include <iostream>
#include "AccountTypeList.h"
#include <sstream>
#include <stdexcept>

namespace {
std::string trim(const std::string& s) {
    const auto first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    const auto last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}
}

bool AccountTypeList::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;
    accountTypes.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (trim(line).empty() || trim(line)[0] == '#') continue;
        std::stringstream ss(line);
        std::string id, name, currency, rateText;
        if (!std::getline(ss, id, '|') || !std::getline(ss, name, '|') ||
            !std::getline(ss, currency, '|') || !std::getline(ss, rateText)) continue;
        try {
            accountTypes.emplace_back(trim(id), trim(name), trim(currency), std::stod(trim(rateText)));
        } catch (...) {
            std::cerr << "Bo qua dong account type khong hop le: " << line << '\n';
        }
    }
    return true;
}

bool AccountTypeList::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    for (const auto& t : accountTypes)
        out << t.getAccountTypeID() << " | " << t.getTypeName() << " | "
            << t.getCurrency() << " | " << t.getInterestRate() << '\n';
    return true;
}

int AccountTypeList::searchID(const std::string& id) const {
    for (std::size_t i = 0; i < accountTypes.size(); ++i)
        if (accountTypes[i].getAccountTypeID() == id) return static_cast<int>(i);
    return -1;
}

AccountType* AccountTypeList::findByID(const std::string& id) {
    const int i = searchID(id);
    return i < 0 ? nullptr : &accountTypes[static_cast<std::size_t>(i)];
}
const AccountType* AccountTypeList::findByID(const std::string& id) const {
    const int i = searchID(id);
    return i < 0 ? nullptr : &accountTypes[static_cast<std::size_t>(i)];
}

AccountType AccountTypeList::getUserChoice() const {
    if (accountTypes.empty()) throw std::runtime_error("Danh sach loai tai khoan rong.");
    listAccountTypes();
    std::string id;
    std::cout << "Nhap AccountType ID: ";
    std::getline(std::cin >> std::ws, id);
    const auto* found = findByID(id);
    if (!found) throw std::runtime_error("Khong tim thay AccountType ID.");
    return *found;
}

void AccountTypeList::addAccountType(const AccountType& type) {
    if (searchID(type.getAccountTypeID()) >= 0)
        throw std::invalid_argument("AccountType ID da ton tai.");
    accountTypes.push_back(type);
}

bool AccountTypeList::updateAccountType(const std::string& id, const AccountType& updated) {
    auto* current = findByID(id);
    if (!current) return false;
    if (updated.getAccountTypeID() != id && searchID(updated.getAccountTypeID()) >= 0)
        return false;
    *current = updated;
    return true;
}

void AccountTypeList::listAccountTypes() const {
    for (const auto& t : accountTypes) std::cout << t.toString() << '\n';
}
const std::vector<AccountType>& AccountTypeList::getAll() const { return accountTypes; }
