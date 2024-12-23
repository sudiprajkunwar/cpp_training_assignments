#ifndef LET_H
#define LET_H

#include <iostream>
#include <string>
#include "VariantList.cpp" // Assuming this file defines Variant and VariantList

class Let
{
public:
    Let() = delete;

    // Constructors for different data types
    Let(int val);
    Let(double val);
    Let(const char *val);

    // Copy constructor
    Let(const Let &other);

    // Move constructor
    Let(Let &&other) noexcept;

    // Copy assignment operator
    Let &operator=(const Let &other);

    // Move assignment operator
    Let &operator=(Let &&other) noexcept;

    // Operator overloads
    Let &operator+=(const Let &other);
    bool operator==(const Let &other) const;

    // Friend function for output
    friend std::ostream &operator<<(std::ostream &os, const Let &other);

    // Manage list functionality
    void addToList(const Let &val);
    void displayList() const;

    // Destructor
    ~Let();

private:
    Variant m_variant;                             // Encapsulates type and value
    std::shared_ptr<VariantList> m_list = nullptr; // Optional list of Variants
};

#endif // LET_H
