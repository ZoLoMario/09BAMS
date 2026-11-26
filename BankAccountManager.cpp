/*
 * File: BankAccountManager.cpp
 * Mo ta: Cai dat BankAccountManager - vong lap menu, nap file, tich hop cac chuc nang
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet: 23/11/2026
 *
 * Ghi chu chung cho cac ham trong file (de khong lap lai o tung ham):
 *   Nguoi viet: K26DTCN100 - Vu Dang Khoi | Ngay viet: 18/11/2026
 *   Nguoi duyet: K26DTCN028 - Ngo Dinh Tai | Ngay duyet: 23/11/2026 | Ket qua: Hoan thanh
 *   Cac ham CN 2-9, 11 chi lo NHAP LIEU + THONG BAO; xu ly du lieu nam trong
 *   AccountTypeList / BankAccountList do thanh vien phu trach CN do viet.
 */
#include "BankAccountManager.h"
#include "Utils.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace {
const char* const ACCOUNT_TYPE_FILE = "accounttypes.txt";
const char* const BANK_ACCOUNT_FILE = "bankaccounts.txt";
const int MAX_CHOICE = 14;
}

/*
 * Ham: BankAccountManager (constructor)
 * Chuc nang: Gan bankAccountList voi accountTypeList, chua co thay doi chua luu
 */
BankAccountManager::BankAccountManager()
    : accountTypeList(), bankAccountList(accountTypeList),
      hasUnsavedTypes(false), hasUnsavedAccounts(false) {
}

/*
 * Ham: run
 * Chuc nang: Nap du lieu roi lap: hien menu -> nhap lua chon -> thuc hien.
 *            Loi trong mot chuc nang chi bao loi, khong lam dung chuong trinh.
 * Tra ve: 0 khi nguoi dung chon Exit
 */
int BankAccountManager::run() {
    loadData();
    bool isRunning = true;
    while (isRunning) {
        showMenu();
        const int choice = Utils::inputInt("Your choice: ", 0, MAX_CHOICE);
        try {
            isRunning = handleChoice(choice);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
    std::cout << "Goodbye!\n";
    return 0;
}

/*
 * Ham: loadData
 * Chuc nang: Nap accounttypes.txt TRUOC bankaccounts.txt (de giai quyet lien ket
 *            BankAccount.accountType). Bao loi ro neu thieu file.
 */
void BankAccountManager::loadData() {
    if (!accountTypeList.loadFromFile(ACCOUNT_TYPE_FILE)) {
        std::cout << "Error: cannot open " << ACCOUNT_TYPE_FILE
                  << ". Starting with an empty AccountType list.\n";
    }
    if (!bankAccountList.loadFromFile(BANK_ACCOUNT_FILE)) {
        std::cout << "Error: cannot open " << BANK_ACCOUNT_FILE
                  << ". Starting with an empty BankAccount list.\n";
    }
    std::cout << "Loaded " << accountTypeList.getAll().size() << " account type(s) and "
              << bankAccountList.getAll().size() << " bank account(s).\n";
}

/*
 * Ham: showMenu
 * Chuc nang: In menu theo dung thu tu va ten trong de bai (muc 3), them 3 chuc nang mo rong
 */
void BankAccountManager::showMenu() const {
    std::cout << "\n===== BANK ACCOUNT MANAGEMENT SYSTEM =====\n"
              << " 1. List all AccountTypes\n"
              << " 2. Add a new AccountType\n"
              << " 3. Search AccountType by ID\n"
              << " 4. Update AccountType\n"
              << " 5. Save AccountTypes to accounttypes.txt\n"
              << " 6. List all BankAccounts sorted by typeName\n"
              << " 7. Search BankAccounts by partial typeName\n"
              << " 8. Add a new BankAccount\n"
              << " 9. Remove BankAccount by ID\n"
              << "10. Update BankAccount by ID\n"
              << "11. Save BankAccounts to bankaccounts.txt\n"
              << "----- Extensions -----\n"
              << "12. Deposit money\n"
              << "13. Withdraw money\n"
              << "14. Show yearly interest\n"
              << " 0. Exit\n";
}

/*
 * Ham: handleChoice
 * Chuc nang: Goi chuc nang tuong ung voi lua chon
 * Tham so: choice - so tu 0 den MAX_CHOICE (Utils::inputInt da kiem tra)
 * Tra ve: false khi nguoi dung xac nhan thoat, true de tiep tuc
 */
bool BankAccountManager::handleChoice(int choice) {
    switch (choice) {
        case 1:  listAccountTypes();   break;
        case 2:  addAccountType();     break;
        case 3:  searchAccountType();  break;
        case 4:  updateAccountType();  break;
        case 5:  saveAccountTypes();   break;
        case 6:  listBankAccounts();   break;
        case 7:  searchBankAccounts(); break;
        case 8:  addBankAccount();     break;
        case 9:  removeBankAccount();  break;
        case 10: updateBankAccount();  break;
        case 11: saveBankAccounts();   break;
        case 12: depositMoney();       break;
        case 13: withdrawMoney();      break;
        case 14: showYearlyInterest(); break;
        case 0:  return !confirmExit();
        default: break;
    }
    return true;
}

/*
 * Ham: inputField
 * Chuc nang: Nhap mot truong chuoi: khong rong, khong co ',' (Utils kiem tra)
 *            va khong co '|' (dau phan cach trong file) - nhap sai thi nhap lai
 * Tham so: prompt - cau nhac
 * Tra ve: chuoi hop le
 */
std::string BankAccountManager::inputField(const std::string& prompt) const {
    while (true) {
        const std::string value = Utils::inputNonEmptyString(prompt);
        if (value.find('|') == std::string::npos) {
            return value;
        }
        std::cout << "[Error] Input cannot contain '|'. Please try again.\n";
    }
}

/*
 * Ham: chooseAccountType
 * Chuc nang: Cho nguoi dung chon AccountType tu danh sach; chon sai thi chon lai
 * Tra ve: AccountType da chon; nem std::runtime_error neu danh sach rong
 */
AccountType BankAccountManager::chooseAccountType() const {
    if (accountTypeList.getAll().empty()) {
        throw std::runtime_error("No AccountType available. Please add one first.");
    }
    while (true) {
        std::cout << "--- Choose an AccountType ---\n";
        try {
            return accountTypeList.getUserChoice();
        } catch (const std::runtime_error& e) {
            std::cout << "[Error] " << e.what() << " Please try again.\n";
        }
    }
}

/* Ham: listAccountTypes (CN 1) - Chuc nang: hien toan bo AccountType */
void BankAccountManager::listAccountTypes() const {
    std::cout << "\n--- ACCOUNT TYPES ---\n";
    accountTypeList.listAccountTypes();
}

/*
 * Ham: addAccountType (CN 2)
 * Chuc nang: Nhap AccountType moi; ma trung/rong, ten rong, lai suat sai -> nhap lai
 */
void BankAccountManager::addAccountType() {
    std::string id = inputField("Enter accountTypeID: ");
    while (accountTypeList.searchID(id) >= 0) {
        std::cout << "[Error] ID already exists. Please try again.\n";
        id = inputField("Enter accountTypeID: ");
    }
    const std::string name = inputField("Enter typeName: ");
    const std::string currency = inputField("Enter currency: ");
    const double rate = Utils::inputDouble("Enter interestRate (e.g. 0.045): ", 0, true);
    accountTypeList.addAccountType(AccountType(id, name, currency, rate));
    hasUnsavedTypes = true;
    std::cout << "AccountType added.\n";
}

/* Ham: searchAccountType (CN 3) - Chuc nang: tim AccountType theo ma */
void BankAccountManager::searchAccountType() const {
    const std::string id = inputField("Enter accountTypeID to search: ");
    const AccountType* found = accountTypeList.findByID(id);
    if (found == nullptr) {
        std::cout << "AccountType " << id << " not found.\n";
        return;
    }
    std::cout << "Found: " << found->toString() << '\n';
}

/*
 * Ham: updateAccountType (CN 4)
 * Chuc nang: Sua AccountType theo ma; ma moi khong duoc trung ma khac.
 *            Dong bo lai cac BankAccount dang dung loai nay (syncAccountType).
 */
void BankAccountManager::updateAccountType() {
    const std::string oldId = inputField("Enter accountTypeID to update: ");
    const AccountType* current = accountTypeList.findByID(oldId);
    if (current == nullptr) {
        std::cout << "Error: AccountType " << oldId << " not found.\n";
        return;
    }
    std::cout << "Current: " << current->toString() << '\n';
    // Ma dang luu (vd "T01"): nguoi dung co the go "t01" vi searchID khong phan biet hoa/thuong
    const std::string storedId = current->getAccountTypeID();
    std::string newId = inputField("Enter new accountTypeID: ");
    while (accountTypeList.searchID(newId) >= 0 && accountTypeList.findByID(newId) != current) {
        std::cout << "[Error] ID already exists. Please try again.\n";
        newId = inputField("Enter new accountTypeID: ");
    }
    const std::string name = inputField("Enter new typeName: ");
    const std::string currency = inputField("Enter new currency: ");
    const double rate = Utils::inputDouble("Enter new interestRate: ", 0, true);
    const AccountType updated(newId, name, currency, rate);
    if (!accountTypeList.updateAccountType(oldId, updated)) {
        std::cout << "Error: update failed.\n";
        return;
    }
    bankAccountList.syncAccountType(storedId, updated);
    hasUnsavedTypes = true;
    hasUnsavedAccounts = true;
    std::cout << "AccountType updated.\n";
}

/* Ham: saveAccountTypes (CN 5) - Chuc nang: ghi danh sach AccountType ra file */
void BankAccountManager::saveAccountTypes() {
    if (!accountTypeList.saveToFile(ACCOUNT_TYPE_FILE)) {
        std::cout << "Error: cannot write " << ACCOUNT_TYPE_FILE << ".\n";
        return;
    }
    hasUnsavedTypes = false;
    std::cout << "Saved AccountTypes to " << ACCOUNT_TYPE_FILE << ".\n";
}

/* Ham: listBankAccounts (CN 6) - Chuc nang: hien BankAccount theo typeName roi accountID */
void BankAccountManager::listBankAccounts() const {
    std::cout << "\n--- BANK ACCOUNTS (ID | typeName | owner | number | balance) ---\n";
    bankAccountList.listBankAccounts();
}

/* Ham: searchBankAccounts (CN 7) - Chuc nang: loc BankAccount theo typeName */
void BankAccountManager::searchBankAccounts() const {
    const std::string keyword = inputField("Enter (part of) typeName: ");
    std::cout << "\n--- SEARCH RESULT ---\n";
    bankAccountList.printBasedAccountTypeName(keyword);
}

/*
 * Ham: addBankAccount (CN 8)
 * Chuc nang: Nhap BankAccount moi, chon AccountType tu menu; ma trung -> nhap lai,
 *            so du am -> nhap lai
 */
void BankAccountManager::addBankAccount() {
    const AccountType type = chooseAccountType();
    std::string id = inputField("Enter accountID: ");
    while (bankAccountList.searchID(id) >= 0) {
        std::cout << "[Error] ID already exists. Please try again.\n";
        id = inputField("Enter accountID: ");
    }
    const std::string owner = inputField("Enter ownerName: ");
    const std::string number = inputField("Enter accountNumber: ");
    const double balance = Utils::inputDouble("Enter balance: ", 0, false);
    bankAccountList.addBankAccount(BankAccount(id, type, owner, number, balance));
    hasUnsavedAccounts = true;
    std::cout << "BankAccount added.\n";
}

/* Ham: removeBankAccount (CN 9) - Chuc nang: xoa BankAccount theo ma */
void BankAccountManager::removeBankAccount() {
    const std::string id = inputField("Enter accountID to remove: ");
    if (!bankAccountList.removeBankAccount(id)) {
        std::cout << "Error: accountID " << id << " not found.\n";
        return;
    }
    hasUnsavedAccounts = true;
    std::cout << "BankAccount " << id << " removed.\n";
}

/*
 * Ham: updateBankAccount (CN 10)
 * Chuc nang: Sua BankAccount theo ma. Ma khong ton tai -> bao loi, ve menu.
 *            Ma moi trung ma khac, so du am, chon loai sai -> nhap lai.
 *            BankAccountList::updateBankAccount kiem tra rang buoc lan cuoi.
 */
void BankAccountManager::updateBankAccount() {
    const std::string oldId = inputField("Enter accountID to update: ");
    const BankAccount* current = bankAccountList.findByID(oldId);
    if (current == nullptr) {
        std::cout << "Error: accountID " << oldId << " not found.\n";
        return;
    }
    std::cout << "Current: " << current->screenString() << '\n';
    std::string newId = inputField("Enter new accountID: ");
    while (newId != oldId && bankAccountList.searchID(newId) >= 0) {
        std::cout << "[Error] ID already exists. Please try again.\n";
        newId = inputField("Enter new accountID: ");
    }
    const AccountType type = chooseAccountType();
    const std::string owner = inputField("Enter new ownerName: ");
    const std::string number = inputField("Enter new accountNumber: ");
    const double balance = Utils::inputDouble("Enter new balance: ", 0, false);
    bankAccountList.updateBankAccount(oldId, BankAccount(newId, type, owner, number, balance));
    hasUnsavedAccounts = true;
    std::cout << "BankAccount updated.\n";
}

/* Ham: saveBankAccounts (CN 11) - Chuc nang: ghi danh sach BankAccount ra file */
void BankAccountManager::saveBankAccounts() {
    if (!bankAccountList.saveToFile(BANK_ACCOUNT_FILE)) {
        std::cout << "Error: cannot write " << BANK_ACCOUNT_FILE << ".\n";
        return;
    }
    hasUnsavedAccounts = false;
    std::cout << "Saved BankAccounts to " << BANK_ACCOUNT_FILE << ".\n";
}

/* Ham: depositMoney (mo rong 12) - Chuc nang: nap tien (> 0) vao tai khoan */
void BankAccountManager::depositMoney() {
    const std::string id = inputField("Enter accountID: ");
    if (bankAccountList.findByID(id) == nullptr) {
        std::cout << "Error: accountID " << id << " not found.\n";
        return;
    }
    const double amount = Utils::inputDouble("Enter amount to deposit: ", 0, true);
    bankAccountList.deposit(id, amount);
    hasUnsavedAccounts = true;
    std::cout << "New balance: " << bankAccountList.findByID(id)->screenString() << '\n';
}

/* Ham: withdrawMoney (mo rong 13) - Chuc nang: rut tien, khong vuot qua so du */
void BankAccountManager::withdrawMoney() {
    const std::string id = inputField("Enter accountID: ");
    const BankAccount* account = bankAccountList.findByID(id);
    if (account == nullptr) {
        std::cout << "Error: accountID " << id << " not found.\n";
        return;
    }
    std::cout << "Current: " << account->screenString() << '\n';
    const double amount = Utils::inputDouble("Enter amount to withdraw: ", 0, true);
    bankAccountList.withdraw(id, amount);
    hasUnsavedAccounts = true;
    std::cout << "New balance: " << bankAccountList.findByID(id)->screenString() << '\n';
}

/*
 * Ham: showYearlyInterest (mo rong 14)
 * Chuc nang: Tinh tien lai 1 nam = balance * interestRate cho tung tai khoan.
 *            interestRate la ty le theo de bai (0.045 = 4.5%). Chi hien thi,
 *            khong sua so du.
 */
void BankAccountManager::showYearlyInterest() const {
    std::cout << "\n--- YEARLY INTEREST (balance x interestRate) ---\n";
    std::cout << std::fixed << std::setprecision(2);
    for (const BankAccount& account : bankAccountList.getAll()) {
        const double rate = account.getAccountType().getInterestRate();
        std::cout << account.getAccountID() << " | " << account.getOwnerName()
                  << " | balance " << account.getBalance() << " | rate " << rate * 100
                  << "% | interest " << account.getBalance() * rate << '\n';
    }
    std::cout.unsetf(std::ios::floatfield);
}

/*
 * Ham: confirmExit (0)
 * Chuc nang: De bai yeu cau Exit KHONG tu ghi de du lieu. Neu con thay doi chua
 *            luu (CN 5 / CN 11) thi canh bao va hoi lai.
 * Tra ve: true neu thoat
 */
bool BankAccountManager::confirmExit() const {
    if (!hasUnsavedTypes && !hasUnsavedAccounts) {
        return true;
    }
    std::cout << "Warning: you have unsaved changes"
              << (hasUnsavedTypes ? " [AccountTypes: use 5]" : "")
              << (hasUnsavedAccounts ? " [BankAccounts: use 11]" : "") << ".\n";
    while (true) {
        std::cout << "Exit without saving? (y/n): ";
        std::string answer;
        if (!std::getline(std::cin, answer)) {
            return true;
        }
        answer = Utils::toLower(Utils::trim(answer));
        if (answer == "y" || answer == "n") {
            return answer == "y";
        }
        std::cout << "[Error] Please enter y or n.\n";
    }
}
