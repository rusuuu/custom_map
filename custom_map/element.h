#pragma once

#include <iostream>
#include "candidate.h"
#include "node.h"

class node;

class element
{
private:

    char status;
    std::string key;
    candidate value;
    node* linkToNode;
    element* linkToIt;

public:

    element();

    element(std::string, candidate);

    void setStatus(char);
    char getStatus();

    void setKey(std::string);
    std::string getKey();

    void setValue(candidate);
    candidate getValue();

    void setLinkToNode(node*);
    node* getLinkToNode();

    void setLinkToIt(element*);
    element* getLinkToIt();
};

