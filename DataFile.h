/*
 * File: DataFile.h
 * Mo ta: Ham dung chung cho 2 ham loadFromFile: tach mot dong du lieu thanh cac
 *        truong, bao loi dong sai dinh dang. Chap nhan ca dau ',' (theo de bai)
 *        va dau '|' (dinh dang saveToFile hien tai) de nhom chua phai sua 2 file.
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 */
#ifndef DATA_FILE_H
#define DATA_FILE_H

#include <cctype>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace DataFile {

/*
 * Ham: trim
 * Chuc nang: Xoa khoang trang, tab, xuong dong o dau va cuoi chuoi
 * Tham so: text - chuoi can xu ly
 * Tra ve: chuoi da cat
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
inline std::string trim(const std::string& text) {
    const char* SPACES = " \t\r\n";
    const std::string::size_type first = text.find_first_not_of(SPACES);
    if (first == std::string::npos) {
        return "";
    }
    const std::string::size_type last = text.find_last_not_of(SPACES);
    return text.substr(first, last - first + 1);
}

/*
 * Ham: isSkippableLine
 * Chuc nang: Dong trong hoac dong chu thich (bat dau bang '#') thi bo qua
 * Tham so: line - mot dong doc tu file
 * Tra ve: true neu bo qua duoc
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
inline bool isSkippableLine(const std::string& line) {
    const std::string content = trim(line);
    return content.empty() || content[0] == '#';
}

/*
 * Ham: isHeaderLine
 * Chuc nang: Nhan dien dong tieu de khong co dau '#', vd "accountTypeID, typeName, ..."
 * Tham so: line - dong doc tu file; firstFieldName - ten cot dau tien
 * Tra ve: true neu dong bat dau bang ten cot dau tien
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
inline bool isHeaderLine(const std::string& line, const std::string& firstFieldName) {
    return trim(line).compare(0, firstFieldName.size(), firstFieldName) == 0;
}

/*
 * Ham: splitRecord
 * Chuc nang: Tach mot dong thanh dung expectedCount truong (da trim).
 *            Dong co dau '|' thi tach theo '|', nguoc lai tach theo ','.
 * Tham so: line - dong du lieu; expectedCount - so truong can co;
 *          fields - ket qua; error - ly do sai (neu co)
 * Tra ve: true neu dung so truong va khong truong nao rong
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
inline bool splitRecord(const std::string& line, std::size_t expectedCount,
                        std::vector<std::string>& fields, std::string& error) {
    const char delimiter = (line.find('|') != std::string::npos) ? '|' : ',';
    fields.clear();
    std::istringstream stream(line);
    std::string token;
    while (std::getline(stream, token, delimiter)) {
        fields.push_back(trim(token));
    }
    if (fields.size() != expectedCount) {
        std::ostringstream message;
        message << "expected " << expectedCount << " fields but found " << fields.size();
        error = message.str();
        return false;
    }
    for (std::size_t i = 0; i < fields.size(); i++) {
        if (fields[i].empty()) {
            std::ostringstream message;
            message << "field " << (i + 1) << " is empty";
            error = message.str();
            return false;
        }
    }
    return true;
}

/*
 * Ham: parseNumber
 * Chuc nang: Doi chuoi sang so thuc, khong chap nhan ky tu thua (vd "12abc")
 * Tham so: text - chuoi so; value - ket qua
 * Tra ve: true neu doi duoc
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 18/11/2026
 * Nguoi duyet: K26DTCN028 - Ngo Dinh Tai
 * Ngay duyet:23/11/2026
 * Ket qua:Hoan thanh
 */
inline bool parseNumber(const std::string& text, double& value) {
    // Sua 27/11/2026 (Khoi): chi nhan chu so, '+', '-', '.', 'e', 'E' va so huu han;
    // truoc day "nan" (lai suat) va "0x10" (= 16) van nap duoc tu file
    bool hasDigit = false;
    for (std::size_t i = 0; i < text.size(); i++) {
        const unsigned char c = static_cast<unsigned char>(text[i]);
        if (std::isdigit(c)) {
            hasDigit = true;
        } else if (c != '+' && c != '-' && c != '.' && c != 'e' && c != 'E') {
            return false;
        }
    }
    if (!hasDigit) {
        return false;
    }
    try {
        std::size_t used = 0;
        value = std::stod(text, &used);
        return used == text.size() && std::isfinite(value);
    } catch (...) {
        return false;
    }
}

/*
 * Ham: removeBom
 * Chuc nang: Bo 3 byte BOM UTF-8 (EF BB BF) o dau dong. Notepad cu luu "UTF-8"
 *            kem BOM; neu khong bo thi ma dau tien thanh "\xEF\xBB\xBFT01", khong
 *            tim thay T01 va moi BankAccount thuoc T01 bi bo qua.
 * Tham so: line - dong dau tien doc tu file (sua tai cho)
 * Tra ve: khong
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 27/11/2026
 * Nguoi duyet:
 * Ngay duyet:
 * Ket qua:
 */
inline void removeBom(std::string& line) {
    if (line.size() >= 3 && line.compare(0, 3, "\xEF\xBB\xBF") == 0) {
        line.erase(0, 3);
    }
}

/*
 * Ham: canWrite
 * Chuc nang: Kiem tra ghi duoc vao file ma KHONG xoa noi dung cu (mo che do noi
 *            duoi). File chi doc (Read-only) thi tra ve false.
 * Tham so: filename - ten file
 * Tra ve: true neu ghi duoc
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 27/11/2026
 * Nguoi duyet:
 * Ngay duyet:
 * Ket qua:
 */
inline bool canWrite(const std::string& filename) {
    std::ofstream probe(filename.c_str(), std::ios::app);
    return probe.is_open();
}

/*
 * Ham: replaceFile
 * Chuc nang: Thay file that bang file tam da ghi xong. Ghi ra file tam truoc roi
 *            moi thay, de ghi hong giua chung (o dia day, mat dien) khong lam file
 *            that bi xoa trang. Windows khong cho rename de len file da co nen
 *            phai xoa file cu truoc.
 * Tham so: tempName - file tam (vd accounttypes.txt.tmp); filename - file that
 * Tra ve: true neu thay thanh cong; that bai thi xoa file tam, file that giu nguyen
 *         (tru truong hop hiem: xoa xong ma rename loi, khi do du lieu con o file tam)
 * Nguoi viet: K26DTCN100 - Vu Dang Khoi
 * Ngay viet: 27/11/2026
 * Nguoi duyet:
 * Ngay duyet:
 * Ket qua:
 */
inline bool replaceFile(const std::string& tempName, const std::string& filename) {
    std::remove(filename.c_str());
    if (std::rename(tempName.c_str(), filename.c_str()) != 0) {
        return false;
    }
    return true;
}

} // namespace DataFile

#endif
