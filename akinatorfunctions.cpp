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
}

void recursiveDump(treeEl* node)
{
    std::cout << "{" << std::endl;

    std::cout << node -> phrase << std::endl;

    if(node -> yes != nullptr)
        recursiveDump(node -> yes);
    if(node -> no != nullptr)
        recursiveDump(node -> no);

    std::cout << "}" << std::endl;
}

/*treeEl* tree::akinator ()
{
    std::cout << "SEARCH:" << std::endl;

    treeEl* node = head_;
    assert(node != nullptr);

    treeEl* prevNode = node;

    while(node != nullptr)
    {
        char answer;

        std::cout << "\"" << node -> phrase << "\"? (y/n) " << std::endl;
        std::cin >> answer; 

        if (answer == 'y')
        {
            if(node -> yes == nullptr)
            {
                std::cout << "Ваш персонаж \"" << node -> phrase << "\"." << std::endl;
                return node;
            }

            else
                node = node -> yes;
        }
        
        else
        {
            if(node -> no == nullptr)
            {
                char addAnswer;
                std::cout << "Программа не знает персонажа \"" << node -> phrase << "\". Хотите его добавить?" << std::endl;
                std::cin >> addAnswer;

                if(addAnswer == 'y')
                {
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
}*/

void liner(FILE* fp, char* treeBuf)
{
    char symbol = getc(fp);

    int i = 0;

    while(symbol != EOF)
    {
        if((symbol != '\n') && (symbol != ' ') && (symbol != '\r') && (symbol != '\t'))
        {
            treeBuf[i] = symbol; 
            i++;
        }

        symbol = getc(fp);
    }
}

treeEl* treeInsert (char* phrase)
{   
    treeEl* newNode = new treeEl;
    newNode -> phrase = phrase;
    newNode -> yes = nullptr;
    newNode -> no = nullptr;

    return newNode;
}

void recursiveReader (FILE* textTree, int* index)
{   
    char* phrase = (char*) calloc (PHRASEMAXLEN, sizeof(char));
    
    //Пропускаем {
    (*index)++;

    for((*index); (textTree != '}') && (textTree != '{'); (*index)++)
    {

    }

    //Если нет '}' рекурсивно вызываем функцию для поддерева yes
    if(textTree[index] != '}')
    {
        fseek(textTree, -1, SEEK_CUR);
        node -> yes = recursiveReader(textTree); 
    }

    //Если есть '{' рекурсивно вызываем функцию для поддерева no
    else
    {
        printf("%c \n", symbol);
        spaceSkip(textTree);
        node -> no = recursiveReader(textTree);
    } 

    return node;*/
}

void tree::reader(FILE* textTree)
{
    //Закинули всё в буффер
    char* treeBuf = (char*) calloc(TREEBUFLEN, sizeof(char)); 
    liner(textTree, treeBuf);

    //Распечатали буффер
    for(int i = 0; treeBuf[i] != '\0'; i++)
    {
        printf("%c", treeBuf[i]);
    }
    printf("\n");

    //Запустили рекурсивную читалку буффера
    int index = 0;
    recursiveReader(treeBuf, &index);
}