
#include <iostream>
using namespace std;

int add(int a, int b)
{
    while (b != 0)
    {
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }

    return a;
};

int subtract(int a, int b)
{
    while (b != 0)
    {
        int borrow = (~a) & b;
        a = a ^ b;
        b = borrow << 1;
    }
    return a;
}

int main()
{
    int num1, num2;

    // Input two numbers
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    // Perform addition
    int sum = add(num1, num2);
    cout << "Sum: " << sum << endl;

    // Perform subtraction
    int difference = subtract(num1, num2);
    cout << "Difference: " << difference << endl;

    return 0;
}
