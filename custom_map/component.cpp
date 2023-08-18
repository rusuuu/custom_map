#include "component.h"

component::component(node* key):key(key)
{
	up_left = nullptr;
	down_right = nullptr;
}

void component::setKey(node* key)
{
	this->key = key;
}

node* component::getKey()
{
	return key;
}

void component::setUp_Left(component* up)
{
	this->up_left = up;
}

component* component::getUp_Left()
{
	return up_left;
}

void component::setDown_Right(component* down)
{
	this->down_right = down;
}

component* component::getDown_Right()
{
	return down_right;
}

