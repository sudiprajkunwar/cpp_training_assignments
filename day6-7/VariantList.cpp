#include <iostream>
#include <cstring>
#include <memory>

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
        : m_type(other.m_type), m_int(other.m_int), m_double(other.m_double)
    {
        if (other.m_type == DataType::STRING && other.m_string)
        {
            m_string = std::make_shared<std::string>(*other.m_string);
        }
    }

    Variant(int n) : m_int(n), m_type(DataType::NUMBER) {}
    Variant(double d) : m_double(d), m_type(DataType::DOUBLE) {}
    Variant(const char *s) : m_type(DataType::STRING), m_string(std::make_shared<std::string>(s)) {}

    Variant &operator=(const Variant &other)
    {
        if (this == &other)
            return *this;

        m_type = other.m_type;
        m_int = other.m_int;
        m_double = other.m_double;
        m_string = other.m_string; // Shared pointer handles reference counting

        return *this;
    }

    DataType getType() const { return m_type; }
    int getNum() const { return m_int; }
    const char *getString() const { return m_string ? m_string->c_str() : nullptr; }
    double getDouble() const { return m_double; }

    bool operator==(const Variant &other) const
    {
        if (m_type != other.m_type)
            return false;

        switch (m_type)
        {
        case DataType::NUMBER:
            return m_int == other.m_int;
        case DataType::DOUBLE:
            return m_double == other.m_double;
        case DataType::STRING:
            return m_string && other.m_string && *m_string == *other.m_string;
        default:
            return false;
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
            os << (var.m_string ? var.m_string->c_str() : "null");
            break;
        default:
            os << "unknown";
            break;
        }
        return os;
    }

private:
    int m_int = 0;
    std::shared_ptr<std::string> m_string = nullptr;
    double m_double = 0.0;
    DataType m_type = DataType::UNKNOWN;
};

struct Node
{
    Variant data;
    std::shared_ptr<Node> next;

    Node(const Variant &val) : data(val), next(nullptr) {}
};

class VariantList
{
public:
    VariantList() : head(nullptr) {}

    void append(const Variant &other)
    {
        auto newNode = std::make_shared<Node>(other);
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
        auto temp = head;
        while (temp)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    ~VariantList() = default;

private:
    std::shared_ptr<Node> head;
};

int main()
{
    VariantList list;

    list.append(Variant(40));
    list.append(Variant("hello"));
    list.append(Variant(67.89));
    list.append(Variant("testing"));

    list.display();

    return 0;
}