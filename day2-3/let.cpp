#include "./let.h"

// Constructor for int, double and char
Let::Let(const int &val) : m_int(val), m_type(DATATYPE::INT) {}
Let::Let(const double &val) : m_double(val), m_type(DATATYPE::DOUBLE) {}
Let::Let(const char *val) : m_type(DATATYPE::CHAR)
{
    m_string = new char[std::strlen(val) + 1]; // Allocate memory for string
    std::strcpy(m_string, val);                // Copy the string
}

// copy contructor
Let::Let(const Let &other) : m_type(other.m_type)
{
    if (m_type == DATATYPE::DOUBLE)
    {
        m_double = other.m_double;
    }

    if (m_type == DATATYPE::INT)
    {
        m_int = other.m_int;
    }

    if (m_type == DATATYPE::CHAR)
    {
        m_string = new char[std::strlen(other.m_string) + 1];
        std::strcpy(m_string, other.m_string);
    }
}

// Move constructor
Let::Let(Let &&other) noexcept : m_type(other.m_type)
{
    if (m_type == DATATYPE::DOUBLE)
    {
        m_double = other.m_double;
    }

    if (m_type == DATATYPE::INT)
    {
        m_int = other.m_int;
    }

    if (m_type == DATATYPE::CHAR)
    {
        m_string = other.m_string;
        other.m_string = nullptr;
    }
};

// Move assignment operator
Let &Let::operator=(Let &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    m_type = other.m_type;

    if (m_type == DATATYPE::DOUBLE)
    {
        m_double = other.m_double;
    }

    if (m_type == DATATYPE::INT)
    {
        m_int = other.m_int;
    }

    if (m_type == DATATYPE::CHAR)
    {
        delete[] m_string;
        m_string = other.m_string;
        other.m_string = nullptr;
    }

    return *this;
}

Let &Let::operator+=(const Let &other)
{

    if (m_type == DATATYPE::DOUBLE && other.m_type == DATATYPE::DOUBLE)
    {
        m_double += other.m_double;
    }

    if (m_type == DATATYPE::INT && other.m_type == DATATYPE::INT)
    {
        m_int += other.m_int;
    }

    if (m_type == DATATYPE::INT && other.m_type == DATATYPE::DOUBLE)
    {
        m_double = static_cast<double>(m_int) + other.m_double;
        m_type = DATATYPE::DOUBLE;
    }
    if (m_type == DATATYPE::DOUBLE && other.m_type == DATATYPE::INT)
    {
        m_double += static_cast<double>(other.m_int);
    }

    if (m_type == DATATYPE::CHAR && other.m_type == DATATYPE::CHAR)
    {
        char *result = new char[std::strlen(m_string) + std::strlen(other.m_string) + 1];

        std::strcpy(result, m_string);
        std::strcat(result, other.m_string);

        delete[] m_string;
        m_string = result;
    }

    return *this;
};

Let &Let::operator+(const Let &other)
{

    if (m_type == DATATYPE::DOUBLE)
    {
        m_double += other.m_double;
    }

    if (m_type == DATATYPE::INT)
    {
        m_int += other.m_int;
    }

    if (m_type == DATATYPE::CHAR && other.m_type == DATATYPE::CHAR)
    {
        char *result = new char[std::strlen(m_string) + std::strlen(other.m_string) + 1];

        std::strcpy(result, m_string);
        std::strcat(result, other.m_string);

        delete[] m_string;
        m_string = result;
    }

    return *this;
};

Let &Let::operator=(const Let &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_type = other.m_type;

    if (m_type == DATATYPE::INT)
    {
        m_int = other.m_int;
    }
    else if (m_type == DATATYPE::DOUBLE)
    {
        m_double = other.m_double;
    }
    else if (m_type == DATATYPE::CHAR)
    {
        // Free existing resources if current type is CHAR
        delete[] m_string;
        m_string = new char[std::strlen(other.m_string) + 1];
        std::strcpy(m_string, other.m_string);
    }

    return *this;
}

bool Let::operator==(const Let &other)
{
    // Check if the types are the same
    if (m_type != other.m_type)
    {
        return false;
    }

    // Compare based on the type
    if (m_type == DATATYPE::INT)
    {
        return m_int == other.m_int;
    }
    if (m_type == DATATYPE::DOUBLE)
    {
        return m_double == other.m_double;
    }
    if (m_type == DATATYPE::CHAR)
    {
        return std::strcmp(m_string, other.m_string) == 0;
    }

    // Return false for unsupported types
    return false;
}

void Let::m_display()
{
    std::cout << *this << '\n';
};

// Destructor
Let::~Let()
{
    if (m_type == DATATYPE::CHAR)
    {
        delete[] m_string;  // Deallocate the memory
        m_string = nullptr; // Set pointer to nullptr to avoid dangling pointer
    }
}

// Overloading the << operator
std::ostream &operator<<(std::ostream &os, const Let &other)
{
    if (other.m_type == DATATYPE::INT)
    {
        os << "Integer value: " << other.m_int;
    }
    else if (other.m_type == DATATYPE::DOUBLE)
    {
        os << "Double value: " << other.m_double;
    }
    else if (other.m_type == DATATYPE::CHAR)
    {
        os << "String value: " << other.m_string;
    }
    else
    {
        os << "Unknown Type";
    }
    return os;
}
