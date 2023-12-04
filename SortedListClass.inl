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
SortedListClass<T>::SortedListClass(){
    head = 0;
    tail = 0;
}

template <class T>
SortedListClass<T>::SortedListClass(const SortedListClass<T> &rhs){
    head = 0;
    tail = 0;
    LinkedNodeClass<T> *nodePtr = rhs.head;
    while(nodePtr != 0){
        int valToInsert = nodePtr->getValue();
        this->insertValue(valToInsert); //insert the value from rhs
        //function insertValue will help us create new pointers to make a copy
        nodePtr = nodePtr->getNext();
    }
}

template <class T>
SortedListClass<T>::~SortedListClass(){
    clear();
}

template <class T>
void SortedListClass<T>::clear(){
    LinkedNodeClass<T> *nodePtr;
    LinkedNodeClass<T> *clearPtr;
    nodePtr = head;
    clearPtr = head;
    while(nodePtr != 0){
        nodePtr = nodePtr->getNext();
        delete clearPtr;
        clearPtr = nodePtr;
    }
    head = 0;
    tail = 0;
}

template <class T>
void SortedListClass<T>::insertValue(const T &valToInsert){
    LinkedNodeClass<T> *insertPtr;

    if(head == 0 && tail == 0){
        insertPtr = new LinkedNodeClass<T>(0, valToInsert, 0);
        head = insertPtr;
        tail = insertPtr;
    }

    else{
        LinkedNodeClass<T> *nodePtr;
        nodePtr = head;

        while(nodePtr!=0 && nodePtr->getValue() <= valToInsert){
            nodePtr = nodePtr->getNext();
        }

        //Insert from front
        if(nodePtr == head){
            insertPtr = new LinkedNodeClass<T>(0, valToInsert, head);
            insertPtr->setBeforeAndAfterPointers();
            head = insertPtr; //change head to point to where insertPtr is pointing to
        }

            //insert from last position
        else if(nodePtr == 0){ //the last node, so nodePtr would be zero
            insertPtr = new LinkedNodeClass<T>(tail, valToInsert, 0);
            insertPtr->setBeforeAndAfterPointers();
            tail = insertPtr;
        }
        else{
            //insert in the middle
            insertPtr = new LinkedNodeClass<T>(nodePtr->getPrev(), valToInsert,
                                               nodePtr);
            insertPtr->setBeforeAndAfterPointers();
        }
    }
}


template <class T>
void SortedListClass<T>::printForward() const{
    LinkedNodeClass<T> *nodePtr;
    nodePtr = head;

    cout << "Forward List Contents Follow:" << endl;

    while(nodePtr != 0){
        cout << "  " << nodePtr->getValue() << endl;
        nodePtr = nodePtr->getNext();
    }
    cout << "End Of List Contents" << endl;
}

template <class T>
void SortedListClass<T>::printBackward() const{
    LinkedNodeClass<T> *nodePtr;
    nodePtr = tail;

    cout << "Backward List Contents Follow:" << endl;

    while(nodePtr != 0){
        cout << "  " << nodePtr->getValue() << endl;
        nodePtr = nodePtr->getPrev();
    }
    cout << "End Of List Contents" << endl;
}


template <class T>
bool SortedListClass<T>::removeFront(T &theVal){
    bool successfullyReomvedItem;
    LinkedNodeClass<T> *newHeadPtr;

    //if the list was empty:
    if(head == 0){    //use head == 0 to represent the list is empty
        successfullyReomvedItem = false;
    }
    else{
        theVal = head->getValue();
        newHeadPtr = head->getNext();
        delete head; //delete the value that head is pointing to
        head = newHeadPtr;

        //handling condition: last node being deleted
        if(head != 0){
            head->setPreviousPointerToNull();
        }
        else{
            tail = 0;
        }
        successfullyReomvedItem = true;
    }
    return successfullyReomvedItem;
}

template <class T>
bool SortedListClass<T>::removeLast(T &theVal){
    bool successfullyReomvedItem;
    LinkedNodeClass<T> *newTailPtr;

    //if the list was empty
    if(tail == 0){
        successfullyReomvedItem = false;
    }
    else{
        theVal = tail->getValue();
        newTailPtr = tail->getPrev();
        delete tail;
        tail = newTailPtr;

        //handling condition: last node being deleted
        if(tail != 0){
            tail->setNextPointerToNull();
        }
        else{
            head = 0;
        }
        successfullyReomvedItem = true;
    }
    return successfullyReomvedItem;
}


template <class T>
int SortedListClass<T>::getNumElems() const{
    LinkedNodeClass<T> *countPtr;
    int numberOfNodes = 0;

    countPtr = head;
    while(countPtr != 0){
        numberOfNodes++;
        countPtr = countPtr->getNext();
    }
    return numberOfNodes;
}


template <class T>
bool SortedListClass<T>::getElemAtIndex(const int index, T &outVal) const{
    bool successfullyGetIndex;
    if(index >= getNumElems()){
        successfullyGetIndex = false;
    }
    else if(index < 0){
        successfullyGetIndex = false;
    }
    else{
        int numberOfIndex = 0;
        LinkedNodeClass<T> *indexPtr;
        indexPtr = head; //point to where head is pointing to
        while(indexPtr != 0){
            if(numberOfIndex == index){
                outVal = indexPtr->getValue();
                successfullyGetIndex = true;
                return successfullyGetIndex;
            }
            numberOfIndex++;
            indexPtr = indexPtr->getNext();
        }
    }
    return successfullyGetIndex;
}
