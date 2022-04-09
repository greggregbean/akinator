#ifndef AKINATOR_H
#define AKINATOR_H

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <fstream>
#include <string.h>
#include <ctype.h>

#define FOUND 1
#define NOTFOUND 0
#define PHRASEMAXLEN 50
#define TREEBUFLEN 1000

struct treeEl
{
    char* phrase;
    treeEl* yes;
    treeEl* no;
};

class tree
{
    private:
        treeEl* head_;

    public:
        tree();
        void textDump();
        void reader(FILE* textTree);
        treeEl* akinator();
};

treeEl* treeInsert (char* phrase);
void recursiveDump(treeEl* node);
void recursiveReader(char* treeBuf, int* index);
char* liner(FILE *fp);

#endif