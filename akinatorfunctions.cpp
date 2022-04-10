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
            node -> phrase, node -> phrase, node, node -> yes, node -> no);
    
    if (node -> yes != nullptr)
    {
        fprintf(filep, " %s -> %s; \n", node -> phrase, node -> yes -> phrase);
        recursiveGraph(filep, node -> yes);
    }

    if (node -> no != nullptr)
    {
        fprintf(filep, " %s -> %s; \n", node -> phrase, node -> no -> phrase);
        recursiveGraph(filep, node -> no);
    }
}

void tree::graphDump(FILE* filep)
{
    printf("Recursive reade: ");

    fprintf(filep, "digraph \n{\n");
    recursiveGraph(filep, head_);
    fprintf(filep, "}");

    printf("your graph in \"graph.dot\". \n");
}

treeEl* tree::akinator ()
{
    std::cout << "+++ AKINATOR +++" << std::endl;

    treeEl* node = head_;
    assert(node != nullptr);

    treeEl* prevNode = node;

    while(node != nullptr)
    {
        char answer;

        printf("Your chracter is %s? (y/n)", node -> phrase);
        scanf("%c", &answer);

        if (answer == 'y')
        {
            if(node -> yes == nullptr)
            {
                printf("I guessed your character. It is %s.", node -> phrase);
                return node;
            }

            else
                node = node -> yes;
        }
        
        else
        {
            if(node -> no == nullptr)
            {
                printf("I don't know your character. Do you want to add him? (y/n) \n";

                char addAnswer;
                scanf("%c", addAnswer);
                
                if(addAnswer == 'y')
                {
                    printf("What is name of your character?");

                    char* phrase = (char*) calloc(PHRASEMAXLEN, sizeof(char));
                    printf("Tell me the di")
                    return treeInsert(node -> no);
                }

                else
                {
                    std::cout << "Персонаж не добавлен." << std::endl;
                    return nullptr;  
                }   
            }

            else
                node = node -> no;
        }
    }
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

treeEl* treeInsert (treeEl* newNode, char* phrase)
{   
    newNode -> phrase = phrase;
    newNode -> yes = nullptr;
    newNode -> no = nullptr;

    return newNode;
}

void nodeDump(treeEl* node)
{
    printf("Addr: %p, ", node);
    printf("Phrase: \"%s\"", node -> phrase);
    printf("(Yes: %p, ", node -> yes);
    printf("No: %p); \n", node -> no);
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

    //printf("прочли название: \"%s\" \n", treeBuf + *index);
    
    //Cоздаем новый узел
    treeEl* node = new treeEl{};
    treeInsert(node, phrase);

    //Если есть '{' рекурсивно вызываем функцию для поддерева yes
    if(treeBuf[(*index)] == '{')
    {
        node -> yes = recursiveReader(treeBuf, index); 
        node -> no = recursiveReader(treeBuf, index);
    }

    //printf("сча рванёт: \"%s\" \n", treeBuf + *index);
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