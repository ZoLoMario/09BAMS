#ifndef ACCOUNTTYPELIST_H
#define ACCOUNTTYPELIST_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "AccountType.h"
#include "Menu.h"
#include "Utils.h"

class AccountTypeList {
private:
    std::vector<AccountType> list;

public:
    AccountTypeList() {}

    int size() const { return static_cast<int>(list.size()); }

    AccountType getAt(int index) const {
        return list.at(index);
    }

    // Tìm kiếm theo ID (không phân biệt hoa/thường), trả về index hoặc -1
    int searchID(const std::string& id) const {
        std::string target = Utils::toLower(Utils::trim(id));
        for (size_t i = 0; i < list.size(); ++i) {
            if (Utils::toLower(list[i].getAccountTypeID()) == target) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // Đọc dữ liệu từ file bằng RAII (std::ifstream tự đóng khi ra khỏi scope)
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
            if (parts.size() != 4) {
                std::cout << "[File Error - " << filename << " line " << lineNum
                          << "] Invalid format (expected 4 fields): " << line << "\n";
                continue;
            }

            std::string id = parts[0];
            std::string name = parts[1];
            std::string curr = parts[2];
            double rate = 0.0;

            try {
                size_t idx = 0;
                rate = std::stod(parts[3], &idx);
                if (idx != parts[3].length()) throw std::invalid_argument("Invalid double");
            } catch (...) {
                std::cout << "[File Error - " << filename << " line " << lineNum
                          << "] Invalid interestRate: " << parts[3] << "\n";
                continue;
            }

            if (id.empty() || name.empty() || curr.empty() || rate <= 0) {
                std::cout << "[File Error - " << filename << " line " << lineNum
                          << "] Constraint violation (empty field or interestRate <= 0).\n";
                continue;
            }

            if (searchID(id) != -1) {
                std::cout << "[File Error - " << filename << " line " << lineNum
                          << "] Duplicate accountTypeID: " << id << "\n";
                continue;
            }

            list.emplace_back(id, name, curr, rate);
        }
        return true;
    }

    // Ghi dữ liệu ra file bằng RAII
    bool saveToFile(const std::string& filename) const {
        std::ofstream fout(filename);
        if (!fout.is_open()) {
            std::cout << "[Error] Cannot open file for writing: " << filename << "\n";
            return false;
        }
        for (const auto& item : list) {
            fout << item.toString() << "\n";
        }
        std::cout << "[Success] Saved " << list.size() << " AccountTypes to " << filename << ".\n";
        return true;
    }

    // Cho người dùng chọn AccountType từ menu
    AccountType getUserChoice() const {
        if (list.empty()) {
            throw std::runtime_error("AccountType list is empty!");
        }
        std::vector<std::string> options;
        for (const auto& item : list) {
            options.push_back(item.getAccountTypeID() + " - " + item.getTypeName() + " (" + item.getCurrency() + ")");
        }
        Menu menu;
        std::cout << "\n--- Select an AccountType ---\n";
        int choice = menu.int_getChoice(options);
        return list[choice - 1];
    }

    // Option 1: Hiển thị toàn bộ AccountType
    void listAccountTypes() const {
        if (list.empty()) {
            std::cout << "No AccountTypes available.\n";
            return;
        }
        std::cout << "\n==========================================================\n";
        std::cout << std::left
                  << std::setw(10) << "TypeID"
                  << std::setw(18) << "TypeName"
                  << std::setw(12) << "Currency"
                  << std::right << std::setw(15) << "InterestRate" << "\n";
        std::cout << "----------------------------------------------------------\n";
        for (const auto& item : list) {
            std::cout << std::left
                      << std::setw(10) << item.getAccountTypeID()
                      << std::setw(18) << item.getTypeName()
                      << std::setw(12) << item.getCurrency()
                      << std::right << std::setw(15) << std::fixed << std::setprecision(4) << item.getInterestRate() << "\n";
        }
        std::cout << "==========================================================\n";
    }

    // Option 2: Thêm AccountType mới
    void addAccountType() {
        std::cout << "\n--- Add a New AccountType ---\n";
        std::string id;
        while (true) {
            id = Utils::inputNonEmptyString("Enter AccountType ID: ");
            if (searchID(id) != -1) {
                std::cout << "[Error] AccountType ID '" << id << "' already exists. Please enter another ID.\n";
            } else {
                break;
            }
        }
        std::string name = Utils::inputNonEmptyString("Enter Type Name: ");
        std::string curr = Utils::inputNonEmptyString("Enter Currency (e.g., VND, USD): ");
        double rate = Utils::inputDouble("Enter Interest Rate (> 0): ", 0.0, true);

        list.emplace_back(id, name, curr, rate);
        std::cout << "[Success] Added new AccountType: " << id << "\n";
    }

    // Option 3: Tìm kiếm AccountType theo ID
    void searchAccountTypeByID() const {
        std::string id = Utils::inputNonEmptyString("Enter AccountType ID to search: ");
        int pos = searchID(id);
        if (pos == -1) {
            std::cout << "[Not Found] No AccountType with ID '" << id << "'.\n";
        } else {
            const AccountType& item = list[pos];
            std::cout << "[Found] ID: " << item.getAccountTypeID()
                      << " | Name: " << item.getTypeName()
                      << " | Currency: " << item.getCurrency()
                      << " | Rate: " << item.getInterestRate() << "\n";
        }
    }

    // Option 4: Cập nhật AccountType theo mã
    void updateAccountType() {
        std::cout << "\n--- Update AccountType ---\n";
        std::string id = Utils::inputNonEmptyString("Enter AccountType ID to update: ");
        int pos = searchID(id);
        if (pos == -1) {
            std::cout << "[Not Found] AccountType ID '" << id << "' does not exist.\n";
            return;
        }

        std::cout << "Updating AccountType: " << list[pos].toString() << "\n";
        std::string newName = Utils::inputNonEmptyString("Enter new Type Name: ");
        std::string newCurr = Utils::inputNonEmptyString("Enter new Currency: ");
        double newRate = Utils::inputDouble("Enter new Interest Rate (> 0): ", 0.0, true);

        list[pos].setTypeName(newName);
        list[pos].setCurrency(newCurr);
        list[pos].setInterestRate(newRate);

        std::cout << "[Success] Updated AccountType '" << id << "'.\n";
    }
};

#endif