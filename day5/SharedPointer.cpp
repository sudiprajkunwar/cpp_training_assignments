#include <iostream>

template <typename T>
class SharedPointer
{
public:
    // Constructor
    SharedPointer(const T &val)
    {
        m_val = new T(val);
        m_refCount = new long(1);
        std::cout << "parameter Constructor: Reference count is now " << *m_refCount << "\n";
    }

    // Copy Constructor
    SharedPointer(const SharedPointer &other)
    {

        m_val = other.m_val;
        m_refCount = other.m_refCount;
        ++(*m_refCount);
        std::cout << "Copy Constructor: Reference count is now " << *m_refCount << "\n";
    }

    // Copy Assignment Operator
    SharedPointer &operator=(const SharedPointer &other)
    {
        std::cout << "Copy Assignment: Reference count is now " << *m_refCount << "\n";

        if (this == &other) // Self-assignment check
        {
            return *this;
        }

        // Release current resources
        if (m_refCount && --(*m_refCount) == 0)
        {
            delete m_val;
            delete m_refCount;
        }

        // Copy resources from other
        m_val = other.m_val;
        m_refCount = other.m_refCount;
        ++(*m_refCount);

        return *this;
    }

    // Move Constructor
    SharedPointer(SharedPointer &&other) noexcept
    {
        m_val = other.m_val;
        m_refCount = other.m_refCount;

        other.m_val = nullptr;
        other.m_refCount = nullptr;
    }

    // Move Assignment Operator
    SharedPointer &operator=(SharedPointer &&other) noexcept
    {
        if (this == &other) // Self-assignment check
        {
            return *this;
        }

        // Release current resources
        if (m_refCount && --(*m_refCount) == 0)
        {
            delete m_val;
            delete m_refCount;
        }

        // Move resources from other
        m_val = other.m_val;
        m_refCount = other.m_refCount;

        other.m_val = nullptr;
        other.m_refCount = nullptr;

        return *this;
    }

    // Dereference Operator
    T &operator*() const
    {
        return *m_val;
    }

    // Destructor
    ~SharedPointer()
    {
        if (m_refCount && --(*m_refCount) == 0)
        {
            delete m_val;
            delete m_refCount;
        }
    }

private:
    T *m_val = nullptr;
    long *m_refCount = nullptr;
};

int main()
{

    SharedPointer<int> sp1(5);
    SharedPointer<int> sp2(sp1);  // Copy constructor
    SharedPointer<int> sp3 = sp1; // Copy constructor

    std::cout << *sp1 << "\n"; // Outputs 5
    std::cout << *sp2 << "\n"; // Outputs 5
    std::cout << *sp3 << "\n"; // Outputs 5

    sp3 = sp2;                 // Copy assignment operator
    std::cout << *sp3 << "\n"; // Outputs 5

     return 0;
}
