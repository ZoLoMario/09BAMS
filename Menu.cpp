/*
 * File: Menu.cpp
 * Mo ta: Quan ly danh sach Menu (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN115 - Luong Duc Trung
 * Ngay viet: 16/11/2026
 */
#include "Menu.h"
#include <iostream>
#include <vector>

int Menu::getChoice(const std::vector<std::string>& options) {
    for (std::size_t i = 0; i < options.size(); ++i)
        std::cout << (i + 1) << ". " << options[i] << '\n';
    int choice;
    std::cout << "Lua chon: ";
    while (!(std::cin >> choice) || choice < 1 || choice > static_cast<int>(options.size())) {
        std::cout << "Lua chon khong hop le. Nhap lai: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore(10000, '\n');
    return choice;
}
