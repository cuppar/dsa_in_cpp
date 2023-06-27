#include <cmath>
#include <iostream>
#include <string>

void printDigit(int c)
{
    if (c < 0 || c > 9)
        std::cout << (char)c;

    else
        std::cout << c;
}

void printInt(int n)
{
    if (n >= 10)
        printInt(n / 10);

    printDigit(n % 10);
}

void printDecimal(double decimal)
{
    decimal *= 10;
    int n = decimal;

    if (decimal - n < 0.0000000000000001)
        printDigit(n);

    else
    {
        printDigit(n);
        printDecimal(decimal - n);
    }
}

void printDouble(double number)
{
    if (number < 0)
    {
        printDigit('-');
        printDouble(-number);
        return;
    }

    int integerPart{static_cast<int>(number)};
    double decimalPart{number - integerPart};
    printInt(integerPart);
    printDigit('.');
    printDecimal(decimalPart);
}

int main()
{
    printDouble(-123.400000006);
    std::cout << '\n';
    printDouble(123.42345325);
    std::cout << '\n';
    printDouble(-123.000000006);
    std::cout << '\n';
    printDouble(-0.400000006);
    std::cout << '\n';
    printDouble(0.400000006);
    std::cout << '\n';
    return 0;
}
