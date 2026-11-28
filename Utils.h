#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <cmath>
#include <exception>
#include <stdexcept>

namespace Utils {
    /*
     * Class: InputEnded
     * Chuc nang: Bao het dau vao (Ctrl+Z tren Windows, Ctrl+D tren Linux, hoac file
     *            nhap da het dong). Khong ke thua runtime_error de cac khoi
     *            catch(runtime_error) nhap lai khong bat nham roi hoi lai mai.
     * Nguoi viet: K26DTCN100 - Vu Dang Khoi, 27/11/2026
     * Nguoi duyet:
     * Ngay duyet:
     * Ket qua:
     */
    class InputEnded : public std::exception {
    public:
        const char* what() const noexcept override { return "Input ended (EOF)."; }
    };

    /*
     * Ham: readLine
     * Chuc nang: Doc mot dong tu ban phim; het dau vao thi nem InputEnded
     *            (truoc day getline that bai tra ve chuoi rong, vong nhap lap vo han)
     * Tham so: line - dong doc duoc
     * Tra ve: khong
     * Nguoi viet: K26DTCN100 - Vu Dang Khoi, 27/11/2026
     * Nguoi duyet:
     * Ngay duyet:
     * Ket qua:
     */
    inline void readLine(std::string& line) {
        if (!std::getline(std::cin, line)) {
            throw InputEnded();
        }
    }

    /*
     * Ham: isPlainNumber
     * Chuc nang: Chi nhan chu so, dau '+'/'-', dau '.', 'e'/'E' (so mu).
     *            std::stod con doc duoc "nan", "inf", "0x10" (=16) nen phai chan truoc.
     * Tham so: text - chuoi da trim
     * Tra ve: true neu chi gom cac ky tu tren va co it nhat mot chu so
     * Nguoi viet: K26DTCN100 - Vu Dang Khoi, 27/11/2026
     * Nguoi duyet:
     * Ngay duyet:
     * Ket qua:
     */
    inline bool isPlainNumber(const std::string& text) {
        bool hasDigit = false;
        for (std::size_t i = 0; i < text.size(); ++i) {
            const unsigned char c = static_cast<unsigned char>(text[i]);
            if (std::isdigit(c)) {
                hasDigit = true;
            } else if (c != '+' && c != '-' && c != '.' && c != 'e' && c != 'E') {
                return false;
            }
        }
        return hasDigit;
    }

    // Xóa khoảng trắng thừa ở đầu và cuối chuỗi
    inline std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));
    }

    // Chuyển chuỗi sang chữ thường để so sánh không phân biệt hoa/thường
    inline std::string toLower(const std::string& str) {
        std::string res = str;
        std::transform(res.begin(), res.end(), res.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return res;
    }

    // Tách chuỗi theo dấu phân cách (delimiter)
    inline std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(trim(token));
        }
        return tokens;
    }

    // Nhập chuỗi không được rỗng và không chứa dấu phẩy (tránh hỏng định dạng CSV)
    inline std::string inputNonEmptyString(const std::string& prompt) {
        std::string value;
        while (true) {
            std::cout << prompt;
            readLine(value);
            value = trim(value);
            if (value.empty()) {
                std::cout << "[Error] Input cannot be empty. Please try again.\n";
            } else if (value.find(',') != std::string::npos) {
                std::cout << "[Error] Input cannot contain commas (','). Please try again.\n";
            } else {
                return value;
            }
        }
    }

    // Nhập số thực với điều kiện minVal (strictlyGreater = true nghĩa là > minVal, false nghĩa là >= minVal)
    inline double inputDouble(const std::string& prompt, double minVal, bool strictlyGreater) {
        std::string line;
        while (true) {
            std::cout << prompt;
            readLine(line);
            line = trim(line);
            try {
                // Sua 27/11/2026 (Khoi): chan "nan", "inf", "0x10"; nan lot qua moi
                // phep so sanh (nan < 0 la false) nen truoc day nhan ca so du nan
                if (!isPlainNumber(line)) {
                    throw std::invalid_argument("Not a plain number");
                }
                size_t idx = 0;
                double val = std::stod(line, &idx);
                if (idx != line.length() || !std::isfinite(val)) {
                    throw std::invalid_argument("Trailing characters");
                }
                if (strictlyGreater && val <= minVal) {
                    std::cout << "[Error] Value must be greater than " << minVal << ". Please try again.\n";
                } else if (!strictlyGreater && val < minVal) {
                    std::cout << "[Error] Value must be greater than or equal to " << minVal << ". Please try again.\n";
                } else {
                    return val;
                }
            } catch (...) {
                std::cout << "[Error] Invalid number format. Please try again.\n";
            }
        }
    }

    // Nhập số nguyên trong khoảng [minVal, maxVal]
    inline int inputInt(const std::string& prompt, int minVal, int maxVal) {
        std::string line;
        while (true) {
            std::cout << prompt;
            readLine(line);
            line = trim(line);
            try {
                size_t idx = 0;
                int val = std::stoi(line, &idx);
                if (idx != line.length()) {
                    throw std::invalid_argument("Trailing characters");
                }
                if (val < minVal || val > maxVal) {
                    std::cout << "[Error] Please enter a number between " << minVal << " and " << maxVal << ".\n";
                } else {
                    return val;
                }
            } catch (...) {
                std::cout << "[Error] Invalid integer. Please try again.\n";
            }
        }
    }
}

#endif