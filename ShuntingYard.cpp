#include "ShuntingYard.h"

std::vector<std::string> expParsing(std::string& input)
{
    std::vector<std::string> output;
    std::vector<std::string> funcs = {"sin", "cos", "tg", "ctg"};

    for (int i = 0; i < input.size(); ++i)
    {
        // reading num
        if (myIsdigit(input[i]))
        {
            std::string num;
            bool pointWasFind = false;
            while (myIsdigit(input[i]) || input[i] == '.')
            {
                if (pointWasFind && input[i] == '.')
                {
                    throw std::invalid_argument("Invalid input");
                }
                if (input[i] == '.')
                {
                    pointWasFind = true;
                }
                num.push_back(input[i]);
                ++i;
            }
            --i;
            output.push_back(num);
            continue;
        }

        // reading func
        if (myIsalpha(input[i]))
        {
            std::string func;
            while (myIsalpha(input[i]))
            {
                func.push_back(input[i]);
                ++i;
            }
            --i;
            strToLower(func); // Cos, cOs, ... are correct cases
            if (find(funcs, func))
            {
                output.push_back(func);
            }
            else
            {
                throw std::invalid_argument("Invalid input");
            }
            continue;
        }

        // TODO: maybe rework by class Token
        // reading operator
        if (opPrior(std::string(1, input[i])) != -1
            ||
            isBrackets(std::string(1, input[i])))
        {
            output.emplace_back(std::string(1, input[i]));
            continue;
        }

        if (input[i] != ' ')
        {
            throw std::invalid_argument("Invalid input");
        }
    }

    return output;
}

bool myIsdigit(char ch)
{
    return std::isdigit(static_cast<unsigned char>(ch));
}

bool myIsalpha(char ch)
{
    return std::isalpha(static_cast<unsigned char>(ch));
}

void strToLower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
}

bool find(const std::vector<std::string>& vec, const std::string& str) {
    return std::find(std::begin(vec),
                     std::end(vec), str) != std::end(vec);
}

int opPrior(const std::string& str)
{
    if (str == "^" || str == "sin" || str == "cos" || str == "tg" || str == "ctg")
    {
        return 4;
    }
    if (str == "*" || str == "/")
    {
        return 3;
    }
    if (str == "+" || str == "-")
    {
        return 2;
    }
    return -1;
}

bool isBrackets(const std::string& str)
{
    if (str == "(" || str == ")")
    {
        return true;
    }
    return false;
}

void printQueue(std::queue<std::string> q)
{
    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

void printVector(const std::vector<std::string>& v)
{
    for (const auto& str : v)
    {
        std::cout << str << " ";
    }
    std::cout << std::endl;
}