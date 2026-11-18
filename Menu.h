/*
 * File: Menu.h
 * Mo ta: Quan ly danh sach Menu (doc/ghi file, them, sua, tim)
 * Nguoi viet: K26DTCN089 - Vu Trong Hanh
 * Ngay viet: 16/11/2026
 */
#pragma once
#include <string>
#include <vector>

class Menu {
public:
    static int getChoice(const std::vector<std::string>& options);
};
