//
// Created by HORIA on 16.11.2023.
//
#include <iostream>
#include "My_String.h"

void readVec(const String& s) {
    std::cout << s << '\n';
}

int main () {

    String s1 {};

    s1[0] = 'D';

    std::cout << s1;

    return 0;
}