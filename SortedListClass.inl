#include "SortedListClass.h"
#include "LinkedNodeClass.h"
#include <iostream>

using namespace std;

//Programmer: Joshua Chang
//Date: November 2021
//SortedListClass Function Definitions
//Purpose: The sorted list class does not store any data directly. Instead,
//it contains a collection //contains one element

template <class T>
SortedListClass<T>::SortedListClass() : head(0), tail(0){}

template <class T>
SortedListClass<T>::SortedListClass(const SortedListClass<T> &rhs){
    // Implement copy constructor logic here
    // Make a deep copy of the linked list
    head = tail = 0;
    LinkedNodeClass<T> *tempNode = rhs.head;
    while(tempNode != 0){
        insertValue(tempNode->getValue());
        tempNode = tempNode->getNext();
    }
}

template <class T>
SortedListClass<T>::~SortedListClass(){
    clear();
}

template <class T>
void SortedListClass<T>::clear(){
    LinkedNodeClass<T> *tempNode;
    while (head != 0) {
        tempNode = head;
        head = head->getNext();
        delete tempNode;
    }
    tail = 0;
}

template<class T>
void SortedListClass<T>::insertValue(const T &valToInsert) {
    if (head == 0) {
        // List is empty
        LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(0, valToInsert, 0);
        head = tail = newNode;
    } else {
        LinkedNodeClass<T> *current = head;
        LinkedNodeClass<T> *prev = 0;

        while (current != 0 && current->getValue() <= valToInsert) {
            prev = current;
            current = current->getNext();
        }

        if (prev == 0) {
            // Insert at the beginning
            LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(0, valToInsert, head);
            newNode->setBeforeAndAfterPointers();
            head = newNode;
        } else if (current == 0) {
            // Insert at the end
            LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(tail, valToInsert, 0);
            newNode->setBeforeAndAfterPointers();
            tail = newNode;
        } else {
            // Insert in the middle
            LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(prev, valToInsert, current);
            newNode->setBeforeAndAfterPointers();
        }

    }
}



template <class T>
void SortedListClass<T>::printForward() const{
    std::cout << "Forward List Contents Follow:" << std::endl;
    LinkedNodeClass<T> *tempNode = head;
    while (tempNode != 0) {
        std::cout << "  " << tempNode->getValue() << std::endl;
        tempNode = tempNode->getNext();
    }
    std::cout << "End Of List Contents" << std::endl;
}

template <class T>
void SortedListClass<T>::printBackward() const{
    std::cout << "Backward List Contents Follow:" << std::endl;
    LinkedNodeClass<T> *tempNode = tail;
    while (tempNode != 0) {
        std::cout << "  " << tempNode->getValue() << std::endl;
        tempNode = tempNode->getPrev();
    }
    std::cout << "End Of List Contents" << std::endl;
}


template <class T>
bool SortedListClass<T>::removeFront(T &theVal){
    if (head == 0) {
        // Empty list
        return false;
    }

    theVal = head->getValue();
    LinkedNodeClass<T> *tempNode = head;
    head = head->getNext();

    if (head == 0) {
        tail = 0;
    } else {
        head->setPreviousPointerToNull();
    }

    delete tempNode;
    return true;
}

template <class T>
bool SortedListClass<T>::removeLast(T &theVal){
    if (tail == 0) {
        // Empty list
        return false;
    }

    theVal = tail->getValue();
    LinkedNodeClass<T> *tempNode = tail;
    tail = tail->getPrev();

    if (tail == 0) {
        head = 0;
    } else {
        tail->setNextPointerToNull();
    }

    delete tempNode;
    return true;
}


template <class T>
int SortedListClass<T>::getNumElems() const{
    int count = 0;
    LinkedNodeClass<T> *tempNode = head;
    while (tempNode != 0) {
        count++;
        tempNode = tempNode->getNext();
    }
    return count;
}


template <class T>
bool SortedListClass<T>::getElemAtIndex(const int index, T &outVal, void *pVoid) const{
    if (index < 0) {
        return false;
    }

    LinkedNodeClass<T> *tempNode = head;
    int numIndex = 0;

    while (tempNode != pVoid && numIndex < index) {
        tempNode = tempNode->getNext();
        numIndex++;
    }

    if (tempNode == pVoid) {
        return false;
    }

    outVal = tempNode->getValue();
    return true;
}
