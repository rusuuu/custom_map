#pragma once
#include "candidate.h"
#include "element.h"

class element;

class node
{
protected:

	candidate key;
	node* left, * right, * parent;
	unsigned int height;
	int balanceFactor;
	element* linkToElement;
	node* linkToIt;
	unsigned int rank;

public:

	node();
	node(candidate);

	void setKey(candidate);
	candidate getKey();

	void setLeft(node*);
	node* getLeft();

	void setRight(node*);
	node* getRight();

	void setParent(node*);
	node* getParent();

	void setHeight(unsigned int);
	unsigned int getHeight();

	void setBalanceFactor(int);
	int getBalanceFactor();

	void setLinkToElement(element*);
	element* getLinkToElement();

	void setLinkToIt(node*);
	node* getLinkToIt();

	void setRank(unsigned int);
	unsigned int getRank();
};

