#include "VariantList.cpp"

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