#ifndef SHUNTING_YARD_SHUNTINGYARD_H
#define SHUNTING_YARD_SHUNTINGYARD_H

#include <vector>
#include <string>
#include <stdexcept>
#include <queue>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cmath>

std::vector<std::string> expParsing(const std::string& input);

std::queue<std::string> toRPN(const std::string& input);

double calculateRPN(std::queue<std::string> tokens);

double getAndPop(std::stack<double>& st);

bool myIsdigit(char ch);
bool myIsalpha(char ch);

void strToLower(std::string& str);

bool find(const std::vector<std::string>& vec, const std::string& str);

int opPrior(const std::string& str);

bool isBrackets(const std::string& str);

void printQueue(std::queue<std::string> q);
void printVector(const std::vector<std::string>& v);

#endif //SHUNTING_YARD_SHUNTINGYARD_H
