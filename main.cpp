// rpm пакет debian пакет

#include "ShuntingYard.h"
#include <iostream>

int main() {
    try
    {
//        std::string input = "--1";
//        std::string input = "1--";
        std::string input = "9^(3/2)";

//        std::string input = "17+2*SiN";
//        std::string input = "17+2*SiN5)";
//        std::string input = "17+2*SiN(5";
//        std::string input = "17+2*SiN(5)";


//        std::string input = "(sin(9-2)^2^1-6/7)^(13-9)";

//        std::string input = "2^3^4";

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
