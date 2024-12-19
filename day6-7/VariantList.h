#ifndef VARIANT_H
#define VARIANT_H

#include <iostream>
#include <cstring>

enum class DataType
{
    UNKNOWN = -1,
    NUMBER,
    DOUBLE,
    STRING,
    BOOLEAN,
};

class Variant
{
public:
    Variant(const Variant &other);
    Variant(int n);
    Variant(double d);
    Variant(const char *s);

    Variant &operator=(const Variant &other);

    DataType getType() const;
    int getNum() const;
    char *getString() const;
    double getDouble() const;

    ~Variant();

private:
    int m_int = 0;
    char *m_string = nullptr;
    double m_double = 0.0;
    DataType m_type = DataType::UNKNOWN;
};

struct Node
{
    Variant v;
    Node *next;
    Node(const Variant v);
};

class VariantList
{
public:
    void addVariant(Variant other);
    friend std::ostream &operator<<(std::ostream &os, VariantList &vl);

    Node *getHead() const;
    Node *getLast() const;

    ~VariantList();

private:
    Node *head = nullptr;
    Node *tail = nullptr;
};

std::ostream &operator<<(std::ostream &os, VariantList &vl);

#endif // VARIANT_H
