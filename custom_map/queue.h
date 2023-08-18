#pragma once

#include "component.h"

class queue
{
private:

	component* head, * tail;
	unsigned int size;

public:

	queue();

	void push(node* key);
	void pop();

	bool empty();

	void clear();

	node* front();
	node* back();
};


