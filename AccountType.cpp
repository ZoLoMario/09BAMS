/*
 * File: AccountType.cpp
 * Mo ta: Cai dat lop AccountType - mot loai tai khoan ngan hang
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 * Nguoi sua: K26DTCN019 - Nguyen Quoc Khanh, 20/11/2026
 *            (sua toString giu du chu so lai suat, them screenString)
 * Nguoi duyet: K26DTCN115 - Luong Duc Trung
 * Ngay duyet:
 *
 * Ghi chu chung cho constructor, getter, setter:
 *   Nguoi viet: K26DTCN089 - Vu Trong Hanh | Ngay viet: 16/11/2026
 */

//Khai bao thu vien
#include "AccountType.h"
#include <sstream>
#include <iomanip>
#include <utility>
using namespace std;

//Ham khoi tao co tham so
AccountType::AccountType(string id, string name, string curr, double rate)
    : accountTypeID(move(id)), typeName(move(name)),
      currency(move(curr)), interestRate(rate) {}

//Cac ham getter
const string& AccountType::getAccountTypeID() const { return accountTypeID; }
const string& AccountType::getTypeName() const { return typeName; }
const string& AccountType::getCurrency() const { return currency; }
double AccountType::getInterestRate() const { return interestRate; }

//Cac ham setter
void AccountType::setTypeName(const string& value) { typeName = value; }
void AccountType::setCurrency(const string& value) { currency = value; }
void AccountType::setInterestRate(double value) { interestRate = value; }

/*
 * Ham: toString
 * Chuc nang: Tao chuoi ghi tep theo dinh dang cua de bai, cac truong cach nhau
 *            bang dau phay. Lai suat ghi day du chu so (0.045 giu nguyen 0.045,
 *            khong lam tron thanh 0.05 nhu ban cu dung setprecision(2)).
 * Tham so: khong
 * Tra ve: chuoi "accountTypeID, typeName, currency, interestRate"
 * Nguoi viet: K26DTCN019 - Nguyen Quoc Khanh
 * Ngay viet: 20/11/2026
 * Nguoi duyet: K26DTCN115 - Luong Duc Trung
 * Ngay duyet:
 * Ket qua:
 */
string AccountType::toString() const {
    ostringstream out;
    //Do chinh xac mac dinh (6 chu so co nghia) du cho lai suat 3-4 chu so thap phan
    out << accountTypeID << ", " << typeName << ", " << currency
        << ", " << interestRate;
    return out.str();
}

/*
 * Ham: screenString
 * Chuc nang: Tao mot dong cua bang hien thi CN 1, can cot bang setw.
 *            Lai suat in 4 chu so thap phan va them cot phan tram cho de doc.
 * Tham so: khong
 * Tra ve: chuoi dang "| T01      | Savings         | VND      |   0.0450 |   4.50% |"
 * Nguoi viet: K26DTCN019 - Nguyen Quoc Khanh
 * Ngay viet: 20/11/2026
 * Nguoi duyet: K26DTCN115 - Luong Duc Trung
 * Ngay duyet:
 * Ket qua:
 */
string AccountType::screenString() const {
    ostringstream out;
    out << "| " << left << setw(9) << accountTypeID
        << "| " << setw(16) << typeName
        << "| " << setw(9) << currency
        << "| " << right << fixed << setprecision(4) << setw(12) << interestRate
        << " | " << setprecision(2) << setw(7) << interestRate * 100 << "% |";
    return out.str();
}

//So sanh theo typeName, trung thi theo accountTypeID
int AccountType::compareTo(const AccountType& other) const {
    if (typeName < other.typeName) return -1;
    if (typeName > other.typeName) return 1;
    return accountTypeID.compare(other.accountTypeID);
}
