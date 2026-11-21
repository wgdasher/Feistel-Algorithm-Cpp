#include <iostream>
#include "my_file.h"

int my_file::size(std::ifstream& file) {
    if (!file.is_open()) {
        std::cerr << " Could not open file\n";
        return -1;
    }

    long count = 0; 
    char ch;

    while (file.get(ch))
        count++;

    file.clear();
    file.seekg(0, std::ios::beg);
    return count;
}