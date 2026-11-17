#ifndef BANKACCOUNTLIST_H
#define BANKACCOUNTLIST_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "BankAccount.h"
#include "AccountTypeList.h"
#include "Utils.h"

class BankAccountList {
private:
    AccountTypeList& accountTypeList;
    std::vector<BankAccount> list;

public:
    BankAccountList(AccountTypeList& typeList) : accountTypeList(typeList) {}

    // Tìm vị trí BankAccount theo ID (không phân biệt hoa/thường), trả về -1 nếu không thấy
    int searchID(const std::string& id) const {
        std::string target = Utils::toLower(Utils::trim(id));
        for (size_t i = 0; i < list.size(); ++i) {
            if (Utils::toLower(list[i].getAccountID()) == target) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // Đọc dữ liệu từ bankaccounts.txt bằng RAII
    bool loadFromFile(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            std::cout << "[Warning] Cannot open file: " << filename << "\n";
            return false;
        }

        list.clear();
        std::string line;
        int lineNum = 0;

        while (std::getline(fin, line)) {
            lineNum++;
            line = Utils::trim(line);
            if (line.empty()) continue;

            std::vector<std::string> parts = Utils::split(line, ',');
            if (parts.size() != 5) {
                std::cout << "[File Error - " << filename << " line " << lineNum
                          << "] Invalid format (expected 5 fields): " << line << "\n";
                continue;
            }

            std::string accID = parts[0];
            std::string typeID = parts[1];
            std::string owner = parts[2];
            std::string accNum = parts[3];
            double bal = 0.0;

            try {
                size_t idx = 0;
                bal = std::stod(parts[4], &idx);
                if (idx != parts[4].length()) throw std::invalid_argument("Invalid double");
            } catch (...) {
                std::cout << "[File Error - " << filename << " line " << lineNum
                          << "] Invalid balance: " << parts[4] << "\n";
                continue;
            }

            if (accID.empty() || typeID.empty() || owner.empty() || accNum.empty() || bal < 0) {
                std::cout << "[File Error - " << filename << " line " << lineNum
                          << "] Constraint violation (empty field or negative balance).\n";
                continue;
            }

            if (searchID(accID) != -1) {
                std::cout << "[File Error - " << filename << " line " << lineNum
                          << "] Duplicate accountID: " << accID << "\n";
                continue;
            }

            // Kiểm tra tham chiếu khóa ngoại tới AccountTypeList
            int typePos = accountTypeList.searchID(typeID);
            if (typePos == -1) {
                std::cout << "[File Error - " << filename << " line " << lineNum
                          << "] Referenced accountTypeID '" << typeID << "' does not exist.\n";
                continue;
            }

            AccountType matchedType = accountTypeList.getAt(typePos);
            list.emplace_back(accID, matchedType, owner, accNum, bal);
        }
        return true;
    }

    // Ghi dữ liệu ra bankaccounts.txt bằng RAII
    bool saveToFile(const std::string& filename) const {
        std::ofstream fout(filename);
        if (!fout.is_open()) {
            std::cout << "[Error] Cannot open file for writing: " << filename << "\n";
            return false;
        }
        for (const auto& acc : list) {
            fout << acc.toString() << "\n";
        }
        std::cout << "[Success] Saved " << list.size() << " BankAccounts to " << filename << ".\n";
        return true;
    }

    // Đồng bộ lại thông tin AccountType nếu danh mục AccountType bị cập nhật tên/lãi suất
    void syncAccountTypes() {
        for (auto& acc : list) {
            int pos = accountTypeList.searchID(acc.getAccountType().getAccountTypeID());
            if (pos != -1) {
                acc.setAccountType(accountTypeList.getAt(pos));
            }
        }
    }

    // Option 6: Hiển thị danh sách sắp xếp tăng dần theo typeName, trùng thì theo accountID
    void listBankAccounts() {
        if (list.empty()) {
            std::cout << "No BankAccounts available.\n";
            return;
        }
        syncAccountTypes();
        std::sort(list.begin(), list.end()); // Sử dụng BankAccount::operator<

        std::cout << "\n===============================================================================\n";
        std::cout << std::left
                  << std::setw(8)  << "AccID"
                  << std::setw(14) << "TypeName"
                  << std::setw(22) << "OwnerName"
                  << std::setw(15) << "AccountNumber"
                  << std::right << std::setw(19) << "Balance" << "\n";
        std::cout << "-------------------------------------------------------------------------------\n";
        for (const auto& acc : list) {
            std::cout << acc.screenString() << "\n";
        }
        std::cout << "===============================================================================\n";
    }

    // Option 7: Tìm kiếm BankAccount theo chuỗi con của typeName (không phân biệt hoa/thường)
    void printBasedAccountTypeName() {
        if (list.empty()) {
            std::cout << "No BankAccounts available.\n";
            return;
        }
        syncAccountTypes();
        std::string keyword = Utils::inputNonEmptyString("Enter partial Type Name to search: ");
        std::string lowerKey = Utils::toLower(keyword);

        bool found = false;
        std::cout << "\n--- Search Results for '" << keyword << "' ---\n";
        for (const auto& acc : list) {
            std::string lowerTypeName = Utils::toLower(acc.getAccountType().getTypeName());
            if (lowerTypeName.find(lowerKey) != std::string::npos) {
                if (!found) {
                    std::cout << std::left
                              << std::setw(8)  << "AccID"
                              << std::setw(14) << "TypeName"
                              << std::setw(22) << "OwnerName"
                              << std::setw(15) << "AccountNumber"
                              << std::right << std::setw(19) << "Balance" << "\n";
                    std::cout << "-------------------------------------------------------------------------------\n";
                }
                std::cout << acc.screenString() << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "[Not Found] No BankAccount matches typeName containing '" << keyword << "'.\n";
        }
    }

    // Option 8: Thêm BankAccount mới
    void addBankAccount() {
        if (accountTypeList.size() == 0) {
            std::cout << "[Error] Cannot add BankAccount because AccountType list is empty.\n";
            return;
        }
        std::cout << "\n--- Add a New BankAccount ---\n";
        std::string id;
        while (true) {
            id = Utils::inputNonEmptyString("Enter BankAccount ID: ");
            if (searchID(id) != -1) {
                std::cout << "[Error] BankAccount ID '" << id << "' already exists. Please enter another ID.\n";
            } else {
                break;
            }
        }

        AccountType chosenType = accountTypeList.getUserChoice();
        std::string owner = Utils::inputNonEmptyString("Enter Owner Name: ");
        std::string accNum = Utils::inputNonEmptyString("Enter Account Number: ");
        double bal = Utils::inputDouble("Enter Initial Balance (>= 0): ", 0.0, false);

        list.emplace_back(id, chosenType, owner, accNum, bal);
        std::cout << "[Success] Added new BankAccount: " << id << "\n";
    }

    // Option 9: Xóa BankAccount theo ID
    bool removeBankAccount() {
        std::cout << "\n--- Remove BankAccount ---\n";
        std::string id = Utils::inputNonEmptyString("Enter BankAccount ID to remove: ");
        int pos = searchID(id);
        if (pos == -1) {
            std::cout << "[Not Found] BankAccount ID '" << id << "' does not exist.\n";
            return false;
        }
        list.erase(list.begin() + pos);
        std::cout << "[Success] Removed BankAccount '" << id << "'.\n";
        return true;
    }

    // Option 10: Cập nhật BankAccount theo ID
    bool updateBankAccount() {
        std::cout << "\n--- Update BankAccount ---\n";
        std::string id = Utils::inputNonEmptyString("Enter BankAccount ID to update: ");
        int pos = searchID(id);
        if (pos == -1) {
            std::cout << "[Not Found] BankAccount ID '" << id << "' does not exist.\n";
            return false;
        }

        std::cout << "Current Info: " << list[pos].screenString() << "\n";

        // Cho phép cập nhật lại ID nhưng phải kiểm tra không trùng với các bản ghi khác
        std::string newID;
        while (true) {
            newID = Utils::inputNonEmptyString("Enter new BankAccount ID (or re-enter '" + list[pos].getAccountID() + "'): ");
            int existingPos = searchID(newID);
            if (existingPos != -1 && existingPos != pos) {
                std::cout << "[Error] BankAccount ID '" << newID << "' is already used by another account.\n";
            } else {
                break;
            }
        }

        AccountType newType = accountTypeList.getUserChoice();
        std::string newOwner = Utils::inputNonEmptyString("Enter new Owner Name: ");
        std::string newAccNum = Utils::inputNonEmptyString("Enter new Account Number: ");
        double newBal = Utils::inputDouble("Enter new Balance (>= 0): ", 0.0, false);

        list[pos].setAccountID(newID);
        list[pos].setAccountType(newType);
        list[pos].setOwnerName(newOwner);
        list[pos].setAccountNumber(newAccNum);
        list[pos].setBalance(newBal);

        std::cout << "[Success] Updated BankAccount '" << newID << "'.\n";
        return true;
    }
};

#endif