#include "AVL.h"
#include <iostream>

node* AVL::find(candidate key)
{
	node* parent = nullptr;
	node* current = this->root;
	
	while (current != nullptr)
	{
		parent = current;

		if (key == current->getKey())
			return current;

		if (key < current->getKey())
			current = current->getLeft();
		else
			current = current->getRight();
	}

	return nullptr;
}

void AVL::recalculateHeightAndBalanceFactorAtInsertion(node* Node)
{
	node* parent = Node->getParent();
	
	node* leftBrother = Node->getParent()->getLeft();
	node* rightBrother = Node->getParent()->getRight();

	//if the node is the root any operation is nonsense
	if (parent == nullptr)
		return;
	
	//if the inserted node has a brother it doesn't make sense to recalculate the height in an AVL, so we only set the balance factor of its parent to 0
	if (Node == leftBrother)
	{
		if (rightBrother != nullptr)
		{
			parent->setBalanceFactor(0);
			return;
		}
	}
	else
	{
		if (leftBrother != nullptr)
		{
			parent->setBalanceFactor(0);
			return;
		}
	}
	
	unsigned int leftHeight, rightHeight;
	int balance_factor = 0;

	do
	{
		//recalculating the height

		if (parent->getLeft() == nullptr)
			leftHeight = 0;
		else
			leftHeight = parent->getLeft()->getHeight();

		if (parent->getRight() == nullptr)
			rightHeight = 0;
		else
			rightHeight = parent->getRight()->getHeight();

		parent->setHeight(leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1);

		//recalculating the balance factor

		balance_factor = 0;

		if (parent->getRight() != nullptr)
			balance_factor += parent->getRight()->getHeight();

		if (parent->getLeft() != nullptr)
			balance_factor -= parent->getLeft()->getHeight();

		parent->setBalanceFactor(balance_factor);
		
		if (parent->getBalanceFactor() == 2 || parent->getBalanceFactor() == -2)
		{
			rotationManager(parent);
		}

		parent = parent->getParent();

	} while (balance_factor != 0 && parent != nullptr);
}

void AVL::recalculateHeightAndBalanceFactorAtErasion(node* Node, node* deletedSuccessor)
{
	node* parent = Node;

	if (parent == nullptr)
		return;
	
	unsigned int leftHeight, rightHeight;
	int balance_factor = 0;

	if (deletedSuccessor != nullptr)
	{
		recalculateNodeHeight(deletedSuccessor);
		recalculateNodeBalanceFactor(deletedSuccessor);
	}

	do
	{
		//recalculating the height

		if (parent->getLeft() == nullptr)
			leftHeight = 0;
		else
			leftHeight = parent->getLeft()->getHeight();

		if (parent->getRight() == nullptr)
			rightHeight = 0;
		else
			rightHeight = parent->getRight()->getHeight();

		parent->setHeight(leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1);

		//recalculating the balance factor

		balance_factor = 0;

		if (parent->getRight() != nullptr)
			balance_factor += parent->getRight()->getHeight();

		if (parent->getLeft() != nullptr)
			balance_factor -= parent->getLeft()->getHeight();

		parent->setBalanceFactor(balance_factor);

		//if the new nde has the new balance factor -2 and his left one 0 or +2 and his right one 0 it doesn't make sense to continue recalculating the height   

		if (parent->getBalanceFactor() == 2)
		{
			if (parent->getRight()->getBalanceFactor() == 0)
				if (deletedSuccessor != nullptr && deletedSuccessor->getBalanceFactor() == 0)
				{
					rotationManager(parent);
					return;
				}
			else
				rotationManager(parent);
		}

		if (parent->getBalanceFactor() == -2)
		{
			if (parent->getLeft()->getBalanceFactor() == 0)
				if (deletedSuccessor != nullptr && deletedSuccessor->getBalanceFactor() == 0)
				{
					rotationManager(parent);
					return;
				}
			else
				rotationManager(parent);
		}

		//if it isn't a case from above we just rebalance the sub-tree and continue recalculating

		if (parent->getBalanceFactor() == 2 || parent->getBalanceFactor() == -2)
		{
			rotationManager(parent);
		}

		parent = parent->getParent();


	} while ((balance_factor != 1 && balance_factor != -1) && parent != nullptr);
}


void AVL::recalculateTreeHeight()
{
	this->height = this->root->getHeight() - 1;
}

void AVL::recalculateNodeHeight(node* Node)
{
	Node->setHeight(std::max((Node->getLeft() != nullptr ? Node->getLeft()->getHeight() : NULL), (Node->getRight() != nullptr ? Node->getRight()->getHeight() : NULL)) + 1);
}

void AVL::recalculateNodeBalanceFactor(node* Node)
{
	unsigned int balance_factor = 0;

	if (Node->getRight() != nullptr)
		balance_factor += Node->getRight()->getHeight();

	if (Node->getLeft() != nullptr)
		balance_factor -= Node->getLeft()->getHeight();

	Node->setBalanceFactor(balance_factor);
}

void AVL::leftRotation(node* Node)
{
	node* NodeRight = Node->getRight();
	Node->setRight(NodeRight->getLeft());

	if (NodeRight->getLeft() != nullptr)
		NodeRight->getLeft()->setParent(Node);

	NodeRight->setParent(Node->getParent());

	if (Node->getParent() == nullptr)
		this->root = NodeRight;
	else
	{
		if (Node == Node->getParent()->getLeft())
			Node->getParent()->setLeft(NodeRight);
		else
			Node->getParent()->setRight(NodeRight);
	}

	NodeRight->setLeft(Node);
	Node->setParent(NodeRight);

	if (NodeRight->getRight() != nullptr)
		recalculateNodeBalanceFactor(NodeRight->getRight());
	recalculateNodeHeight(Node);
	recalculateNodeBalanceFactor(Node);
	recalculateNodeHeight(NodeRight);
	recalculateNodeBalanceFactor(NodeRight);
}
 
void AVL::rightRotation(node* Node)
{
	node* NodeLeft = Node->getLeft();
	Node->setLeft(NodeLeft->getRight());

	if (NodeLeft->getRight() != nullptr)
		NodeLeft->getRight()->setParent(Node);

	NodeLeft->setParent(Node->getParent());

	if (Node->getParent() == nullptr)
		this->root = NodeLeft;
	else
	{
		if (Node == Node->getParent()->getRight())
			Node->getParent()->setRight(NodeLeft);
		else
			Node->getParent()->setLeft(NodeLeft);
	}

	NodeLeft->setRight(Node);
	Node->setParent(NodeLeft);

	if (NodeLeft->getLeft() != nullptr)
		recalculateNodeBalanceFactor(NodeLeft->getLeft());
	recalculateNodeHeight(Node);
	recalculateNodeBalanceFactor(Node);
	recalculateNodeHeight(NodeLeft);
	recalculateNodeBalanceFactor(NodeLeft);
}

void AVL::rotationManager(node* Node)
{
	if (Node == nullptr)
		return;

	if (Node->getBalanceFactor() == 2)
	{
		if (Node->getRight() == nullptr)
			return;

		if (Node->getRight()->getBalanceFactor() == 1 || Node->getRight()->getBalanceFactor() == 0)
		{
			leftRotation(Node);
			return;
		}
		
		if (Node->getRight()->getBalanceFactor() == -1)
		{
			rightRotation(Node->getRight()); 
			leftRotation(Node);
			return;
		}
	}

	if (Node->getBalanceFactor() == -2)
	{
		if (Node->getLeft() == nullptr)
			return;

		if (Node->getLeft()->getBalanceFactor() == -1 || Node->getLeft()->getBalanceFactor() == 0)
		{
			rightRotation(Node);
			return;
		}

		if (Node->getLeft()->getBalanceFactor() == 1)
		{
			leftRotation(Node->getLeft());
			rightRotation(Node);
			return;
		}
	}
}

node* AVL::getPredecessor(node* Node)
{
	if (Node == nullptr)
		return nullptr;

	if (Node->getLeft() != nullptr)
	{
		if (Node->getLeft()->getRight() == nullptr)
			return Node->getLeft();
		else
		{
			node* current = Node->getLeft()->getRight();;
			node* child = current->getRight();

			while (child != nullptr)
			{
				current = child;
				child = child->getRight();
			}

			return current;
		}
	}
	else
	{
		node* current = Node;
		node* parent = Node->getParent();

		while (parent != nullptr && parent->getRight() != current)
		{
			current = parent;
			parent = parent->getParent();
		}

		return parent;
	}
}

node* AVL::getSuccessor(node* Node)
{
	if (Node == nullptr)
		return nullptr;

	if (Node->getRight() != nullptr)
	{
		if (Node->getRight()->getLeft() == nullptr)
			return Node->getRight();
		else
		{
			node* current = Node->getRight()->getLeft();
			node* child = current->getLeft();
			
			while (child != nullptr)
			{
				current = child;
				child = child->getLeft();
			}

			return current;
		}
	}
	else
	{
		node* current = Node;
		node* parent = Node->getParent();

		while (parent != nullptr && parent->getLeft() != current)
		{
			current = parent;
			parent = parent->getParent();
		}

		return parent;
	}
}

void AVL::transplant(node* receiver, node* giver)
{
	if (receiver == nullptr)
		return;

	if (receiver->getParent() == nullptr)
		this->root = giver;
	else 
		if (receiver->getParent()->getLeft() == receiver)
			receiver->getParent()->setLeft(giver);
		else
			receiver->getParent()->setRight(giver);

	if (giver != nullptr)
		giver->setParent(receiver->getParent());
}

void reRank(node* root)
{
	if (root == nullptr)
		return;

	stack nodeStack;
	node* currentNode = root;

	unsigned int rank = 1;

	while (nodeStack.empty() == false || currentNode != nullptr)
	{
		if (currentNode != nullptr)
		{
			nodeStack.push(currentNode);

			currentNode = currentNode->getRight();
		}
		else
		{
			currentNode = nodeStack.top();
			nodeStack.pop();

			currentNode->setRank(rank);
			rank++;

			currentNode = currentNode->getLeft();
		}
	}
}

void AVL::rankManager()
{
	if (ranked == false)
	{
		reRank(this->root);
		this->ranked = true;
	}
	else
		return;
}

AVL::AVL()
{
	this->root = nullptr;
	this->size = 0;
	this->height = 0;
	ranked = false;
}

AVL::AVL(candidate key)
{
	this->root = new node(key);
	this->size = 1;
	this->height = 0;
	ranked = false;
}

AVL::~AVL()
{
	clear(root);
}

void AVL::setRoot(node* Node)
{
	this->root = Node;
}

node* AVL::getRoot()
{
	return this->root;
}

void AVL::insert(candidate key, element* Element)
{
	node* parent = nullptr;
	node* current = this->root;

	while (current != nullptr)
	{
		parent = current;

		if (key < current->getKey())
			current = current->getLeft();
		else
			if (key > current->getKey())
				current = current->getRight();
			else
				return;
	}


	node* newNode = new node(key);

	newNode->setParent(parent);

	newNode->setLinkToIt(newNode);
	newNode->setLinkToElement(Element);
	Element->setLinkToNode(newNode);

	if (parent == nullptr)
	{
		this->root = newNode;
		this->size++;
		recalculateTreeHeight();
		return;
	}
	else
		if (key < parent->getKey())
			parent->setLeft(newNode);
		else
			parent->setRight(newNode);

	this->size++;
	recalculateHeightAndBalanceFactorAtInsertion(newNode);
	recalculateTreeHeight();
	this->ranked = false;
}

void AVL::erase(candidate key)
{
	node* parent = nullptr;
	node* current = this->root;

	while (current != nullptr)
	{
		if (key == current->getKey())
			break;
		else
		{
			parent = current;

			if (key < current->getKey())
				current = current->getLeft();
			else
				current = current->getRight();
		}
	}
	if (current == nullptr)
		return;
	
	node* successor;
	if (getSuccessor(current) != nullptr)
		successor = getSuccessor(current);
	else
		successor = nullptr;

	if (current->getLeft() == nullptr)
	{
		transplant(current, current->getRight());
		recalculateHeightAndBalanceFactorAtErasion(parent, successor);
	}
	else if (current->getRight() == nullptr)
	{
		transplant(current, current->getLeft());
		recalculateHeightAndBalanceFactorAtErasion(parent, successor);
	}
	else
	{
		if (current == root)
		{
			node* predecessor = getPredecessor(current);

			if (current->getLeft() != predecessor)
			{
				transplant(predecessor, predecessor->getLeft());
				predecessor->setLeft(current->getLeft());
				current->getLeft()->setParent(predecessor);
			}

			transplant(current, predecessor);
			predecessor->setRight(current->getRight());
			current->getRight()->setParent(predecessor);

			recalculateNodeHeight(predecessor);
			recalculateNodeBalanceFactor(predecessor);
			if (predecessor->getLeft() != nullptr)
			{
				recalculateNodeHeight(predecessor->getLeft());
				recalculateNodeBalanceFactor(predecessor->getLeft());
				recalculateHeightAndBalanceFactorAtErasion(predecessor->getLeft(), nullptr);
			}
		}
		else
		{
			if (current->getRight() != successor)
			{
				transplant(successor, successor->getRight());
				successor->setRight(current->getRight());
				current->getRight()->setParent(successor);
			}

			transplant(current, successor);
			successor->setLeft(current->getLeft());
			current->getLeft()->setParent(successor);

			recalculateNodeHeight(successor);
			recalculateNodeBalanceFactor(successor);
			recalculateHeightAndBalanceFactorAtErasion(successor->getParent(), successor);
		}
	}
	delete current;

	this->size--;
	recalculateTreeHeight();
	this->ranked = false;
}

void AVL::erase(node* Node)
{
	node* parent = Node->getParent();
	node* current = Node;

	if (current == nullptr)
		return;

	node* successor;
	if (getSuccessor(current) != nullptr)
		successor = getSuccessor(current);
	else
		successor = nullptr;

	if (current->getLeft() == nullptr)
	{
		transplant(current, current->getRight());
		recalculateHeightAndBalanceFactorAtErasion(parent, successor);
	}
	else if (current->getRight() == nullptr)
	{
		transplant(current, current->getLeft());
		recalculateHeightAndBalanceFactorAtErasion(parent, successor);
	}
	else
	{
		if (current == root)
		{
			node* predecessor = getPredecessor(current);

			if (current->getLeft() != predecessor)
			{
				transplant(predecessor, predecessor->getLeft());
				predecessor->setLeft(current->getLeft());
				current->getLeft()->setParent(predecessor);
			}

			transplant(current, predecessor);
			predecessor->setRight(current->getRight());
			current->getRight()->setParent(predecessor);

			recalculateNodeHeight(predecessor);
			recalculateNodeBalanceFactor(predecessor);
			if (predecessor->getLeft() != nullptr)
			{
				recalculateNodeHeight(predecessor->getLeft());
				recalculateNodeBalanceFactor(predecessor->getLeft());
				recalculateHeightAndBalanceFactorAtErasion(predecessor->getLeft(), nullptr);
			}
		}
		else
		{
			if (current->getRight() != successor)
			{
				transplant(successor, successor->getRight());
				successor->setRight(current->getRight());
				current->getRight()->setParent(successor);
			}

			transplant(current, successor);
			successor->setLeft(current->getLeft());
			current->getLeft()->setParent(successor);

			recalculateNodeHeight(successor);
			recalculateNodeBalanceFactor(successor);
			recalculateHeightAndBalanceFactorAtErasion(successor->getParent(), successor);
		}
	}
	current->setLinkToElement(nullptr);
	delete current;

	this->size--;
	recalculateTreeHeight();
	this->ranked = false;
}

void AVL::clear(node* root)
{
	if (root == nullptr)
		return;

	stack nodeStack;
	node* lastVisitedNode = nullptr;

	while (!nodeStack.empty() || root != nullptr)
	{
		if (root != nullptr)
		{
			nodeStack.push(root);
			nodeStack.push(root);
			root = root->getLeft();
		}
		else
		{
			root = nodeStack.top();
			nodeStack.pop();

			if (!nodeStack.empty() && nodeStack.top() == root)
				root = root->getRight();
			else
			{
				node* temp = root;
				root = nullptr;

				if (temp != nullptr)
				{
					lastVisitedNode = temp;
					delete temp;
				}
			}
		}
	}

	this->root = nullptr;
	this->size = 0;
	this->height = 0;
}

void AVL::inorder(node* root)
{
	if (root == nullptr)
		return;

	stack nodeStack;
	node* currentNode = root;

	while (nodeStack.empty() == false || currentNode != nullptr)
	{
		if (currentNode != nullptr)
		{
			nodeStack.push(currentNode);

			currentNode = currentNode->getLeft();
		}
		else
		{
			currentNode = nodeStack.top();
			nodeStack.pop();
			std::cout << currentNode->getKey() << " ";

			currentNode = currentNode->getRight();
		}
	}
}

void AVL::findNthNode(unsigned int N)
{
	if (this->ranked == false)
		rankManager();

	if (N > this->size)
		return;

	node* current = root;

	while (current->getRank() != N)
	{
		if (N > current->getRank())
			current = current->getLeft();
		else
			current = current->getRight();
	}

	std::cout << current->getKey() << std::endl;
}

void AVL::gradesInBetween(float begin, float end)
{
	node* current = root;

	if (current == nullptr)
		return;

	queue order;
	order.push(current);

	unsigned int numberOfGrades = 0;

	while (order.empty() == false)
	{
		float currentGrade = order.front()->getKey().getGrade();

		if (currentGrade >= begin && currentGrade <= end)
		{
			numberOfGrades++;
			std::cout << order.front()->getKey() << std::endl;
		}

		if (order.front()->getLeft())
		{
			if (currentGrade >= begin)
				order.push(order.front()->getLeft());
		}

		if (order.front()->getRight())
		{
			if (currentGrade <= end)
				order.push(order.front()->getRight());
		}

		order.pop();
	}

	std::cout << std::endl;
	std::cout << numberOfGrades << " grades" << std::endl;
}