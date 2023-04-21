//
// Created by Egor on 15.04.2023.
//
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Hello world!" << std::endl;
    int count_threads = std::stoi(argv[1]);

    std::cout << count_threads << std::endl;
    return 0;
}
