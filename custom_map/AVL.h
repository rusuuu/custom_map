#pragma once
#include "node.h"
#include "stack.h"
#include "queue.h"

class AVL
{
protected:

	node* root;
	unsigned int size, height;
	bool ranked;

	node* find(candidate);

	void recalculateHeightAndBalanceFactorAtInsertion(node*);
	void recalculateHeightAndBalanceFactorAtErasion(node*, node*);
	void recalculateTreeHeight();
	void recalculateNodeHeight(node*);
	void recalculateNodeBalanceFactor(node*);

	void rightRotation(node*);
	void leftRotation(node*);
	void rotationManager(node*);

	node* getPredecessor(node*);
	node* getSuccessor(node*);

	void transplant(node*, node*);

	void rankManager();

public:

	AVL();
	AVL(candidate);
	~AVL();

	void setRoot(node*);
	node* getRoot();

	void insert(candidate, element*);

	void erase(candidate);
	void erase(node*);

	void clear(node*);

	void inorder(node*);

	void findNthNode(unsigned int);
	void gradesInBetween(float begin, float end);
};
