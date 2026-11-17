#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>
#include "Utils.h"

class Menu {
public:
    template <typename T>
    int int_getChoice(const std::vector<T>& options) {
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << (i + 1) << ". " << options[i] << "\n";
        }
        return Utils::inputInt("Choose an option (1-" + std::to_string(options.size()) + "): ",
                               1, static_cast<int>(options.size()));
    }

    template <typename T>
    T ref_getChoice(const std::vector<T>& options) {
        int response = int_getChoice(options);
        return options[response - 1];
    }
};

#endif