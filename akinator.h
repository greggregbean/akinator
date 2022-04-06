#ifndef AKINATOR_H
#define AKINATOR_H

#include <iostream>
#include <assert.h>

#define FOUND 1
#define NOTFOUND 0

struct treeEl
{
    int num;
    size_t level;
    treeEl* bigger;
    treeEl* lower;
};

class tree
{
    private:
        treeEl* head_;
        size_t numOfEl_;
        size_t numOfLevels_;

    public:
        tree();
        void textDump();
        treeEl* treeSearch (int val, int* searchStat);
        treeEl* treeInsert (int val);
};

void recursiveDump(treeEl* node);



#endif