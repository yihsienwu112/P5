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
                                                   LinkedNodeClass<T> *inNext){
  nodeVal = inVal;
  nextNode = inNext;
  prevNode = inPrev;
}

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

//This function DOES NOT modify "this" node. Instead, it uses 
//the pointers contained within this node to change the previous 
//and next nodes so that they point to this node appropriately. 
//In other words, if "this" node is set up such that its prevNode 
//pointer points to a node (call it "A"), and "this" node's 
//nextNode pointer points to a node (call it "B"), then calling 
//setBeforeAndAfterPointers results in the node we're calling 
//"A" to be updated so its "nextNode" points to "this" node, and 
//the node we're calling "B" is updated so its "prevNode" points 
//to "this" node, but "this" node itself remains unchanged.
template <class T>
void LinkedNodeClass<T>::setBeforeAndAfterPointers(){
  if(prevNode != 0){ 
    if(nextNode != 0){
        //in the middle of the list
        prevNode->nextNode = this;
        nextNode->prevNode = this;
    }
    else{ //the node before tail 
      prevNode->nextNode = this; 
    }
  }
  else{  //the node after head 
    if(nextNode !=0){
      nextNode->prevNode = this;
    }
  }
}