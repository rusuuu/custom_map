#include "element.h"

element::element()
{
    this->status = 'f';
    this->key = "";
    this->value = candidate();
    this->linkToNode = nullptr;
    this->linkToIt = nullptr;
}

element::element(std::string key, candidate value)
{
    this->status = 'f';
    this->key = key;
    this->value = value;
    this->linkToNode = nullptr;
    this->linkToIt = nullptr;
}

void element::setStatus(char status)
{
    if (status == 'o' || status == 'f' || status == 'd')
        this->status = status;
}

char element::getStatus()
{
    return this->status;
}

void element::setKey(std::string key)
{
    this->key = key;
}

std::string element::getKey()
{
    return this->key;
}

void element::setValue(candidate value)
{
    this->value = value;
}

candidate element::getValue()
{
    return this->value;
}

void element::setLinkToNode(node* Node)
{
    linkToNode = Node;
}

node* element::getLinkToNode()
{
    return linkToNode;
}

void element::setLinkToIt(element* Element)
{
    linkToIt = Element;
}

element* element::getLinkToIt()
{
    return linkToIt;
}
