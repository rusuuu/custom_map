#pragma once

#include "AVL.h"
#include "hashTable.h"

class AVL_hashTable
{
private:

	AVL tree;
	hashTable table;

public:

	void insert(element);

	void erase(candidate);

	node* findInTree(candidate);
	int findInTable(candidate);

	void writeTree();
	void writeTable();

	void clear();
};

element readFromFile(std::ifstream& input);


