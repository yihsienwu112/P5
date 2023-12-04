#ifndef SortedList_H
#define SortedList_H
# include "LinkedNodeClass.h"

//Programmer: Yi Hsien Wu
//Date: 11/11/2023
//SortedListClass Declaration
//Purpose: This class is designed to use ascending order to
//         store and retrieve data.
template <class T>
class SortedListClass
{
private:
    LinkedNodeClass<T> *head;
    LinkedNodeClass<T> *tail;

public:
    SortedListClass();
    //Constructor: initializes both head and tail pointers to 0.
    SortedListClass(const SortedListClass<T> &rhs);
    //Copy constructor: makes a complete copy of its parameter.
    ~SortedListClass();
    //Destructor: free up any dynamically allocated memory.
        // SortedListClass& operator=(const SortedListClass &rhs);
    //Assignment operator: makes a complete copy of its parameter.
    void clear();
    //Clears the list to an empty state without resulting in any memory leaks
    void insertValue(const T &valToInsert);
    //Inserts the specified value into the list,
    //maintaining ascending order of values in the list.
    void printForward() const;
    //Prints the values of the nodes in the list in forward order.
    void printBackward() const;
    //Prints the values of the nodes in the list in reverse order.
    bool removeFront(T &theVal);
    //Remove the front item from the list and return its value
    bool removeLast(T &theVal);
    //Remove the last item from the list and return its value
    int getNumElems() const;
    //Counts and returns the number of nodes in the list.
    bool getElemAtIndex(const int index, T &outVal) const;
    //Retrieves the value at the specified index in the list.

};

#include "SortedListClass.inl"
#endif


