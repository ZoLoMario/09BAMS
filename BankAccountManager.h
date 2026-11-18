/*
 * File: BankAccountManager.h
 * Mo ta: Lop dieu phoi chuong trinh (BankAccountManager trong UML): nap 2 file
 *        du lieu, hien menu 11 chuc nang + mo rong + Exit, goi AccountTypeList
 *        va BankAccountList. Exit khong tu ghi de file.
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:
 */
#ifndef BANK_ACCOUNT_MANAGER_H
#define BANK_ACCOUNT_MANAGER_H

#include "AccountTypeList.h"
#include "BankAccountList.h"
#include <string>

class BankAccountManager {
private:
    // accountTypeList phai khai bao TRUOC bankAccountList vi bankAccountList giu tham chieu toi no
    AccountTypeList accountTypeList;
    BankAccountList bankAccountList;
    bool hasUnsavedTypes;
    bool hasUnsavedAccounts;

    void loadData();
    void showMenu() const;
    bool handleChoice(int choice);
    std::string inputField(const std::string& prompt) const;
    AccountType chooseAccountType() const;

    void listAccountTypes() const;      // CN 1
    void addAccountType();              // CN 2
    void searchAccountType() const;     // CN 3
    void updateAccountType();           // CN 4
    void saveAccountTypes();            // CN 5
    void listBankAccounts() const;      // CN 6
    void searchBankAccounts() const;    // CN 7
    void addBankAccount();              // CN 8
    void removeBankAccount();           // CN 9
    void updateBankAccount();           // CN 10
    void saveBankAccounts();            // CN 11
    void depositMoney();                // mo rong 12
    void withdrawMoney();               // mo rong 13
    void showYearlyInterest() const;    // mo rong 14
    bool confirmExit() const;           // 0

public:
    BankAccountManager();
    int run();
};

#endif
