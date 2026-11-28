/*
 * File: Menu.cpp
 * Mo ta: Quan ly danh sach Menu (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN115 - Luong Duc Trung
 * Ngay viet: 16/11/2026
 */

#include "Menu.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

int Menu::getChoice(const std::vector<std::string>& options) {

    // Kiểm tra danh sách menu
    if (options.empty()) {
        throw std::invalid_argument("Menu options cannot be empty.");
    }

    // Hiển thị danh sách menu
    for (std::size_t i = 0; i < options.size(); ++i) {
        std::cout << (i + 1) << ". " << options[i] << '\n';
    }

    int choice;

    std::cout << "Lua chon: ";

    while (true) {

        if (std::cin >> choice) {

            // Xóa phần còn lại của dòng nhập
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            // Kiểm tra lựa chọn
            if (choice >= 1 &&
                choice <= static_cast<int>(options.size())) {
                return choice;
            }

        }
        else {

            // Xử lý khi luồng nhập kết thúc
            if (std::cin.eof()) {
                throw std::runtime_error("Input stream closed.");
            }

            // Xóa trạng thái lỗi
            std::cin.clear();

            // Loại bỏ dữ liệu nhập không hợp lệ
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
        }

        std::cout << "Lua chon khong hop le. Nhap lai: ";
    }
}

