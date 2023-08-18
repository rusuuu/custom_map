#include "AVL_hashTable.h"

void AVL_hashTable::insert(element Element)
{
    table.insertElem(Element);
    element* Link = table.getElementAdress(table.findElem(Element.getValue()));
    tree.insert(Element.getValue(),Link);
}

void AVL_hashTable::erase(candidate Candidate)
{
    int tableIndex = table.findElem(Candidate);

    if (tableIndex == -1)
    {
        std::cout << "Elementul nu a putut fi sters!" << std::endl << std::endl;
        return;
    }

    node* toBeDeleted= table.getLinkToNode(tableIndex);
    tree.erase(toBeDeleted);
	table.eraseElem(Candidate);
}

node* AVL_hashTable::findInTree(candidate Candidate)
{
    return table.getLinkToNode(table.findElem(Candidate));
}

int AVL_hashTable::findInTable(candidate Candidate)
{
    return table.findElem(Candidate);
}

void AVL_hashTable::writeTree()
{
    tree.inorder(tree.getRoot());
}

void AVL_hashTable::writeTable()
{
    table.write();
}

void AVL_hashTable::clear()
{
    table.clear();
    tree.clear(tree.getRoot());
}

element readFromFile(std::ifstream& input)
{
    element element;

    std::string surname, name, CNP;
    float grade;

    input >> surname >> name >> CNP >> grade;

    candidate value(surname, name, CNP, grade);

    element.setKey(CNP);
    element.setValue(value);

    return element;
}
