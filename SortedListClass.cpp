# include "SortedListClass.h"
# include <iostream>
using namespace std;


SortedListClass::SortedListClass() : head(0), tail(0) {}

SortedListClass::SortedListClass(const SortedListClass &rhs) {
    head = tail = 0;
    LinkedNodeClass *tempNode = rhs.head;
    while (tempNode != 0) {
        insertValue(tempNode->getValue());
        tempNode = tempNode->getNext();
    }
}

SortedListClass::~SortedListClass() {
    clear();
}

SortedListClass& SortedListClass::operator=(const SortedListClass &rhs) {
    if (this != &rhs) {
        clear();
        LinkedNodeClass *tempNode = rhs.head;
        while (tempNode != 0) {
            insertValue(tempNode->getValue());
            tempNode = tempNode->getNext();
        }
    }
    return *this;
}

void SortedListClass::clear() {
    LinkedNodeClass *tempNode;
    while (head != 0) {
        tempNode = head;
        head = head->getNext();
        delete tempNode;
    }
    tail = 0;
}


void SortedListClass::insertValue(const int &valToInsert) {

    if (head == 0) {
        // List is empty
        LinkedNodeClass *newNode = new LinkedNodeClass(
            0, valToInsert, 0);
        head = tail = newNode;
    } else {
        LinkedNodeClass *currentPtr = head;
        LinkedNodeClass *prevPtr = 0;

        while (currentPtr != 0 &&
               currentPtr->getValue() < valToInsert) {
            prevPtr = currentPtr;
            currentPtr = currentPtr->getNext();
        }

        if (prevPtr == 0) {
            // Insert at the beginning
            LinkedNodeClass *newNode = new LinkedNodeClass(
                0, valToInsert, head);
            newNode->setBeforeAndAfterPointers();
            head = newNode;
        } else if (currentPtr == 0) {
            // Insert at the end
            LinkedNodeClass *newNode = new LinkedNodeClass(
                tail, valToInsert, 0);
            newNode->setBeforeAndAfterPointers();
            tail = newNode;
        } else {
            // Insert in the middle
            LinkedNodeClass *newNode = new LinkedNodeClass(
                prevPtr, valToInsert, currentPtr);
            newNode->setBeforeAndAfterPointers();
        }
    }
}


void SortedListClass::printForward() const {
    std::cout << "Forward List Contents Follow:" << std::endl;
    LinkedNodeClass *tempNode = head;
    while (tempNode != 0) {
        std::cout << "  " << tempNode->getValue() << std::endl;
        tempNode = tempNode->getNext();
    }
    std::cout << "End Of List Contents" << std::endl;
}

void SortedListClass::printBackward() const {
    std::cout << "Backward List Contents Follow:" << std::endl;
    LinkedNodeClass *tempNode = tail;
    while (tempNode != 0) {
        std::cout << "  " << tempNode->getValue() << std::endl;
        tempNode = tempNode->getPrev();
    }
    std::cout << "End Of List Contents" << std::endl;
}

bool SortedListClass::removeFront(int &theVal) {
    if (head == 0) {
        // Empty list
        return false;
    }

    theVal = head->getValue();
    LinkedNodeClass *tempNode = head;
    head = head->getNext();

    if (head == 0) {
        tail = 0;
    } else {
        head->setPreviousPointerToNull();
    }

    delete tempNode;
    return true;
}

bool SortedListClass::removeLast(int &theVal) {
    if (tail == 0) {
        // Empty list
        return false;
    }

    theVal = tail->getValue();
    LinkedNodeClass *tempNode = tail;
    tail = tail->getPrev();

    if (tail == 0) {
        head = 0;
    } else {
        tail->setNextPointerToNull();
    }

    delete tempNode;
    return true;
}

int SortedListClass::getNumElems() const {
    int count = 0;
    LinkedNodeClass *tempNode = head;
    while (tempNode != 0) {
        count++;
        tempNode = tempNode->getNext();
    }
    return count;
}

bool SortedListClass::getElemAtIndex(const int index, int &outVal) const {
    if (index < 0) {
        return false;
    }

    LinkedNodeClass *tempNode = head;
    int numIndex = 0;

    while (tempNode != 0 && numIndex < index) {
        tempNode = tempNode->getNext();
        numIndex++;
    }

    if (tempNode == 0) {
        return false;
    }

    outVal = tempNode->getValue();
    return true;
}
