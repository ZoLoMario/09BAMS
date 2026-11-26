/*
 * File: BankAccount.cpp
 * Mo ta: Quan ly danh sach BankAccount (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 17/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat. Gop y: dong "Mo ta" o tren nen la "Cai dat lop BankAccount - mot
 *   tai khoan"; screenString/screenHeader chua duoc listBankAccounts (CN 6) goi.
 */
#include "BankAccount.h"
#include "Utils.h"
#include <iomanip>
#include <sstream>

// Do rong cac cot khi in ra man hinh bang screenString()
const int ID_WIDTH = 8;
const int TYPE_WIDTH = 12;
const int OWNER_WIDTH = 22;
const int NUMBER_WIDTH = 12;
const int BALANCE_WIDTH = 18;

/*
 * Ham: BankAccount (constructor)
 * Chuc nang: Tao tai khoan voi day du thong tin
 * Tham so: id - accountID; type - AccountType cua tai khoan; owner - ownerName;
 *          number - accountNumber; amount - balance ban dau
 * Tra ve: khong
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 17/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
BankAccount::BankAccount(const std::string& id, const AccountType& type,
                         const std::string& owner, const std::string& number, double amount)
    : accountID(id), accountType(type), ownerName(owner),
      accountNumber(number), balance(amount) {}

/*
 * Ham: getAccountID, getAccountType, getOwnerName, getAccountNumber, getBalance
 * Chuc nang: Tra ve gia tri thuoc tinh tuong ung (chi doc)
 * Tham so: khong
 * Tra ve: gia tri thuoc tinh
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 17/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
const std::string& BankAccount::getAccountID() const { return accountID; }
const AccountType& BankAccount::getAccountType() const { return accountType; }
const std::string& BankAccount::getOwnerName() const { return ownerName; }
const std::string& BankAccount::getAccountNumber() const { return accountNumber; }
double BankAccount::getBalance() const { return balance; }

/*
 * Ham: setAccountType, setOwnerName, setAccountNumber, setBalance
 * Chuc nang: Gan gia tri moi cho thuoc tinh tuong ung
 *            (kiem tra rang buoc do BankAccountList/BankAccountManager thuc hien)
 * Tham so: value - gia tri moi
 * Tra ve: khong
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 17/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
void BankAccount::setAccountType(const AccountType& value) { accountType = value; }
void BankAccount::setOwnerName(const std::string& value) { ownerName = value; }
void BankAccount::setAccountNumber(const std::string& value) { accountNumber = value; }
void BankAccount::setBalance(double value) { balance = value; }

/*
 * Ham: toString
 * Chuc nang: Tao dong du lieu de GHI TEP bankaccounts.txt, dung dinh dang de bai:
 *            accountID, accountTypeID, ownerName, accountNumber, balance
 *            (ghi MA loai, khong ghi typeName, de loadFromFile tim lai duoc AccountType).
 *            Hien thi ra man hinh thi dung screenString().
 * Tham so: khong
 * Tra ve: chuoi mot dong, balance dang so thuong (std::fixed) 2 chu so thap phan,
 *         khong bao gio ra dang 1.2e+07
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 17/11/2026; 26/11/2026 doi sang dinh dang ghi tep
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
std::string BankAccount::toString() const {
    std::ostringstream out;
    out << accountID << ", " << accountType.getAccountTypeID() << ", " << ownerName
        << ", " << accountNumber << ", " << std::fixed << std::setprecision(2) << balance;
    return out.str();
}

/*
 * Ham: screenString
 * Chuc nang: Tra ve mot dong de in danh sach ra man hinh, cac cot can deu;
 *            balance can phai, 2 chu so thap phan, kem don vi tien te cua AccountType
 * Tham so: khong
 * Tra ve: chuoi da can cot
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 23/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
std::string BankAccount::screenString() const {
    std::ostringstream out;
    out << std::left << std::setw(ID_WIDTH) << accountID
        << std::setw(TYPE_WIDTH) << accountType.getTypeName()
        << std::setw(OWNER_WIDTH) << ownerName
        << std::setw(NUMBER_WIDTH) << accountNumber
        << std::right << std::setw(BALANCE_WIDTH) << std::fixed << std::setprecision(2)
        << balance << ' ' << accountType.getCurrency();
    return out.str();
}

/*
 * Ham: screenHeader
 * Chuc nang: Tra ve dong tieu de cot + dong gach ngang cho bang screenString(),
 *            dung chung hang do rong cot nen tieu de luon thang hang voi du lieu
 * Tham so: khong
 * Tra ve: chuoi 2 dong (tieu de, gach ngang), khong co '\n' cuoi
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 23/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
std::string BankAccount::screenHeader() {
    std::ostringstream out;
    out << std::left << std::setw(ID_WIDTH) << "ID"
        << std::setw(TYPE_WIDTH) << "Type"
        << std::setw(OWNER_WIDTH) << "Owner"
        << std::setw(NUMBER_WIDTH) << "Number"
        << std::right << std::setw(BALANCE_WIDTH) << "Balance" << " Currency" << '\n'
        << std::string(ID_WIDTH + TYPE_WIDTH + OWNER_WIDTH + NUMBER_WIDTH + BALANCE_WIDTH + 9, '-');
    return out.str();
}

/*
 * Ham: compareTo
 * Chuc nang: So sanh 2 tai khoan theo typeName, neu trung thi so sanh accountID.
 *            Khong phan biet hoa/thuong ("savings" va "Savings" xep cung nhom).
 * Tham so: other - tai khoan can so sanh
 * Tra ve: < 0 neu dung truoc other, 0 neu bang, > 0 neu dung sau
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 17/11/2026; 23/11/2026 doi sang khong phan biet hoa/thuong
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
int BankAccount::compareTo(const BankAccount& other) const {
    const std::string typeName = Utils::toLower(accountType.getTypeName());
    const std::string otherTypeName = Utils::toLower(other.accountType.getTypeName());
    const int typeCompare = typeName.compare(otherTypeName);
    if (typeCompare != 0) {
        return typeCompare;
    }
    return Utils::toLower(accountID).compare(Utils::toLower(other.accountID));
}

/*
 * Ham: operator<
 * Chuc nang: Thu tu sap xep cho std::sort: typeName tang dan, trung thi accountID tang dan
 * Tham so: other - tai khoan can so sanh
 * Tra ve: true neu tai khoan nay dung truoc other
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 23/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
bool BankAccount::operator<(const BankAccount& other) const {
    return compareTo(other) < 0;
}

/*
 * Ham: operator==
 * Chuc nang: Hai tai khoan bang nhau khi trung accountID (khong phan biet hoa/thuong)
 * Tham so: other - tai khoan can so sanh
 * Tra ve: true neu cung accountID
 * Nguoi viet: K26DTCN107 - Nguyen Thanh Phong
 * Ngay viet: 17/11/2026
 * Nguoi duyet: K26DTCN089 - Vu Trong Hanh
 *   (K26DTCN100 - Vu Dang Khoi duyet thay, Hanh ban da xin phep nhom)
 * Ngay duyet: 25/11/2026
 * Ket qua: Dat
 */
bool BankAccount::operator==(const BankAccount& other) const {
    return Utils::toLower(accountID) == Utils::toLower(other.accountID);
}
