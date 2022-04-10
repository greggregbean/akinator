#include "akinator.h"

int main()
{
    FILE* textTree = fopen("textTree.txt"  , "r");
    FILE* graph    = fopen("gpraphDump.dot", "w");
    tree tr;
    tr.reader(textTree);
    tr.textDump();
    tr.graphDump(graph);

    return 0;
}