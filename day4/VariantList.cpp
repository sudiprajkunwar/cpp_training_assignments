#include <iostream>
#include "../day2-3/let.cpp"

struct Node
{
    Let data;
    Node *next;

    Node(const Let &val) : data(val), next(nullptr) {}
};

class VariantList
{
public:
    VariantList() : head(nullptr) {}

    void append(Let other)

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

int main()
{

    VariantList list;

    list.append(40);
    list.append("hello");
    list.append(67.89);
    list.append("testing");

    list.display();

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

    Let var5("Hello");
    Let var6("Hello");

    // == operator
    if (var5 == var6)
    {
        std::cout << "var5 == var6 -> This condition satisfies\n";
    }

    return 0;
}