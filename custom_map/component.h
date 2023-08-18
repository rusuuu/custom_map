#pragma once

#include "node.h"

class component
{
private:

	node* key;
	component* up_left, * down_right;

public:

	component(node* = nullptr);

	void setKey(node*);
	node* getKey();

	void setUp_Left(component*);
	component* getUp_Left();

	void setDown_Right(component*);
	component* getDown_Right();
};


