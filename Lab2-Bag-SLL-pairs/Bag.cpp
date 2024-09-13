#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <utility>
using namespace std;


Bag::Bag() {
    nrElems = 0;
    head = nullptr;
}


void Bag::add(TElem elem) {
    //search to increment frequency
    Node* current = head;
    while (current != nullptr) {
        if (current->elem.first == elem) {
            current->elem.second++;
            return;
        }
        current = current->next;  // Traverse to the next node
    }
    
    //if not found just add at the begining
    //TPair newElem = std::make_pair(elem, 1);
    Node* newNode = new Node(elem);
    newNode->next = head; // newNode.next for value newNode->next for *pointers
    head = newNode;
    nrElems++;
}


bool Bag::remove(TElem elem) {
    //walk list with 2 *pointers
    Node* currentNode = head;
    Node* prevNode = nullptr;
    //runs and stops when it hits elem
    //now sitting on the correct positions, current is now the elem
    while (currentNode != nullptr && currentNode->elem.first != elem) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    // If element not found, return false
     if (currentNode == nullptr) {
         return false; // Element is not in the list
     }
    
    //decrement since element found should have atleast 1
    currentNode->elem.second--;
    
    //check if freq 0 to remove pair
    if (currentNode->elem.second == 0) {
        //in case currentNode is the very first element and need to remove the head
        if (currentNode != nullptr && prevNode == nullptr) {
            head = head->next;
        }
        //not sure what this does?
        else if (currentNode != nullptr) {
            prevNode->next = currentNode->next;
            currentNode->next = nullptr;
            }
        delete currentNode;
        nrElems--;
    }
    return true;
}


bool Bag::search(TElem elem) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->elem.first == elem) {
            return true;  // Element found
        }
        current = current->next;  // Traverse to the next node
    }
    return false;  // Element not found
}

int Bag::nrOccurrences(TElem elem) const {

    Node * current = head;
    while (current != nullptr) {
        if (current->elem.first == elem) {
            return current->elem.second;
        }
        //forgot to move forward
        current = current->next;
    }
	return 0;
}


int Bag::size() const {
	int totalSize = 0;
    Node * current = head;
    while (current != nullptr) {
        totalSize += current->elem.second;
        current = current->next;
    }
    return totalSize;
}


bool Bag::isEmpty() const {
	return nrElems == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

