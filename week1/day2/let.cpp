#include <iostream>
#include <string>

enum class DATATYPE
{
    INT,
    DOUBLE,
    CHAR
};

class Let
{

public:
    Let(int val) : m_int(val), m_type(DATATYPE::INT) {}

    Let(const double val) : m_double(val), m_type(DATATYPE::DOUBLE) {}

    Let(const char *val) : m_type(DATATYPE::CHAR)
    {
        m_string = new char[std::strlen(val) + 1]; // Allocate memory for string
        std::strcpy(m_string, val);                // Copy the string
    }

    // copy contructor
    Let(const Let &other) : m_type(other.m_type)
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
    Let(Let &&other) noexcept : m_type(other.m_type)
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
    Let &operator=(Let &&other) noexcept
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

    Let &operator+=(const Let &other)
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

    Let &operator+(const Let &other)
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

    Let &operator=(const Let &other)
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

    bool operator==(const Let &other)
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

    void m_display()
    {
        if (m_type == DATATYPE::INT)
        {
            std::cout << "Integer value: " << m_int << '\n';
        }

        else if (m_type == DATATYPE::DOUBLE)
        {
            std::cout << "Double value: " << m_double << '\n';
        }

        else if (
            m_type == DATATYPE::CHAR)
        {
            std::cout << "String value: " << m_string << '\n';
        }
    };

    // Destructor
    ~Let()
    {
        if (m_type == DATATYPE::CHAR)
        {
            delete[] m_string;  // Deallocate the memory
            m_string = nullptr; // Set pointer to nullptr to avoid dangling pointer
        }
    }

private:
    int m_int = 0;
    char *m_string = nullptr;
    double m_double = 0.0;
    DATATYPE m_type;
};

int main()
{

    // Create object of Let with different data types
    Let intObj(42);          // Integer object
    Let doubleObj(3.14159);  // Double object
    Let stringObj("Hello!"); // String object

    // Display their values
    std::cout << "Displaying values:\n";
    intObj.m_display();    // Display Integer
    doubleObj.m_display(); // Display Double
    stringObj.m_display(); // Display String

    // Copy
    std::cout << "Copy object values:\n";
    Let copyObj = stringObj;
    copyObj.m_display(); // Display String

    // Move
    std::cout << "Move object values:\n";
    Let moveObj = std::move(stringObj);
    moveObj.m_display(); // Display String

    // += operator
    Let op1 = 5;
    op1 += 4.1;

    op1.m_display();

    // == operator
    Let var5("Hello");
    Let var6("Hello");

    if (var5 == var6)
    {
        std::cout << "var5 == var6 -> This condition satisfies\n";
    }

    return 0;
}