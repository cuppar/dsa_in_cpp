#include <iostream>
#include <map>
#include <string>
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

void exec()
{
    auto expr1 = "1+2*3+(4*5+6)*7";
    auto expr2 = "2^2^3";

    auto postfix_expr1 = infix2postfix(expr1);
    auto postfix_expr2 = infix2postfix(expr2);
    println(expr1, " => ", postfix_expr1, " => ", calc(postfix_expr1));
    println(expr2, " => ", postfix_expr2, " => ", calc(postfix_expr2));
}

int main()
{
    exec();
    return 0;
}
