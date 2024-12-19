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
    Variant(const Variant &other)
    {
        m_type = other.m_type;
        m_int = other.m_int;
        m_double = other.m_double;
        if (other.m_type == DataType::STRING && other.m_string)
        {
            m_string = new char[strlen(other.m_string) + 1];
            strcpy(m_string, other.m_string);
        }
        else
        {
            m_string = nullptr;
        }
    }

    Variant(int n) : m_int(n), m_type(DataType::NUMBER) {}
    Variant(double d) : m_double(d), m_type(DataType::DOUBLE) {}
    Variant(const char *s) : m_type(DataType::STRING)
    {
        m_string = new char[strlen(s) + 1];
        strcpy(m_string, s);
    }

    Variant &operator=(const Variant &other)
    {
        if (this == &other)
            return *this;

        m_type = other.m_type;
        m_int = other.m_int;
        m_double = other.m_double;

        if (m_string)
        {
            delete[] m_string;
        }

        if (other.m_type == DataType::STRING && other.m_string)
        {
            m_string = new char[strlen(other.m_string) + 1];
            strcpy(m_string, other.m_string);
        }
        else
        {
            m_string = nullptr;
        }

        return *this;
    }

    DataType getType() const
    {
        return m_type;
    }

    int getNum() const
    {
        return m_int;
    }

    const char *getString() const
    {
        return m_string;
    }

    double getDouble() const
    {
        return m_double;
    }

    ~Variant()
    {
        if (m_type == DataType::STRING)
        {
            delete[] m_string;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Variant &var)
    {
        switch (var.m_type)
        {
        case DataType::NUMBER:
            os << var.m_int;
            break;
        case DataType::DOUBLE:
            os << var.m_double;
            break;
        case DataType::STRING:
            os << (var.m_string ? var.m_string : "null");
            break;
        default:
            os << "unknown";
            break;
        }
        return os;
    }

private:
    int m_int = 0;
    char *m_string = nullptr;
    double m_double = 0.0;
    DataType m_type = DataType::UNKNOWN;
};

struct Node
{
    Variant data;
    Node *next;

    Node(const Variant &val) : data(val), next(nullptr) {}
};

class VariantList
{
public:
    VariantList() : head(nullptr) {}

    void append(const Variant &other)
    {
        Node *newNode = new Node(other);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            auto temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Display function to print the list
    void display() const
    {
        Node *temp = head;
        while (temp)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Destructor to clean up memory
    ~VariantList()
    {
        Node *temp = head;
        while (temp)
        {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
    }

private:
    Node *head;
};
