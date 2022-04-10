#include "akinator.h"

int main()
{
    FILE* textTree = fopen("textTree.txt"  , "r");
    FILE* graph    = fopen("gpraph.dot", "w");
    tree tr;
    tr.reader(textTree);
    tr.textDump();
    while(true)
    {
        tr.akinator();
        printf("Do you want to play again? (y/n) \n");
        char answer;
        scanf("%c", &answer);
        printf("\n");
        while (getchar() != '\n') ;
        if(answer != 'y')
        {
            printf("Thanks for the game. \n");
            break;
        }
    }
    tr.graphDump(graph);

    return 0;
}