#ifndef FIFOQUE_H
#define FIFOQUE_H
#include "LinkedNodeClass.h"

//Programmer: Yi Hsien Wu
//Date: 11/11/2023
//FIFOQueueClass Declaration
//Purpose: This class is designed to use First In First Out method to
//         store and retrieve data.

class FIFOQueueClass
{
private:
    LinkedNodeClass *head;
    //Points to the first node in a queue, or NULL
    //if queue is empty.
    LinkedNodeClass *tail;
    //Points to the last node in a queue, or NULL
    //if queue is empty.
public:
    FIFOQueueClass();
    //Constructor: initializes both head and tail pointers to 0.
    ~FIFOQueueClass();
    //Destructor: free up any dynamically allocated memory.
    void enqueue(const int &newItem);
    //Adds a new node to the end of the queue with the specified value.
    bool dequeue(int &outItem);
    //Removes the front node from the queue and retrieves its value.
    void print() const;
    //Prints the values of all nodes in the queue from front to end.
    int getNumElems() const;
    //Counts and returns the number of nodes in the queue.
    void clear();
    //Clears the queue to an empty state without resulting in any memory leaks
};

#endif