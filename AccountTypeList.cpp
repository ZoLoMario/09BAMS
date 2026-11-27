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
#include "Utils.h"


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

/*
 * Ham: saveToFile (CN 5)
 * Chuc nang: Ghi toan bo danh sach AccountType ra file theo dinh dang cua de bai
 *            (dau ','), dong dau la dong chu thich ten cot (loadFromFile bo qua
 *            dong bat dau bang '#'). Dung ofstream (RAII) nen file tu dong dong.
 * Tham so: filename - ten file (accounttypes.txt)
 * Tra ve: false neu khong mo duoc file hoac ghi loi, nguoc lai true
 * Nguoi viet: K26DTCN019 - Nguyen Quoc Khanh
 * Ngay viet: 20/11/2026
 * Nguoi duyet: K26DTCN115 - Luong Duc Trung
 * Ngay duyet:
 * Ket qua:
 */
bool AccountTypeList::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;
    out << "# accountTypeID, typeName, currency, interestRate\n";
    for (const auto& t : accountTypes)
        out << t.toString() << '\n';
    //Kiem tra trang thai luong sau khi ghi (vd o dia day)
    return static_cast<bool>(out);
}

/*
 * Ham: searchID (CN 3)
 * Chuc nang: Tim vi tri AccountType theo ma, KHONG phan biet hoa/thuong
 *            (nhap "t01" van tim ra "T01")
 * Tham so: id - ma can tim
 * Tra ve: vi tri trong danh sach; -1 neu khong co
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 * Nguoi sua: K26DTCN100 - Vu Dang Khoi, 25/11/2026 (ho tro Hanh)
 * Nguoi duyet: K26DTCN019 - Nguyen Quoc Khanh
 * Ngay duyet: 27/11/2026
 * Ket qua: Dat
 */
int AccountTypeList::searchID(const std::string& id) const {
    const std::string key = Utils::toLower(Utils::trim(id));
    for (std::size_t i = 0; i < accountTypes.size(); ++i) {
        if (Utils::toLower(accountTypes[i].getAccountTypeID()) == key) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

/*
 * Ham: findByID (CN 3, CN 4)
 * Chuc nang: Tra con tro toi AccountType co ma id (dung searchID)
 * Tham so: id - ma can tim
 * Tra ve: con tro; nullptr neu khong co
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 * Nguoi sua: K26DTCN100 - Vu Dang Khoi, 25/11/2026 (ho tro Hanh)
 * Nguoi duyet: K26DTCN019 - Nguyen Quoc Khanh
 * Ngay duyet: 27/11/2026
 * Ket qua: Dat
 */
AccountType* AccountTypeList::findByID(const std::string& id) {
    const int i = searchID(id);
    return i < 0 ? nullptr : &accountTypes[static_cast<std::size_t>(i)];
}
const AccountType* AccountTypeList::findByID(const std::string& id) const {
    const int i = searchID(id);
    return i < 0 ? nullptr : &accountTypes[static_cast<std::size_t>(i)];
}

/*
 * Ham: getUserChoice (dung cho CN 8, CN 10)
 * Chuc nang: Hien bang AccountType, cho nguoi dung nhap ma loai de chon
 * Tham so: khong
 * Tra ve: AccountType da chon; nem std::runtime_error neu danh sach rong
 *         hoac ma khong ton tai (BankAccountManager bat loi va cho chon lai)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 * Nguoi sua: K26DTCN100 - Vu Dang Khoi, 25/11/2026 (ho tro Hanh)
 * Nguoi duyet: K26DTCN019 - Nguyen Quoc Khanh
 * Ngay duyet: 27/11/2026
 * Ket qua: Dat. Gop y: neu het dau vao (Ctrl+Z / EOF) thi id rong, ham nem loi
 *   'not found' va chooseAccountType hoi lai mai (lap vo han); nen kiem tra
 *   std::cin sau getline va nem loi rieng khi het dau vao.
 */
AccountType AccountTypeList::getUserChoice() const {
    if (accountTypes.empty()) {
        throw std::runtime_error("AccountType list is empty.");
    }
    listAccountTypes();
    std::string id;
    std::cout << "Enter accountTypeID: ";
    std::getline(std::cin >> std::ws, id);
    const AccountType* found = findByID(id);
    if (!found) {
        throw std::runtime_error("AccountType ID not found.");
    }
    return *found;
}

/*
 * Ham: addAccountType (CN 2)
 * Chuc nang: Them AccountType moi vao cuoi danh sach; ma trung (khong phan
 *            biet hoa/thuong) thi nem loi
 * Tham so: type - AccountType da nhap va kiem tra o BankAccountManager
 * Tra ve: khong; nem std::invalid_argument neu ma da ton tai
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 * Nguoi sua: K26DTCN100 - Vu Dang Khoi, 25/11/2026 (ho tro Hanh)
 * Nguoi duyet: K26DTCN019 - Nguyen Quoc Khanh
 * Ngay duyet: 27/11/2026
 * Ket qua: Dat
 */
void AccountTypeList::addAccountType(const AccountType& type) {
    if (searchID(type.getAccountTypeID()) >= 0) {
        throw std::invalid_argument("AccountType ID already exists.");
    }
    accountTypes.push_back(type);
}

/*
 * Ham: updateAccountType (CN 4)
 * Chuc nang: Sua AccountType co ma id; ma moi khong duoc trung ma cua loai KHAC
 * Tham so: id - ma loai can sua; updated - du lieu moi
 * Tra ve: true neu sua duoc; false neu khong co ma id hoac ma moi bi trung
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 * Nguoi sua: K26DTCN100 - Vu Dang Khoi, 25/11/2026 (ho tro Hanh)
 * Nguoi duyet: K26DTCN019 - Nguyen Quoc Khanh
 * Ngay duyet: 27/11/2026
 * Ket qua: Dat
 */
bool AccountTypeList::updateAccountType(const std::string& id, const AccountType& updated) {
    AccountType* current = findByID(id);
    if (!current) {
        return false;
    }
    const int other = searchID(updated.getAccountTypeID());
    if (other >= 0 && &accountTypes[static_cast<std::size_t>(other)] != current) {
        return false;
    }
    *current = updated;
    return true;
}

/*
 * Ham: listAccountTypes (CN 1)
 * Chuc nang: Hien thi toan bo danh muc AccountType dang bang (tieu de, tung dong,
 *            tong so). Danh sach rong thi bao "Danh sach AccountType trong!".
 *            Ham nay cung duoc getUserChoice dung khi chon loai tai khoan.
 * Tham so: khong
 * Tra ve: khong
 * Nguoi viet: K26DTCN019 - Nguyen Quoc Khanh
 * Ngay viet: 20/11/2026
 * Nguoi duyet: K26DTCN115 - Luong Duc Trung
 * Ngay duyet:
 * Ket qua:
 */
void AccountTypeList::listAccountTypes() const {
    if (accountTypes.empty()) {
        std::cout << "Danh sach AccountType trong!\n";
        return;
    }
    const std::string border =
        "+----------+-----------------+----------+--------------+----------+";
    std::cout << border << '\n'
              << "| TypeID   | TypeName        | Currency | InterestRate |  Rate(%) |\n"
              << border << '\n';
    for (const auto& t : accountTypes)
        std::cout << t.screenString() << '\n';
    std::cout << border << '\n'
              << "Tong so: " << accountTypes.size() << " AccountType.\n";
}

const std::vector<AccountType>& AccountTypeList::getAll() const { return accountTypes; }
