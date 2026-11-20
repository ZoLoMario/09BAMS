/*
 * File: AccountType.h
 * Mo ta: Khai bao lop AccountType - mot loai tai khoan ngan hang
 *        (ma loai, ten loai, tien te, lai suat)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 * Nguoi sua: K26DTCN019 - Nguyen Quoc Khanh, 20/11/2026 (them screenString cho CN 1)
 * Nguoi duyet: K26DTCN115 - Luong Duc Trung
 * Ngay duyet:
 */
#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H

#include <string>

class AccountType {
private:
    std::string accountTypeID;  // ma loai: khong rong, khong trung
    std::string typeName;       // ten loai: khong rong
    std::string currency;       // tien te: khong rong
    double interestRate;        // lai suat (ty le, vd 0.045 = 4,5%/nam): > 0

public:
    AccountType(std::string id, std::string name,
                std::string curr, double rate);

    // Getters
    const std::string& getAccountTypeID() const;
    const std::string& getTypeName() const;
    const std::string& getCurrency() const;
    double getInterestRate() const;

    // Setters
    void setTypeName(const std::string& value);
    void setCurrency(const std::string& value);
    void setInterestRate(double value);

    // Chuoi ghi tep: "accountTypeID, typeName, currency, interestRate"
    std::string toString() const;
    // Chuoi hien thi mot dong trong bang (CN 1)
    std::string screenString() const;
    // So sanh theo typeName, trung thi theo accountTypeID
    int compareTo(const AccountType& other) const;
};

#endif
