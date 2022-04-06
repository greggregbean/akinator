#include "akinator.h"

int main()
{
    tree tr;
    int searchStat = 0;

    tr.treeInsert(1);
    tr.treeInsert(2);
    tr.treeInsert(4);
    tr.treeInsert(-1);

    tr.textDump();
    tr.treeSearch(1, &searchStat);

}