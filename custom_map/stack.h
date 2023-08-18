#pragma once

#include "component.h"

class stack
{
private:

	component* first;
	unsigned int size;

public:

	stack();

	void push(node* key);
	void pop();

	bool empty();

	void clear();

	node* top();
};


