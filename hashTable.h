/* Comp 15 - Fall 2019
 * Project 2 Part 2
 * NAME: Qijin Chau
 * DATE: 12/6/19
 *
 * hashTable.h
 * Class interface for the hashTable class
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "linkedList.h"

class hashTable
{
public:
	// default constructor
	hashTable();

	// destructor
	~hashTable();

	// copy constructor
	hashTable(const hashTable &source);
	
	// assignment operator
	hashTable &operator=(const hashTable &source);

	// hash function
	size_t hashFunction(string key);

	void insert(string key, int index);

	// case sensitive search
	bool search(string key, ofstream &output_source);
	// case insensitive search
	bool iSearch(string key, ofstream &output_source);

	int currentMaxSize();
	int currentOccup();

	// for debugging purposes
	void print();

	// for outputs vector
	void addOutput(string toAdd);
	size_t outputsSize();
	string stringAt(int i);

private:
	static const int INITIAL_TABLE_SIZE = 100000;

	// vector of all the paths to every file in the directory 
	// given and the all lines inside the files
	vector<string> outputs;

	// max table size
    int currentTableSize;

    // current number of nodes
    int numItemsInTable;

    // pointer to a linked list
	linkedList  *chainedTable;

	// expand when load factor is reached
	void expand();
};

#endif	/* HASHTABLE_H */