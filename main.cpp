#include "ShuntingYard.h"
#include <iostream>

int main() {
    try
    {
        std::string input = "17+1/2-(2+3)/(6/7^2)*17-9*(6*(6+sin5)) + cos6^2";
//        std::string input = "(sin(9-2)^2^1-6/7)^(13-9)";
        printVector(expParsing(input));
        auto rpnInput = toRPN(input);
        printQueue(rpnInput);
        std::cout << calculateRPN(rpnInput) << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
