#include "queue.h"


queue::queue()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void queue::push(node* key)
{
    component* newNode = new component;
    newNode->setKey(key);
    newNode->setUp_Left(tail);
    newNode->setDown_Right(nullptr);

    if (tail)
        tail->setDown_Right(newNode);
    else
        head = newNode;

    tail = newNode;

    size++;
}

void queue::pop()
{
    if (!head)
        return;

    component* current = head->getDown_Right();

    if (current)
        current->setDown_Right(nullptr);
    else
        tail = nullptr;

    delete head;
    head = current;

    size--;
}

bool queue::empty()
{
    if (head == nullptr)
        return true;

    return false;
}

void queue::clear()
{
    while (empty() == false)
        pop();
}

node* queue::front()
{
    return head->getKey();
}

node* queue::back()
{
    return tail->getKey();
}
