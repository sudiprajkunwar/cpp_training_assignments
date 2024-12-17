#ifndef LET_H
#define LET_H

#include <iostream>

enum class DATATYPE
{
    INT,
    DOUBLE,
    CHAR
};

class Let
{
public:
    // Constructors
    Let(const int &val);
    Let(const double &val);
    Let(const char *val);

    // Copy constructor
    Let(const Let &other);

    // Move constructor
    Let(Let &&other) noexcept;

    // Move assignment operator
    Let &operator=(Let &&other) noexcept;

    // Copy assignment operator
    Let &operator=(const Let &other);

    // Operator overloads
    Let &operator+=(const Let &other);
    Let &operator+(const Let &other);
    bool operator==(const Let &other);

    // friend function
    friend std::ostream &operator<<(std::ostream &os, const Let &other);
    // Display function
    void m_display();

    // Destructor
    ~Let();

private:
    int m_int = 0;
    char *m_string = nullptr;
    double m_double = 0.0;
    DATATYPE m_type;
};

#endif // LET_H
