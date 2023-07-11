#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include "util.h"

enum op_associate
{
    left,
    right,
};

struct OpPrep
{
    int precedence;
    op_associate associate;
};

static std::map<char, OpPrep> op_map{
    {'+', {10, left}},
    {'-', {10, left}},
    {'*', {20, left}},
    {'/', {20, left}},
    {'^', {30, right}},
};

std::string infix2postfix(std::string_view s)
{
    std::vector<char> stack;
    std::string result;

    for (const auto &ch : s)
    {
        if (op_map.find(ch) != op_map.end() || ch == '(' || ch == ')')
        {
            // is operator or ()
            if (ch == '(')
            {
                stack.push_back(ch);
                continue;
            }

            if (ch == ')')
            {
                while (!stack.empty() && stack.back() != '(')
                {
                    result += stack.back();
                    stack.pop_back();
                }

                if (!stack.empty())
                    stack.pop_back(); // pop (
                continue;
            }

            // is operator
            if (op_map[ch].associate == left)
            {
                while (!stack.empty() && op_map[stack.back()].precedence >= op_map[ch].precedence)
                {
                    result += stack.back();
                    stack.pop_back();
                }
            }
            else
            {
                while (!stack.empty() && op_map[stack.back()].precedence > op_map[ch].precedence)
                {
                    result += stack.back();
                    stack.pop_back();
                }
            }

            stack.push_back(ch);
        }
        else
        {
            // is operand
            result += ch;
        }
    }

    while (!stack.empty())
    {
        result += stack.back();
        stack.pop_back();
    }

    return result;
}

double calc_op(char op, double left, double right)
{
    switch (op)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    case '^':
        return pow(left, right);
    default:
        return -1;
    }
}

double calc(std::string_view s)
{
    std::vector<double> stack;
    for (const auto &ch : s)
    {
        if (op_map.find(ch) != op_map.end())
        {
            // is operator
            auto right{stack.back()};
            stack.pop_back();
            auto left{stack.back()};
            stack.pop_back();
            stack.push_back(calc_op(ch, left, right));
        }
        else
        {
            // is operand
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            std::string temp_s = temp;
            stack.push_back(std::stof(temp_s.c_str()));
        }
    }
    return stack.back();
}

std::string postfix2indix(std::string_view s)
{
    std::vector<std::string> stack;
    for (auto &ch : s)
    {
        if (op_map.find(ch) != op_map.end())
        {
            // is opr
            auto right{stack.back()};
            stack.pop_back();
            auto left{stack.back()};
            stack.pop_back();
            stack.push_back("(" + left + ch + right + ")");
        }
        else
        {
            // is opd
            std::ostringstream s;
            s << ch;
            stack.push_back(s.str());
        }
    }
    return stack.back();
}

void p(std::string_view expr)
{
    auto postfix_expr{infix2postfix(expr)};
    println(expr.data(), " => ", postfix_expr.c_str(), " => ",
            calc(postfix_expr), " => ", postfix2indix(postfix_expr).c_str());
}
void exec()
{
    auto expr1 = "1+2*3+(4*5+6)*7";
    auto expr2 = "(2^2)^3";
    auto expr3 = "2^2^3";
    p(expr1);
    p(expr2);
    p(expr3);
}

int main()
{
    exec();
    return 0;
}
