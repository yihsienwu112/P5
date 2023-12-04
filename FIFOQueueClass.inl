#include <iostream>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"


//Programmer: Joshua Chang
//Date: November 2021
//FIFOQueueClass Functions Definition
//Purpose: This class will be used to store a simple first-in-first-out
//queue data structure.

template <class T>
FIFOQueueClass<T>::FIFOQueueClass(): head(0), tail(0) {}

template <class T>
FIFOQueueClass<T>::~FIFOQueueClass(){
  clear();
}

template <class T>
void FIFOQueueClass<T>::enqueue(const T &newItem){
    if (tail == 0) {
        // Queue is empty
        LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(0, newItem, 0);
        head = tail = newNode;
    } else {
        LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(tail, newItem, 0);
        newNode->setBeforeAndAfterPointers();
        tail = newNode;
    }
}

template <class T>
bool FIFOQueueClass<T>::dequeue(T &outItem){
    if (head == 0) {
        // Queue is empty
        return false;
    }

    outItem = head->getValue();
    LinkedNodeClass<T> *tempNode = head;
    head = head->getNext();

    delete tempNode;

    if (head == 0) {
        // Queue is now empty
        tail = 0;
    }

    return true;
}


//Here we print from head to tail(First element will be on the lest)
template <class T>
void FIFOQueueClass<T>::print() const{
    LinkedNodeClass<T> *current = head;
    while (current != 0) {
        std::cout << current->getValue() << " ";
        current = current->getNext();
    }
    std::cout << std::endl;
}

template <class T>
int FIFOQueueClass<T>::getNumElems() const{
    int count = 0;
    LinkedNodeClass<T> *current = head;
    while (current != 0) {
        count++;
        current = current->getNext();
    }
    return count;
}


template < class T >
void FIFOQueueClass<T>::clear(){
    LinkedNodeClass<T> *current = head;
    while (current != 0) {
        LinkedNodeClass<T> *temp = current;
        current = current->getNext();
        delete temp;
    }

    head = tail = 0;
}