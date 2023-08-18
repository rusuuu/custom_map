#pragma once

#include <iostream>
#include <fstream>
#include "element.h"

class hashTable
{
private:

    element* table;
    int tableCapacity;
    double loadFactor;
    double contaminationFactor;

public:

    hashTable();
    ~hashTable();

    int primaryHash(std::string, unsigned int);
    void rehashing();

    void insertElem(element);

    int findElem(candidate);

    void eraseElem(candidate);
    void clear();

    void write();

    element* getElementAdress(int);

    node* getLinkToNode(int);
};


