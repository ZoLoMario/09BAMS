/*
 * File: Main.cpp
 * Mo ta: Quan ly danh sach Main (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 */
#include <iostream>
#include "AccountTypeList.h"
#include "BankAccountList.h"
#include "Menu.h"
int main() {
    const std::string typeFile = "account_types.txt";
    const std::string accountFile = "bank_accounts.txt";

    AccountTypeList typeList;
    BankAccountList accountList(typeList);

    // Tu dong doc du lieu tu file neu co san, neu chua co thi tao du lieu mau
    if (!typeList.loadFromFile(typeFile)) {
        typeList.addAccountType(AccountType("AT01", "Thanh toan", "VND", 0.5));
        typeList.addAccountType(AccountType("AT02", "Tiet kiem", "VND", 5.2));
        typeList.addAccountType(AccountType("AT03", "Ngoai te", "USD", 1.1));
    }
    accountList.loadFromFile(accountFile);

    std::vector<std::string> options = {
        "Hien thi danh sach loai tai khoan",
        "Them loai tai khoan moi",
        "Cap nhat loai tai khoan",
        "Hien thi danh sach tai khoan ngan hang",
        "Them tai khoan ngan hang moi",
        "Cap nhat tai khoan ngan hang",
        "Xoa tai khoan ngan hang",
        "Tim kiem tai khoan theo ten loai tai khoan",
        "Luu du lieu ra file va Thoat"
    };

    while (true) {
        std::cout << "\n=== QUAN LY TAI KHOAN NGAN HANG ===\n";
        int choice = Menu::getChoice(options);

        try {
            if (choice == 1) {
                std::cout << "\n--- DANH SACH LOAI TAI KHOAN ---\n";
                typeList.listAccountTypes();
            }
            else if (choice == 2) {
                std::string id, name, currency;
                double rate;
                std::cout << "Nhap ma loai tai khoan (ID): ";
                std::getline(std::cin >> std::ws, id);
                std::cout << "Nhap ten loai tai khoan: ";
                std::getline(std::cin >> std::ws, name);
                std::cout << "Nhap don vi tien te (VND/USD): ";
                std::getline(std::cin >> std::ws, currency);
                std::cout << "Nhap lai suat (%): ";
                std::cin >> rate;

                typeList.addAccountType(AccountType(id, name, currency, rate));
                std::cout << "Them loai tai khoan thanh cong!\n";
            }
            else if (choice == 3) {
                std::string oldId, newId, name, currency;
                double rate;
                std::cout << "Nhap ID loai tai khoan can sua: ";
                std::getline(std::cin >> std::ws, oldId);
                std::cout << "Nhap ID moi: ";
                std::getline(std::cin >> std::ws, newId);
                std::cout << "Nhap ten moi: ";
                std::getline(std::cin >> std::ws, name);
                std::cout << "Nhap don vi tien te moi: ";
                std::getline(std::cin >> std::ws, currency);
                std::cout << "Nhap lai suat moi: ";
                std::cin >> rate;

                if (typeList.updateAccountType(oldId, AccountType(newId, name, currency, rate))) {
                    std::cout << "Cap nhat thanh cong!\n";
                } else {
                    std::cout << "Khong tim thay ID hoac ID moi bi trung!\n";
                }
            }
            else if (choice == 4) {
                std::cout << "\n--- DANH SACH TAI KHOAN NGAN HANG ---\n";
                accountList.listBankAccounts();
            }
             else if (choice == 5) {
                std::string accId, ownerName, accNumber;
                double balance;
                std::cout << "Nhap ma tai khoan (Account ID): ";
                std::getline(std::cin >> std::ws, accId);
                AccountType selectedType = typeList.getUserChoice();
                std::cout << "Nhap ten chu tai khoan: ";
                std::getline(std::cin >> std::ws, ownerName);
                std::cout << "Nhap so tai khoan (Account Number): ";
                std::getline(std::cin >> std::ws, accNumber);
                std::cout << "Nhap so du ban dau: ";
                std::cin >> balance;

                accountList.addBankAccount(BankAccount(accId, selectedType, ownerName, accNumber, balance));
                std::cout << "Them tai khoan ngan hang thanh cong!\n";
            }
            else if (choice == 6) {
                std::string oldId, newId, ownerName, accNumber;
                double balance;
                std::cout << "Nhap ma tai khoan can cap nhat: ";
                std::getline(std::cin >> std::ws, oldId);
                std::cout << "Nhap ma tai khoan moi: ";
                std::getline(std::cin >> std::ws, newId);
                AccountType selectedType = typeList.getUserChoice();
                std::cout << "Nhap ten chu tai khoan moi: ";
                std::getline(std::cin >> std::ws, ownerName);
                std::cout << "Nhap so tai khoan moi (Account Number): ";
                std::getline(std::cin >> std::ws, accNumber);
                std::cout << "Nhap so du moi: ";
                std::cin >> balance;

                if (accountList.updateBankAccount(oldId, BankAccount(newId, selectedType, ownerName, accNumber, balance))) {
                    std::cout << "Cap nhat tai khoan thanh cong!\n";
                } else {
                    std::cout << "Cap nhat that bai (khong tim thay ID hoac ID moi bi trung)!\n";
                }
            }
            else if (choice == 7) {
                std::string accId;
                std::cout << "Nhap so tai khoan can xoa: ";
                std::getline(std::cin >> std::ws, accId);
                if (accountList.removeBankAccount(accId)) {
                    std::cout << "Xoa tai khoan thanh cong!\n";
                } else {
                    std::cout << "Khong tim thay so tai khoan!\n";
                }
            }
            else if (choice == 8) {
                std::string typeName;
                std::cout << "Nhap ten loai tai khoan can loc (VD: Tiet kiem): ";
                std::getline(std::cin >> std::ws, typeName);
                std::cout << "\n--- KET QUA LOC ---\n";
                accountList.printBasedAccountTypeName(typeName);
            }
            else if (choice == 9) {
                typeList.saveToFile(typeFile);
                accountList.saveToFile(accountFile);
                std::cout << "Da luu du lieu ra file. Tam biet!\n";
                break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Loi: " << e.what() << '\n';
        }
    }

    return 0;
}