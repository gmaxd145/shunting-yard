#include "ShuntingYard.h"

std::vector<std::string> expParsing(const std::string& input) // can be private method of class
{
    std::vector<std::string> output;
    std::vector<std::string> funcs = {"sin", "cos", "tg", "ctg", "acos", "asin", "atg", "ctg", "log2"};  // can be field of class

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

    // case unclosed brackets
    if (std::count(std::cbegin(output), cend(output), "(")
        != std::count(std::cbegin(output), cend(output), ")"))
    {
                throw std::invalid_argument("Invalid input");
    }

    // case braces after funcs
    for (auto it = output.begin(); it != output.end();  ++it)
    {
        if (find(funcs, *it))
        {
            if ( it == output.end() - 1)
            {
                throw std::invalid_argument("Invalid input");
            }
            if (*(it + 1) != "(")
            {
                throw std::invalid_argument("Invalid input");
            }
        }
    }

    return output;
}


std::queue<std::string> toRPN(const std::string& input)
{
    std::vector<std::string> funcs = {"sin", "cos", "tg", "ctg", "acos", "asin", "atg", "ctg", "log2"}; // can be field of class
    std::vector<std::string> leftAs = {"^"}; // can be field of class

    std::stack<std::string> opStack;
    std::queue<std::string> output;

    std::vector<std::string> tokens  = expParsing(input);
    for (auto it = tokens.begin(); it != tokens.end();  ++it)
    {
        auto& tk = *it;

        // number case
        if (myIsdigit(tk[0]))
        {
            output.push(tk);
            continue;
        }

        // function case
        if (myIsalpha(tk[0]))
        {
            opStack.push(tk);
            continue;
        }

        // operator case
        if (opPrior(tk) != -1
            ||
            isBrackets(tk))
        {
            // negative number cases
            if (it + 1 < tokens.end() - 1)
            {
                auto nextTk = *(it + 1);
                if ( it != tokens.begin()) // case (-1...
                {
                    auto prevTk = *(it - 1);
                    if (!opStack.empty())
                    {
                        if (prevTk == "(" && tk == "-" && myIsdigit(nextTk[0]))
                        {
                            output.push("0");
                        }
                    }
                }
                else if (tk == "-" && nextTk == "(") // case -(...
                {
                    output.push("0");
                }
            }

            if (!opStack.empty())
            {
                if (opPrior(opStack.top()) >= opPrior(tk)
                    && !isBrackets(tk)
                    && !isBrackets(opStack.top()))
                {
                    if (find(leftAs, opStack.top()) && find(leftAs, tk))
                    {
                        opStack.push(tk);
                        continue;
                    }
                    while((opPrior(opStack.top()) >= opPrior(tk)))
                    {
                        output.push(opStack.top());
                        opStack.pop();
                        if (opStack.empty())
                        {
                            break;
                        }
                    }
                    opStack.push(tk);
                    continue;
                }
            }

            if (tk == ")")
            {
                while (opStack.top() != "(")
                {
                    output.push(opStack.top());
                    opStack.pop();
                }

                opStack.pop();
                continue;
            }
            opStack.push(tk);
            continue;
        }
    }
    if (!opStack.empty())
    {
        while(!opStack.empty())
        {
            output.push(opStack.top());
            opStack.pop();
        }
    }

    return output;
}

double calculateRPN(std::queue<std::string> tokens)
{
    std::stack<double> values;
    while (!tokens.empty())
    {
        std::string tk = tokens.front();
        tokens.pop();

        if (tk == "sin")
        {
            values.push(sin(getAndPop(values)));
            continue;
        }

        if (tk == "cos")
        {
            values.push(cos(getAndPop(values)));
            continue;
        }

        if (tk == "tg")
        {
            values.push(tan(getAndPop(values)));
            continue;
        }

        if (tk == "ctg")
        {
            values.push(1 / tan(getAndPop(values)));
            continue;
        }
        if (tk == "acos")
        {
            values.push(acos(getAndPop(values)));
        }
        if (tk == "asin")
        {
            values.push(asin(getAndPop(values)));
        }
        if (tk == "atg")
        {
            values.push(atan(getAndPop(values)));
        }
        if (tk == "ctg")
        {
            values.push(1.0 / tan((getAndPop(values))));
        }
        if (myIsdigit(tk[0]))
        {
            values.push(std::stod(tk));
            continue;
        }
        if (tk == "+")
        {
            double  a = getAndPop(values);
            double b = getAndPop(values);
            values.push(b + a);
            continue;
        }
        if (tk == "-")
        {
            double  a = getAndPop(values);
            double b = getAndPop(values);
            values.push(b - a);
            continue;
        }
        if (tk == "*")
        {
            double  a = getAndPop(values);
            double b = getAndPop(values);
            values.push(b * a);
            continue;
        }
        if (tk == "/")
        {
            double  a = getAndPop(values);
            double b = getAndPop(values);
            values.push(b / a);
            continue;
        }
        if (tk == "^")
        {
            double  a = getAndPop(values);
            double b = getAndPop(values);
            values.push(pow(b, a));
            continue;
        }
    }

    if (values.size() != 1)
    {
        throw std::invalid_argument("Invalid input");
    }

    return values.top();
}

double getAndPop(std::stack<double>& st)
{
    if (st.empty())
    {
        throw std::invalid_argument("Invalid input");
    }

    double buf = st.top();
    st.pop();
    return buf;
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
