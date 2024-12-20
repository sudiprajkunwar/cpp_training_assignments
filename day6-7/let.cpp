#include "let.h"

// Constructor for int
Let::Let(int val) : m_variant(val) {}

// Constructor for double
Let::Let(double val) : m_variant(val) {}

// Constructor for string
Let::Let(const char *val) : m_variant(val) {}

// Copy constructor
Let::Let(const Let &other) : m_variant(other.m_variant)
{
    if (other.m_list)
    {
        m_list = std::make_shared<VariantList>(*other.m_list);
    }
}

// Move constructor
Let::Let(Let &&other) noexcept : m_variant(std::move(other.m_variant)), m_list(std::move(other.m_list)) {}

// Copy assignment operator
Let &Let::operator=(const Let &other)
{
    if (this != &other)
    {
        m_variant = other.m_variant;
        if (other.m_list)
        {
            m_list = std::make_shared<VariantList>(*other.m_list);
        }
        else
        {
            m_list.reset();
        }
    }
    return *this;
}

// Move assignment operator
Let &Let::operator=(Let &&other) noexcept
{
    if (this != &other)
    {
        m_variant = std::move(other.m_variant);
        m_list = std::move(other.m_list);
    }
    return *this;
}

// += operator
Let &Let::operator+=(const Let &other)
{
    if (m_variant.getType() == DataType::NUMBER && other.m_variant.getType() == DataType::NUMBER)
    {
        m_variant = m_variant.getNum() + other.m_variant.getNum();
    }
    else if (m_variant.getType() == DataType::DOUBLE && other.m_variant.getType() == DataType::DOUBLE)
    {
        m_variant = m_variant.getDouble() + other.m_variant.getDouble();
    }
    else if (m_variant.getType() == DataType::STRING && other.m_variant.getType() == DataType::STRING)
    {
        std::string combined = m_variant.getString();
        combined += other.m_variant.getString();
        m_variant = combined.c_str();
    }
    return *this;
}

// Equality operator
bool Let::operator==(const Let &other) const
{
    return m_variant.getType() == other.m_variant.getType() && m_variant == other.m_variant;
}

// Add to list
void Let::addToList(const Let &val)
{
    if (!m_list)
    {
        m_list = std::make_shared<VariantList>();
    }
    m_list->append(val.m_variant);
}

// Display list
void Let::displayList() const
{
    if (m_list)
    {
        m_list->display();
    }
    else
    {
        std::cout << "List is empty." << std::endl;
    }
}

// Destructor
Let::~Let() = default;

// Overload << operator
std::ostream &operator<<(std::ostream &os, const Let &other)
{
    os << other.m_variant;
    return os;
}

int main()
{
    // Creating Let objects with different types
    Let intVar(10);
    Let doubleVar(20.5);
    Let stringVar("Hello");

    // Displaying individual values
    std::cout << "intVar: " << intVar << std::endl;
    std::cout << "doubleVar: " << doubleVar << std::endl;
    std::cout << "stringVar: " << stringVar << std::endl;

    // Adding integer and double values
    intVar += Let(5);
    doubleVar += Let(10.5);

    std::cout << "Updated intVar: " << intVar << std::endl;
    std::cout << "Updated doubleVar: " << doubleVar << std::endl;

    // Concatenating strings
    stringVar += Let(" World!");
    std::cout << "Updated stringVar: " << stringVar << std::endl;

    // Working with the list
    Let listHolder(0);
    listHolder.addToList(intVar);
    listHolder.addToList(doubleVar);
    listHolder.addToList(stringVar);

    std::cout << "Displaying list in listHolder:" << std::endl;
    listHolder.displayList();

    // Copying Let object
    Let copy = listHolder;
    std::cout << "Displaying copied list:" << std::endl;
    copy.displayList();

    // Equality check
    if (intVar == Let(15))
    {
        std::cout << "intVar is equal to 15" << std::endl;
    }

    return 0;
}