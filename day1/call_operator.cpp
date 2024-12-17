#include <iostream>

class Addition
{

public:
    // Constructor
    Addition(int f) : m_val(f) {}

    // Overload the call operator
    int operator()(int number)
    {
        return number + m_val;
    }

private:
    int m_val;
};

int main()
{
    Addition addFive(5);

    int a = 3;

    // Use the overloaded call operator
    int result = addFive(3);

    std::cout << "Result of adding is " << result << std::endl;

    return 0;
}
