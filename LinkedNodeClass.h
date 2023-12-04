#ifndef LINK_H
#define LINK_H

//Programmer: Yi Hsien Wu
//Date: 11/11/2023
//LinkedNodeClass Declaration
//Purpose: This class is designed to store data and pointers to
//         the next and previous node in a linked list.

class LinkedNodeClass
{
private:
    LinkedNodeClass *prevNode;
    int nodeVal;
    LinkedNodeClass *nextNode;

public:

    LinkedNodeClass(LinkedNodeClass *inPrev,
        const int &inVal, LinkedNodeClass *inNext);
    //Constructor: Initialize nodeValue to inVal,
//and prevNode and nextNode to NULL

    int getValue() const;
    //Returns the value stored within this node.
    LinkedNodeClass* getNext() const;
    //returns a pointer to the next node in the linked list.
    LinkedNodeClass* getPrev() const;
    //returns a pointer to the previous node in the linked list.
    void setNextPointerToNull();
    //Sets the nextNode pointer to 0.
    //Means that there is no node after the current node.
    void setPreviousPointerToNull();
    //Sets the prevNode pointer to 0
    //Means that there is no node before the current node.
    void setBeforeAndAfterPointers();
    //Sets the pointers before and after this node to point to this node.
    //Used during insertion.
};

#endif










