/* Comp 15 - Fall 2019
 * Project 2 Part 2
 * NAME: Qijin Chau
 * DATE: 12/6/19
 *
 * linkedList.cpp
 * Implementation of the linkedList class 
 */

#include <iostream>
#include "linkedList.h"

// default constructor
linkedList::linkedList()
{
	front = nullptr;
	listLen = 0;
}

// destructor
linkedList::~linkedList()
{
	deleteList();
}

// copy constructor
linkedList::linkedList(const linkedList &source)
{
	if (source.front == nullptr) {
		front = nullptr;
		listLen = 0;
	} else {
    	// copy first node
        front = new Node;
        front->next = nullptr;
        front->key = source.front->key;
        front->indices = source.front->indices;

        Node *curr = front;
        Node *currSource = source.front;

        //copy remaining nodes if exist
        while (currSource->next != nullptr) {
        	curr->next = new Node;
        	curr = curr->next;
        	curr->next = nullptr;
        	currSource = currSource->next;
          
            curr->key = currSource->key;
        	curr->indices = currSource->indices;
        }

        // copy listLen
        listLen = source.listLen;
    }
}

// assignment overload
linkedList &linkedList::operator=(const linkedList &source)
{
	if(this != &source) {
		if(source.front == nullptr) {
        	front = nullptr;
        	listLen = 0;
        } else {
            deleteList();
      
        	// copy first node
        	front = new Node;
        	front->next = nullptr;
        	front->key = source.front->key;
        	front->indices = source.front->indices;
        
	        Node *curr = front;
	        Node *currSource = source.front;

	        //copy remaining nodes if exist
	        while (currSource->next != nullptr) {
	        	curr->next = new Node;
	        	curr = curr->next;
	        	curr->next = nullptr;
	        	currSource = currSource->next;
	          
	            curr->key = currSource->key;
	        	curr->indices = currSource->indices;
	        }
	        
	        // copy listLen
	        listLen = source.listLen;
   		}
	}
    return *this;
}

// Function deleteList
// Parameters: None 
// Returns: Nothing
// Does: Deletes all the nodes in the linked list starting at the front.
void linkedList::deleteList()
{
	Node *current = front;
	Node *next;

	while(current != nullptr) {
		next = current->next;
		delete current;
		current = next;
	}

	front = nullptr;
	listLen = -1;
}

// Function insert
// Parameters: One strings and an integer
// Returns: A boolean.
// Does: If the key already exists in the list, the index passed in gets
//       added to the vector in the node with the key; false is returned.
//       If the key doesn't exist yet, then a node with the parameter values
//       is into the front of the linked list; true is returned. 
bool linkedList::insert(string key, int index)
{
    Node *curr = front;

    // if key already exists
    for(int i=0; i<listLen; i++) {
        if(curr->key == key) {
            curr->indices.push_back(index);

            // return false because no new node
            return false;
        }
        
        curr = curr->next; 
    }

    // if key doesn't exist yet
    Node *aux = new Node;
    aux->key = key;
    aux->indices.push_back(index);
    aux->next = front;
    front = aux;
    listLen++;

    // return true because new node is added
    return true;
}

// Function insertNode
// Parameters: A node
// Returns: Number of nodes after insert.
// Does: Inserts a node with the values of the given node, 
//       then returns the total number of nodes in the linked list. 
int linkedList::insertNode(Node *toInsert)
{
	Node *aux = new Node;
	aux->key = toInsert->key;
	aux->indices = toInsert->indices;
	aux->next = front;
	front = aux;
	listLen++;

	return listLen;
}

// Function listLength
// Parameters: None
// Returns: An integer
// Does: Return length of the linked list.
int linkedList::listLength()
{
    return listLen;
}

// Function indicesSize
// Parameters: A node
// Returns: A size_t
// Does: Return size of indices vector in the node passed in.
size_t linkedList::indicesSize(Node *node)
{
	return node->indices.size();
}

// Function getFront
// Parameters: Nothing
// Returns: A node
// Does: Return the front of the linked list.
Node* linkedList::getFront()
{
	return front;
}

// Function getNode
// Parameters: A node
// Returns: A node
// Does: Returns the next node of the node passed in.
Node* linkedList::getNextNode(Node *node)
{
	return node->next;
}

// Function printList
// Parameters: None
// Returns: Nothing
// Does: Prints the information of each node to standard cout.
void linkedList::printList()
{
	Node *curr = front;
	int count = 1;
	
	for(int i=0; i<listLen; i++) {
		cout << "Node #" << count << ":\n";
		
		cout << "Key: " << curr->key << "\n";

		cout << "Indices: ";
		for(size_t j=0; j<curr->indices.size(); j++) {
			cout << curr->indices.at(j) << "  ";  
		}

		cout << "\n";
		count++;

		curr = curr->next;
	}
}

// Function makeLower
// Parameters: A string
// Returns: A string
// Does: Converts the string passed in to all lowercase and returns it.
string linkedList::makeLower(string toLower)
{
	string loweredString;

	for(unsigned long i=0; i<toLower.length(); i++) 
		loweredString += tolower(toLower[i]);

	return loweredString;
}