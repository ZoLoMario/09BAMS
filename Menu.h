/*
 * File: Menu.h
 * Mo ta: Quan ly danh sach Menu (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN115 - Luong Duc Trung
 * Ngay viet: 16/11/2026
 */

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu {
public:
    // Hiển thị danh sách menu và trả về lựa chọn từ 1 đến N
    static int getChoice(const std::vector<std::string>& options);
};

#endif

