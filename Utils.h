#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>

namespace Utils {
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
            std::getline(std::cin, value);
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
            std::getline(std::cin, line);
            line = trim(line);
            try {
                size_t idx = 0;
                double val = std::stod(line, &idx);
                if (idx != line.length()) {
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
            std::getline(std::cin, line);
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