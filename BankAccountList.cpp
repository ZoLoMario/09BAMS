/*
 * File: BankAccountList.cpp
 * Mo ta: Quan ly danh sach BankAccountList (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 17/11/2026
 */
#include "BankAccountList.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "DataFile.h"
#include "Utils.h"

BankAccountList::BankAccountList(const AccountTypeList& types) : accountTypeList(types) {}

/*
 * Ham: sortAccounts
 * Chuc nang: Sap xep danh sach theo typeName, trung thi theo accountID
 *            (dung BankAccount::operator< + std::sort)
 * Tham so: khong
 * Tra ve: khong
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 23/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
void BankAccountList::sortAccounts() {
    std::sort(bankAccounts.begin(), bankAccounts.end());
}

/*
 * Ham: loadFromFile
 * Chuc nang: Doc danh sach BankAccount tu file (phai nap accounttypes.txt truoc).
 *            Dong sai dinh dang, truong rong, so du khong phai so hoac am,
 *            ma trung, accountType khong ton tai: bo qua va bao ro so dong.
 * Tham so: filename - ten file (bankaccounts.txt)
 * Tra ve: false neu khong mo duoc file (file thieu), nguoc lai true
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Kiem tra loi nap file: K26DTCN100 - Vu Dang Khoi, 18/11/2026
 *   (thay trimAccount cu: chuoi " \\t\\r\\n" cat nham chu t/r/n cuoi ten)
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
bool BankAccountList::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        return false;
    }
    bankAccounts.clear();
    std::string line;
    int lineNumber = 0;
    while (std::getline(in, line)) {
        lineNumber++;
        if (DataFile::isSkippableLine(line) || DataFile::isHeaderLine(line, "accountID")) {
            continue;
        }
        std::vector<std::string> fields;
        std::string error;
        double balance = 0.0;
        const AccountType* type = nullptr;
        if (!DataFile::splitRecord(line, 5, fields, error)) {
            // error da duoc splitRecord ghi
        } else if ((type = accountTypeList.findByID(fields[1])) == nullptr) {
            error = "accountType " + fields[1] + " does not exist";
        } else if (!DataFile::parseNumber(fields[4], balance) || !std::isfinite(balance)) {
            // std::stod doc duoc "nan"/"inf"; nan < 0 la false nen phai chan rieng
            error = "balance is not a number";
        } else if (balance < 0) {
            error = "balance must not be negative";
        } else if (searchID(fields[0]) >= 0) {
            error = "duplicate accountID " + fields[0];
        } else {
            bankAccounts.emplace_back(fields[0], *type, fields[2], fields[3], balance);
            continue;
        }
        std::cerr << "Warning: " << filename << " line " << lineNumber
                  << " skipped (" << error << "): " << line << '\n';
    }
    sortAccounts();
    return true;
}

/*
 * Ham: saveToFile (CN 11)
 * Chuc nang: Ghi danh sach BankAccount ra file: dong tieu de '#', cac truong cach nhau
 *            boi ", " (cung dinh dang accounttypes.txt va de bai). So du ghi dang thuong
 *            2 chu so thap phan, khong ghi dang 1.2e+07 va khong mat chu so.
 * Tham so: filename - ten file (bankaccounts.txt)
 * Tra ve: false neu khong mo duoc file hoac ghi loi, nguoc lai true
 * Nguoi viet: K26DTCN008 - Nguyen Thanh Dat
 * Ngay viet: 22/11/2026
 * Nguoi duyet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay duyet:
 * Ket qua:
 */
bool BankAccountList::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    out << "# accountID, accountType, ownerName, accountNumber, balance\n"
        << std::fixed << std::setprecision(2);
    // Luu y: truong co dau ',' (chi co the den tu file '|' sua tay) se loi khi nap lai
    for (const auto& a : bankAccounts)
        out << a.getAccountID() << ", " << a.getAccountType().getAccountTypeID()
            << ", " << a.getOwnerName() << ", " << a.getAccountNumber()
            << ", " << a.getBalance() << '\n';
    out.flush();
    return static_cast<bool>(out);
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

/*
 * Ham: updateBankAccount (CN 10)
 * Chuc nang: Cap nhat BankAccount theo ma, kiem tra rang buoc truoc khi ghi:
 *            ma moi khong trung ban ghi khac, accountType phai ton tai,
 *            ownerName/accountNumber khong rong, balance khong am.
 * Tham so: id - ma tai khoan can sua; updated - du lieu moi
 * Tra ve: false neu khong tim thay id; nem std::invalid_argument neu vi pham rang buoc
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
bool BankAccountList::updateBankAccount(const std::string& id, const BankAccount& updated) {
    const int index = searchID(id);
    if (index < 0) {
        return false;
    }
    if (updated.getAccountID().empty() || updated.getOwnerName().empty()
        || updated.getAccountNumber().empty()) {
        throw std::invalid_argument("accountID, ownerName and accountNumber must not be empty.");
    }
    if (updated.getBalance() < 0) {
        throw std::invalid_argument("balance must not be negative.");
    }
    if (updated.getAccountID() != id && searchID(updated.getAccountID()) >= 0) {
        throw std::invalid_argument("accountID " + updated.getAccountID() + " already exists.");
    }
    if (accountTypeList.findByID(updated.getAccountType().getAccountTypeID()) == nullptr) {
        throw std::invalid_argument("accountType does not exist.");
    }
    bankAccounts[static_cast<std::size_t>(index)] = updated;
    sortAccounts();
    return true;
}

/*
 * Ham: findByID
 * Chuc nang: Lay BankAccount theo ma (de hien du lieu cu khi cap nhat)
 * Tham so: id - ma tai khoan
 * Tra ve: con tro toi tai khoan, nullptr neu khong co
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
const BankAccount* BankAccountList::findByID(const std::string& id) const {
    const int index = searchID(id);
    return index < 0 ? nullptr : &bankAccounts[static_cast<std::size_t>(index)];
}

/*
 * Ham: deposit (mo rong)
 * Chuc nang: Nap tien vao tai khoan
 * Tham so: id - ma tai khoan; amount - so tien nap (> 0)
 * Tra ve: false neu khong tim thay id; nem std::invalid_argument neu amount <= 0
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
bool BankAccountList::deposit(const std::string& id, double amount) {
    const int index = searchID(id);
    if (index < 0) {
        return false;
    }
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be greater than 0.");
    }
    BankAccount& account = bankAccounts[static_cast<std::size_t>(index)];
    account.setBalance(account.getBalance() + amount);
    return true;
}

/*
 * Ham: withdraw (mo rong)
 * Chuc nang: Rut tien, khong cho rut qua so du (balance khong duoc am)
 * Tham so: id - ma tai khoan; amount - so tien rut (> 0, <= so du)
 * Tra ve: false neu khong tim thay id; nem std::invalid_argument neu so tien sai
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
bool BankAccountList::withdraw(const std::string& id, double amount) {
    const int index = searchID(id);
    if (index < 0) {
        return false;
    }
    BankAccount& account = bankAccounts[static_cast<std::size_t>(index)];
    if (amount <= 0) {
        throw std::invalid_argument("Withdraw amount must be greater than 0.");
    }
    if (amount > account.getBalance()) {
        throw std::invalid_argument("Insufficient balance.");
    }
    account.setBalance(account.getBalance() - amount);
    return true;
}

/*
 * Ham: getAll
 * Chuc nang: Tra ve danh sach tai khoan (chi doc) de tinh lai
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
const std::vector<BankAccount>& BankAccountList::getAll() const {
    return bankAccounts;
}

/*
 * Ham: syncAccountType
 * Chuc nang: Sau khi sua mot AccountType (CN 4), cap nhat ban sao AccountType
 *            trong cac BankAccount dang tham chieu ma cu. Neu khong dong bo,
 *            tai khoan van hien ten loai cu, va khi doi ma loai thi luu file
 *            se ghi ma cu khong con ton tai -> lan nap sau bi bo qua (mat du lieu).
 * Tham so: oldTypeID - ma loai truoc khi sua; updated - AccountType moi
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
void BankAccountList::syncAccountType(const std::string& oldTypeID, const AccountType& updated) {
    for (std::size_t i = 0; i < bankAccounts.size(); i++) {
        if (bankAccounts[i].getAccountType().getAccountTypeID() == oldTypeID) {
            bankAccounts[i].setAccountType(updated);
        }
    }
    sortAccounts();
}

void BankAccountList::listBankAccounts() const {
    for (const auto& a : bankAccounts) std::cout << a.toString() << '\n';
}

/*
 * Ham: printBasedAccountTypeName (CN 7)
 * Chuc nang: In cac BankAccount co typeName CHUA chuoi can tim (mot phan, khong phan
 *            biet hoa/thuong); khong co ket qua thi in thong bao.
 * Tham so: typeName - chuoi can tim (mot phan cua typeName)
 * Nguoi viet: K26DTCN008 - Nguyen Thanh Dat
 * Ngay viet: 22/11/2026
 * Nguoi duyet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay duyet:
 * Ket qua:
 */
void BankAccountList::printBasedAccountTypeName(const std::string& typeName) const {
    const std::string keyword = Utils::toLower(Utils::trim(typeName));
    int found = 0;
    for (const auto& a : bankAccounts) {
        if (Utils::toLower(a.getAccountType().getTypeName()).find(keyword) != std::string::npos) {
            std::cout << a.toString() << '\n';
            found++;
        }
    }
    if (found == 0) std::cout << "No BankAccount matches \"" << typeName << "\".\n";
}
