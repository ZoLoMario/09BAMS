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
#include "DataFile.h"


/*
 * Ham: loadFromFile
 * Chuc nang: Doc danh sach AccountType tu file. Dong sai dinh dang, truong rong,
 *            lai suat khong phai so hoac <= 0, ma trung: bo qua va bao ro so dong.
 * Tham so: filename - ten file (accounttypes.txt)
 * Tra ve: false neu khong mo duoc file (file thieu), nguoc lai true
 * Nguoi viet: K26DTCN019 - Nguyen Quoc Khanh
 * Kiem tra loi nap file: K26DTCN100 - Vu Dang Khoi, 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
bool AccountTypeList::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        return false;
    }
    accountTypes.clear();
    std::string line;
    int lineNumber = 0;
    while (std::getline(in, line)) {
        lineNumber++;
        if (DataFile::isSkippableLine(line) || DataFile::isHeaderLine(line, "accountTypeID")) {
            continue;
        }
        std::vector<std::string> fields;
        std::string error;
        double rate = 0.0;
        if (!DataFile::splitRecord(line, 4, fields, error)) {
            // error da duoc splitRecord ghi
        } else if (!DataFile::parseNumber(fields[3], rate)) {
            error = "interestRate is not a number";
        } else if (rate <= 0) {
            error = "interestRate must be greater than 0";
        } else if (searchID(fields[0]) >= 0) {
            error = "duplicate accountTypeID " + fields[0];
        } else {
            accountTypes.emplace_back(fields[0], fields[1], fields[2], rate);
            continue;
        }
        std::cerr << "Warning: " << filename << " line " << lineNumber
                  << " skipped (" << error << "): " << line << '\n';
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
