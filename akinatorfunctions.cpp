#include "akinator.h"

tree::tree()
{
    head_ = new treeEl;
    head_ -> phrase = new char [PHRASEMAXLEN];
    head_ -> yes = nullptr;
    head_ -> no = nullptr;
}

void tree::textDump()
{
    std::cout << "Text dump:"<< std::endl;
    recursiveDump(head_);
    printf("\n");
}

void recursiveDump(treeEl* node)
{
    printf("{\n");

    printf("%s \n", node -> phrase);

    if (node -> yes != nullptr)
        recursiveDump(node -> yes);
    if (node -> no != nullptr)
        recursiveDump(node -> no);

    printf("}\n");
}

void recursiveGraph(FILE* filep, treeEl* node)
{
    fprintf(filep, " %s [shape=record, fillcolor = darkkhaki, style = filled, label = \" { %s | Addr: %p | {Yes: %p | No: %p }}\" ] \n",     
            node -> phrase, node -> phrase, (void*) node, (void*) node -> yes, (void*) node -> no);
    
    if (node -> yes != nullptr)
    {
        fprintf(filep, " %s -> %s [label = \" Yes \"]; \n", node -> phrase, node -> yes -> phrase);
        recursiveGraph(filep, node -> yes);
    }

    if (node -> no != nullptr)
    {
        fprintf(filep, " %s -> %s [label = \" No \"]; \n", node -> phrase, node -> no -> phrase);
        recursiveGraph(filep, node -> no);
    }
}

void tree::graphDump(FILE* filep)
{
    printf("GraphDump: ");

    fprintf(filep, "digraph \n{\n");
    recursiveGraph(filep, head_);
    fprintf(filep, "}");

    printf("your graph in \"graph.dot\". \n");
}

void tree::fileDump(FILE* filep)
{
    printf("File dump:");
    recursiveFileDump(filep, head_);
    printf(" tree in \"textTree.txt\". ");
    printf("\n");    
}

void recursiveFileDump(FILE* filep, treeEl* node)
{
    fprintf(filep, "{\n");

    fprintf(filep, "%s \n", node -> phrase);

    if (node -> yes != nullptr)
        recursiveFileDump(filep, node -> yes);
    if (node -> no != nullptr)
        recursiveFileDump(filep, node -> no);

    fprintf(filep, "}\n");
}

treeEl* treeInsert (char* phrase)
{   
    treeEl* newNode = new treeEl{};

    newNode -> phrase = phrase;
    newNode -> yes = nullptr;
    newNode -> no = nullptr;

    return newNode;
}

treeEl* tree::akinator ()
{
    printf("+++ AKINATOR +++ \n");

    treeEl* node = head_;
    assert(node != nullptr);

    while(node != nullptr)
    {
        printf("Your chracter is %s? (y/n) \n", node -> phrase);

        char answer[PHRASEMAXLEN];

        scanf("%s", answer);

        while((strcmp(answer,"y") != 0) && (strcmp(answer, "n") != 0))
        {
            printf("Please enter 'y' or 'n'. \n");
            scanf("%s", answer);
        }

        while(getchar() != '\n') ;

        if (answer[0] == 'y')
        {
            if(node -> yes == nullptr)
            {
                printf("I guessed your character. It is %s. \n", node -> phrase);
                return node;
            }

            else
                node = node -> yes;
        }
        
        else if (answer[0] == 'n')
        {
            if(node -> no == nullptr)
            {
                printf("I don't know your character. Do you want to add him? (y/n) \n");

                char addAnswer[PHRASEMAXLEN];

                scanf("%s", addAnswer);

                while((strcmp(addAnswer,"y") != 0) && (strcmp(addAnswer, "n") != 0))
                {
                    printf("Please enter 'y' or 'n'. \n");
                    scanf("%s", addAnswer);
                }
                
                if(addAnswer[0] == 'y')
                {
                    printf("What is name of your character? \n");
                    char* pers = (char*) calloc(PHRASEMAXLEN, sizeof(char));
                    scanf("%s", pers);

                    printf("What is the distinguishing feature of your character from %s? \n", node -> phrase);
                    char* difference = (char*) calloc(PHRASEMAXLEN, sizeof(char));
                    scanf("%s", difference);

                    node -> no = treeInsert(node -> phrase);
                    node -> yes = treeInsert(pers);
                    node -> phrase = difference;

                    printf("%s has been added to akinator's data. \n", node -> yes -> phrase);

                    return node -> yes;
                }

                else if(addAnswer[0] == 'n')
                {
                    printf("Your character has not been added. \n");
                    return nullptr;  
                }
            }

            else
                node = node -> no;
        }
    }

    return node;
}

void liner(FILE* fp, char* treeBuf)
{
    char symbol = getc(fp);

    int i = 0;

    while(symbol != EOF)
    {
        if(symbol)
        if((symbol != '\n') && (symbol != ' ') && (symbol != '\r') && (symbol != '\t'))
        {
            treeBuf[i] = symbol; 
            i++;
        }

        symbol = getc(fp);
    }
}

void nodeDump(treeEl* node)
{
    printf("Addr: %p, ", (void*) node);
    printf("Phrase: \"%s\"", node -> phrase);
    printf("(Yes: %p, ", (void*) node -> yes);
    printf("No: %p); \n", (void*) node -> no);
}

treeEl* recursiveReader (char* treeBuf, int* index)
{   
    char* phrase = (char*) calloc (PHRASEMAXLEN, sizeof(char));

    //Пропускаем '{'
    assert(treeBuf[*index] == '{');
    (*index)++;

    int i = 0;

    while((treeBuf[*index] != '}') && (treeBuf[*index] != '{'))
    {
        phrase[i] = treeBuf[*index];
        (*index)++;
        i++;
    }
    
    //Cоздаем новый узел
    treeEl* node = treeInsert(phrase);

    //Если есть '{' рекурсивно вызываем функцию для поддерева yes
    if(treeBuf[(*index)] == '{')
    {
        node -> yes = recursiveReader(treeBuf, index); 
        node -> no = recursiveReader(treeBuf, index);
    }

    nodeDump(node);
    assert(treeBuf[(*index)] == '}');

    (*index)++;

    return node;
}

void tree::reader(FILE* textTree)
{
    printf("READER: \n");

    //Закинули всё в буффер
    char* treeBuf = (char*) calloc(TREEBUFLEN, sizeof(char)); 
    liner(textTree, treeBuf);

    //Распечатали буффер
    printf("Data in buffer: ");
    for(int i = 0; treeBuf[i] != '\0'; i++)
    {
        printf("%c", treeBuf[i]);
    }
    printf("\n");

    //Запустили рекурсивную читалку буффера
    int index = 0;
    head_ = recursiveReader(treeBuf, &index);
    printf("\n");
}