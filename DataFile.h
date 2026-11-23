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
    try {
        std::size_t used = 0;
        value = std::stod(text, &used);
        return used == text.size();
    } catch (...) {
        return false;
    }
}

} // namespace DataFile

#endif
