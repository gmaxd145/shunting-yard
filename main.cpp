#include "ShuntingYard.h"
#include <iostream>

int main() {
    try
    {
        std::string input = "sin(1.1) +1";
        printVector(expParsing(input));
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
