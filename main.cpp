#include <iostream>
#include <vector>
#include <string>
#include "AccountTypeList.h"
#include "BankAccountList.h"
#include "Utils.h"

class BankAccountManager {
public:
    static int run() {
        const std::string TYPE_FILE = "accounttypes.txt";
        const std::string ACCOUNT_FILE = "bankaccounts.txt";

        AccountTypeList typeList;
        BankAccountList accountList(typeList);

        std::cout << "Loading data files...\n";
        typeList.loadFromFile(TYPE_FILE);
        accountList.loadFromFile(ACCOUNT_FILE);

        int choice = -1;
        do {
            std::cout << "\n================ BANK ACCOUNT MANAGEMENT ================\n";
            std::cout << "1.  List all AccountTypes\n";
            std::cout << "2.  Add a new AccountType\n";
            std::cout << "3.  Search AccountType by ID\n";
            std::cout << "4.  Update AccountType\n";
            std::cout << "5.  Save AccountTypes to accounttypes.txt\n";
            std::cout << "6.  List all BankAccounts sorted by typeName\n";
            std::cout << "7.  Search BankAccounts by partial typeName\n";
            std::cout << "8.  Add a new BankAccount\n";
            std::cout << "9.  Remove BankAccount by ID\n";
            std::cout << "10. Update BankAccount by ID\n";
            std::cout << "11. Save BankAccounts to bankaccounts.txt\n";
            std::cout << "0.  Exit\n";
            std::cout << "=========================================================\n";

            choice = Utils::inputInt("Enter your choice (0-11): ", 0, 11);

            switch (choice) {
                case 1:
                    typeList.listAccountTypes();
                    break;
                case 2:
                    typeList.addAccountType();
                    break;
                case 3:
                    typeList.searchAccountTypeByID();
                    break;
                case 4:
                    typeList.updateAccountType();
                    break;
                case 5:
                    typeList.saveToFile(TYPE_FILE);
                    break;
                case 6:
                    accountList.listBankAccounts();
                    break;
                case 7:
                    accountList.printBasedAccountTypeName();
                    break;
                case 8:
                    accountList.addBankAccount();
                    break;
                case 9:
                    accountList.removeBankAccount();
                    break;
                case 10:
                    accountList.updateBankAccount();
                    break;
                case 11:
                    accountList.saveToFile(ACCOUNT_FILE);
                    break;
                case 0:
                    std::cout << "Exiting program without auto-saving. Goodbye!\n";
                    break;
            }
        } while (choice != 0);

        return 0;
    }
};

int main() {
    return BankAccountManager::run();
}