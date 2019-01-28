/*
 * main.cpp
 *
 *  Created on: 26 Jan 2019
 *      Author: osboxes
 */

#include "String.hpp"
#include <iostream>

using namespace cus;

int main() {
    cus::String s{"My string"_s};
    std::cout << s << "\n";

    s += 's';
    std::cout << s << "\n";

    s += " is the best ever string!";
    std::cout << s << "\n";

    return 0;
}

