
#ifndef LET_H
#define LET_H

#include <iostream>
#include <string>
#include <vector>

using VariantType = std::variant<int, double, std::string>;

class Let
{
public:
    Let(int n) : m_var(n) {}
    Let(const char *s) : m_var(s) {}
    Let(double d) : m_var(d) {}
    Let(std::initializer_list<VariantType>);
    Let &operator+(const Let &other);
    Let &operator-(const Let &other);

    char operator[](const int);

    friend std::ostream &operator<<(std::ostream &os, Let &let);

private:
    std::variant<VariantType, std::vector<VariantType>> m_var;
};

#endif