/* Comp 15 - Fall 2019
 * Project 2 Part 2
 * NAME: Qijin Chau
 * DATE: 12/6/19
 *
 * linkedList.h
 * Class interface for the linkedList class
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <vector>

using namespace std;

// Node definition
struct Node {
	string key;
	
	// all the indices in the outputs vector declared in
	// the hashTable class where the key is located
	vector<int> indices;
	Node *next;
};


class linkedList
{
public:
	// default constructor
	linkedList();

	// destructor
	~linkedList();

	// copy constructor
	linkedList(const linkedList &source);

	// assignment operator
	linkedList &operator=(const linkedList &source);

	void deleteList();

	// inserts
	bool insert(string key, int index);
	int insertNode(Node *toInsert);

	// get lengths or sizes
	int listLength();
	size_t indicesSize(Node *node);

	// get nodes
	Node* getFront();
	Node* getNextNode(Node *node);

	// for debugging
	void printList();

private:
	// pointer to front of linked list
	Node  *front;

	// number of nodes in linked list
	int listLen;

	// makes string lowercase
	string makeLower(string toLower);
};

#endif	/* LINKEDLIST_H */