#include "node.h"

node::node()
{
	this->key = candidate();
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
	this->height = 0;
	this->balanceFactor = 0;
	this->linkToElement = nullptr;
	this->linkToIt = nullptr;
}

node::node(candidate key): key(key)
{
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
	this->height = 1;
	this->balanceFactor = 0;
	this->linkToElement = nullptr;
	this->linkToIt = nullptr;
}

void node::setKey(candidate key)
{
	this->key = key;
}

candidate node::getKey()
{
	return this->key;
}

void node::setLeft(node* Node)
{
	this->left = Node;
}

node* node::getLeft()
{
	return this->left;
}

void node::setRight(node* Node)
{
	this->right = Node;
}

node* node::getRight()
{
	return this->right;
}

void node::setParent(node* Node)
{
	this->parent = Node;
}

node* node::getParent()
{
	return this->parent;
}

void node::setHeight(unsigned int height)
{
	this->height = height;
}

unsigned int node::getHeight()
{
	return this->height;
}

void node::setBalanceFactor(int balance_factor)
{
	this->balanceFactor = balance_factor;
}

int node::getBalanceFactor()
{
	return this->balanceFactor;
}

void node::setLinkToElement(element* Element)
{
	linkToElement = Element;
}

element* node::getLinkToElement()
{
	return linkToElement;
}

void node::setLinkToIt(node* Node)
{
	linkToIt = Node;
}

node* node::getLinkToIt()
{
	return linkToIt;
}

void node::setRank(unsigned int rank)
{
	this->rank = rank;
}

unsigned int node::getRank()
{
	return this->rank;
}
