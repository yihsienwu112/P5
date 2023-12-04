#include <iostream>
#include "FIFOQueueClass.h"

FIFOQueueClass::FIFOQueueClass() : head(0), tail(0) {}

FIFOQueueClass::~FIFOQueueClass() {
    clear();
}

void FIFOQueueClass::enqueue(const int &newItem) {
    if (tail == 0) {
        // Queue is empty
        LinkedNodeClass *newNode = new LinkedNodeClass(
            0, newItem, 0);
        head = tail = newNode;
    } else {
        LinkedNodeClass *newNode = new LinkedNodeClass(
            tail, newItem, 0);
        newNode->setBeforeAndAfterPointers();
        tail = newNode;
    }
}

bool FIFOQueueClass::dequeue(int &outItem) {
    if (head == 0) {
        // Queue is empty
        return false;
    }

    outItem = head->getValue();
    LinkedNodeClass *tempNode = head;
    head = head->getNext();

    delete tempNode;

    if (head == 0) {
        // Queue is now empty
        tail = 0;
    }

    return true;
}

void FIFOQueueClass::print() const {
    LinkedNodeClass *currentPtr = head;
    while (currentPtr != 0) {
        std::cout << currentPtr->getValue() << " ";
        currentPtr = currentPtr->getNext();
    }
    std::cout << std::endl;
}

int FIFOQueueClass::getNumElems() const {
    int countOfNodes = 0;
    LinkedNodeClass *currentPtr = head;
    while (currentPtr != 0) {
        countOfNodes++;
        currentPtr = currentPtr->getNext();
    }
    return countOfNodes;
}

void FIFOQueueClass::clear() {
    LinkedNodeClass *currentPtr = head;
    while (currentPtr != 0) {
        LinkedNodeClass *tempNode = currentPtr;
        currentPtr = currentPtr->getNext();
        delete tempNode;
    }

    head = tail = 0;
}