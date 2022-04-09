#include "akinator.h"

int main()
{
    FILE* textTree = fopen("textTree.txt", "r");
    tree tr;
    tr.reader(textTree);

    return 0;
}