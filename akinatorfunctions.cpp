#include "akinator.h"

tree::tree()
{
    std::cout << "+++ CONSTRUCTION +++ \n" << std::endl;

    numOfEl_ = 0;
    numOfLevels_ = 0;

    head_ = new treeEl;
    head_ -> num = 0;
    head_ -> lower = nullptr;
    head_ -> bigger = nullptr;
    head_ -> level = 0;
}

void tree::textDump()
{
    std::cout << "Dump:"<< std::endl;
    recursiveDump(head_);
}

void recursiveDump(treeEl* node)
{
    std::cout << "{" << std::endl;

    std::cout << node -> num << std::endl;

    if(node -> lower != nullptr)
        recursiveDump(node -> lower);
    if(node -> bigger != nullptr)
        recursiveDump(node -> bigger);

    std::cout << "}" << std::endl;
}

treeEl* tree::treeSearch (int val, int* searchStat)
{
    std::cout << "SEARCH:" << std::endl;
    assert(searchStat != nullptr);

    treeEl* node = head_;
    assert(node != nullptr);

    treeEl* prevNode = node;

    while(node != nullptr)
    {
        if (node -> num == val)
        {
            std::cout << "Элемент " << val <<" найден."<< std::endl;
            *searchStat = FOUND;
            return node;
        }
        
        else if (node -> num < val)
        {
            prevNode = node;
            node = node -> bigger;
        }

        else
        {
            prevNode = node; 
            node = node -> lower;
        } 
    }

    std::cout << "Элемент " << val <<" не найден."<< std::endl;

    *searchStat = NOTFOUND;

    return prevNode;
}

treeEl* tree::treeInsert (int val)
{
    std::cout << "INSERT: \n" << std::endl;
    int searchStat;

    treeEl* node = treeSearch(val, &searchStat);

    if (searchStat == FOUND)
    {
        std::cout << "Элемент уже есть в дереве!" << std::endl;
        return node;
    }

    if(val > node -> num)
    {
        node -> bigger = new treeEl;
        node -> bigger -> num = val;
        node -> bigger -> bigger = nullptr;
        node -> bigger -> lower = nullptr;
        node -> bigger -> level = (node -> level) + 1;
        numOfEl_ ++;
        numOfLevels_ ++;

        std::cout << "Элемент успешно вставлен!" << std::endl;
        return node -> bigger;
    }

    else
    {
        node -> lower = new treeEl;
        node -> lower -> num = val;
        node -> lower -> bigger = nullptr;
        node -> lower -> lower = nullptr;
        node -> lower -> level = (node -> level) + 1;
        numOfEl_ ++;
        numOfLevels_ ++;

        std::cout << "Элемент успешно вставлен!" << std::endl;
        return node -> lower;
    }

}