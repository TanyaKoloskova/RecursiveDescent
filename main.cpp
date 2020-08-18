#include "Recursive_descent-calculator.h"
#include <iostream>
#include <sstream>
#include <memory>


int main(int argc, char* argv[]) {
    std::unique_ptr<std::istream> iss;
    switch (argc) {
        case 1:
            iss.reset(new std::istream(std::cin.rdbuf()));
            break;
        case 2:
            iss.reset(new std::istringstream(argv[1]));
            break;
        default:
            std::cerr << "Incorrect arguments" << std::endl;
            return 1;
    }
    int result;
    if(calculator(*iss, result))
        return 2;
    std::cout<<result<<std::endl;
    return 0;
}

