#include <iostream>
#include "LinkedNodeClass.h"


using namespace std;

//Programmer: Joshua Chang 
//Date: November 2021
//LinkedNodeClass Function Definitions
//Purpose: The list node class will be the data type for individual nodes of 
//a doubly-linked data structure.

template <class T>
LinkedNodeClass<T>::LinkedNodeClass(LinkedNodeClass<T> *inPrev, const T &inVal,
                                    LinkedNodeClass<T> *inNext)
        : prevNode(inPrev), nodeVal(inVal), nextNode(inNext) {}

template <class T>
T LinkedNodeClass<T>::getValue() const{
    return nodeVal;
}

//Returns the address of the node that follows this node. 
template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getNext() const{
    return nextNode;
}

//Returns the address of the node that comes before this node.
template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getPrev() const{
    return prevNode;
}

//Sets the object’s next node pointer to NULL. 
template <class T>
void LinkedNodeClass<T>::setNextPointerToNull(){
    nextNode = 0;
}

//Sets the object's previous node pointer to NULL. 
template <class T>
void LinkedNodeClass<T>::setPreviousPointerToNull(){
    prevNode = 0;
}


template <class T>
void LinkedNodeClass<T>::setBeforeAndAfterPointers(){
    if (prevNode != 0) {
        prevNode->nextNode = this;
    }
    if (nextNode != 0) {
        nextNode->prevNode = this;
    }
}