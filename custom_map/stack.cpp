#include "stack.h"

stack::stack()
{
	first = nullptr;
	size = 0;
}

void stack::push(node* key)
{
    component* newNode = new component;
    newNode->setKey(key);
    newNode->setUp_Left(nullptr);
    newNode->setDown_Right(first);

    if (first)
        first->setUp_Left(newNode);


    first = newNode;

    size++;
}

void stack::pop()
{
    if (!first) return;

    component* current = first->getDown_Right();

    if (current)
        current->setUp_Left(nullptr);

    delete first;
    first = current;

    size--;
}

bool stack::empty()
{
    if (first ==nullptr)
        return true;
    
    return false;
}

void stack::clear()
{
    while (empty()==false)
        pop();
}

node* stack::top()
{
    return first->getKey();
}


