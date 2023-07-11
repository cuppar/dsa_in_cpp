#include <iostream>
#include <algorithm>
#include <sstream>
#include <list>
#include <map>
#include "util.h"

static const char END{'#'};
static std::istringstream input("{[hello](world!)}x[]*/*  [  [(foo)bar]/* * /] /* ()*/#");
static std::string identifierStr;
static int currentToken;

enum Token
{
    tok_identifier = -1,
    tok_begin = -2,
    tok_end = -3,
    tok_eof = -4,
};

char getChar()
{
    return input.get();
}

int getToken()
{
    static char lastChar = ' ';
    while (isspace(lastChar))
        lastChar = getChar();

    if (isalpha(lastChar))
    {
        identifierStr = lastChar;
        lastChar = getChar();
        while (isalnum(lastChar))
        {
            identifierStr += lastChar;
            lastChar = getChar();
        }
        return tok_identifier;
    }
    if (lastChar == '/')
    {
        lastChar = getChar();
        if (lastChar == '*')
        {
            return tok_begin;
        }
        else
            return '/';
    }
    if (lastChar == '*')
    {
        lastChar = getChar();
        if (lastChar == '/')
        {
            return tok_end;
        }
        else
            return '*';
    }

    if (lastChar == END)
        return tok_eof;

    int thisChar = lastChar;
    lastChar = getChar();
    return thisChar;
}

int getNextToken()
{
    return currentToken = getToken();
}

template <typename... Args>
void reportError(const Args &...args)
{
    std::ostringstream msg{};
    (msg << ... << args);
    throw std::runtime_error(msg.str());
}

static std::map<int, int> pairMap{
    {'(', ')'},
    {'[', ']'},
    {'{', '}'},
};

void parser()
{
    getNextToken();
    std::vector<int> stack;
    while (currentToken != tok_eof)
    {
        // left pair, push to stack
        if (currentToken == tok_begin ||
            currentToken == '(' ||
            currentToken == '[' ||
            currentToken == '{')
            stack.push_back(currentToken);

        // right pair, pop stack to match
        if (currentToken == tok_end ||
            currentToken == ')' ||
            currentToken == ']' ||
            currentToken == '}')
        {
            if (stack.empty())
            {
                if (currentToken == tok_end)
                    reportError("non-excepted `", "*/", "`");
                else
                    reportError("non-excepted `", (char)currentToken, "`");
            }

            int leftPair{stack.back()};

            if (currentToken == tok_end && leftPair != tok_begin)
            {
                reportError("except `", (char)pairMap[leftPair], "`, but get `*/`");
            }
            if (currentToken == ')' && leftPair != '(')
            {
                if (leftPair == tok_begin)
                    reportError("export ", "`*/`", ", but get `)`");
                else
                    reportError("except `", (char)pairMap[leftPair], "`, but get `)`");
            }
            if (currentToken == ']' && leftPair != '[')
            {
                if (leftPair == tok_begin)
                    reportError("export ", "`*/`", ", but get `]`");
                else
                    reportError("except `", (char)pairMap[leftPair], "`, but get `]`");
            }
            if (currentToken == '}' && leftPair != '{')
            {
                if (leftPair == tok_begin)
                    reportError("export ", "`*/`", ", but get `}`");
                else
                    reportError("except `", (char)pairMap[leftPair], "`, but get `}`");
            }

            stack.pop_back();
        }
        getNextToken();
    }
    if (!stack.empty())
    {
        int leftPair{stack.back()};
        if (leftPair == tok_begin)
            reportError("unmatched `", "/*", "`");
        else
            reportError("unmatched `", (char)leftPair, "`");
    }
}

void exec()
{
    parser();
}

int main()
{
    exec();
    return 0;
}
