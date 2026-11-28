/*
 * File: Utils.h
 * Mo ta: Ham nhap lieu
 * Nguoi viet: K26DTCN115 - Luong Duc Trung
 * Ngay viet: 16/11/2026
 */


#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <limits>

namespace Utils {

    // Xóa khoảng trắng ở đầu và cuối chuỗi
    inline std::string trim(const std::string& str) {
        constexpr std::string_view whitespace = " \t\r\n";

        const size_t first = str.find_first_not_of(whitespace);
        if (first == std::string::npos) {
            return "";
        }

        const size_t last = str.find_last_not_of(whitespace);

        return str.substr(first, last - first + 1);
    }

    // Chuyển chuỗi sang chữ thường
    inline std::string toLower(const std::string& str) {
        std::string result = str;

        std::transform(
            result.begin(),
            result.end(),
            result.begin(),
            [](unsigned char c) {
                return static_cast<char>(std::tolower(c));
            }
        );

        return result;
    }

    // Tách chuỗi theo dấu phân cách
    inline std::vector<std::string> split(
        const std::string& s,
        char delimiter
    ) {
        std::vector<std::string> tokens;
        std::istringstream stream(s);
        std::string token;

        while (std::getline(stream, token, delimiter)) {
            tokens.push_back(trim(token));
        }

        return tokens;
    }

    // Kiểm tra trạng thái nhập liệu
    inline void checkInput() {
        if (std::cin.eof()) {
            throw std::runtime_error("Input stream closed.");
        }

        if (!std::cin) {
            throw std::runtime_error("Input stream error.");
        }
    }

    // Nhập chuỗi không rỗng và không chứa dấu phẩy
    inline std::string inputNonEmptyString(
        const std::string& prompt
    ) {
        std::string value;

        while (true) {
            std::cout << prompt;

            if (!std::getline(std::cin, value)) {
                checkInput();
            }

            value = trim(value);

            if (value.empty()) {
                std::cout
                    << "[Error] Input cannot be empty. Please try again.\n";
            }
            else if (value.find(',') != std::string::npos) {
                std::cout
                    << "[Error] Input cannot contain commas (','). Please try again.\n";
            }
            else {
                return value;
            }
        }
    }

    // Nhập số thực
    // strictlyGreater = true  : val > minVal
    // strictlyGreater = false : val >= minVal
    inline double inputDouble(
        const std::string& prompt,
        double minVal,
        bool strictlyGreater
    ) {
        std::string line;

        while (true) {
            std::cout << prompt;

            if (!std::getline(std::cin, line)) {
                checkInput();
            }

            line = trim(line);

            try {
                size_t idx = 0;

                const double val = std::stod(line, &idx);

                if (idx != line.length() || !std::isfinite(val)) {
                    throw std::invalid_argument("Invalid number");
                }

                if (strictlyGreater && val <= minVal) {
                    std::cout
                        << "[Error] Value must be greater than "
                        << minVal << ". Please try again.\n";
                }
                else if (!strictlyGreater && val < minVal) {
                    std::cout
                        << "[Error] Value must be greater than or equal to "
                        << minVal << ". Please try again.\n";
                }
                else {
                    return val;
                }

            }
            catch (const std::exception&) {
                std::cout
                    << "[Error] Invalid number format. Please try again.\n";
            }
        }
    }

    // Nhập số nguyên trong khoảng [minVal, maxVal]
    inline int inputInt(
        const std::string& prompt,
        int minVal,
        int maxVal
    ) {
        std::string line;

        while (true) {
            std::cout << prompt;

            if (!std::getline(std::cin, line)) {
                checkInput();
            }

            line = trim(line);

            try {
                size_t idx = 0;

                const int val = std::stoi(line, &idx);

                if (idx != line.length()) {
                    throw std::invalid_argument("Invalid integer");
                }

                if (val < minVal || val > maxVal) {
                    std::cout
                        << "[Error] Please enter a number between "
                        << minVal << " and " << maxVal << ".\n";
                }
                else {
                    return val;
                }

            }
            catch (const std::exception&) {
                std::cout
                    << "[Error] Invalid integer. Please try again.\n";
            }
        }
    }

}

#endif
