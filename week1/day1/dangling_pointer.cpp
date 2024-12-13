#include <iostream>

void danglingPointer()
{
    int *ptr = new int(2); // Dynamically allocate memory
    std::cout << "Dynamically allocated: *ptr = " << *ptr << std::endl;

    delete ptr; // Free the memory to avoid memory leak

    // Now ptr is a dangling pointer because ptr value is deleted.
    std::cout << "Outside the block: *ptr (dangling) = " << *ptr << std::endl; // Undefined behavior
}

// Solution: Avoid dangling pointer by proper memory management
void safePointer()
{
    int *ptr = new int(2); // Dynamically allocate memory
    std::cout << "Dynamically allocated: *ptr = " << *ptr << std::endl;

    delete ptr;    // Free the memory to avoid memory leak
    ptr = nullptr; // Set ptr to nullptr to avoid dangling
}

int main()
{
    std::cout << "--- Dangling Pointer Example ---\n";
    danglingPointer();

    std::cout << "\n--- Safe Pointer  ---\n";
    safePointer();

    return 0;
}
