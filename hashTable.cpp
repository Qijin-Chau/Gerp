/* Comp 15 - Fall 2019
 * Project 2 Part 2
 * NAME: Qijin Chau
 * DATE: 12/6/19
 *
 * hashTable.cpp
 * Implementation of the hashTable class 
 */

#include <iostream>
#include <fstream>
#include "hashTable.h"
#include "linkedList.h"

// default constructor
hashTable::hashTable()
{
	currentTableSize = INITIAL_TABLE_SIZE;

    chainedTable = new linkedList [currentTableSize];

    numItemsInTable = 0;
}

// destructor
hashTable::~hashTable()
{
	delete []chainedTable;
}

// copy constructor
hashTable::hashTable(const hashTable &source)
{
	currentTableSize = source.currentTableSize;
	chainedTable = new linkedList [currentTableSize];

	for (int i = 0; i < currentTableSize; i++) {
		chainedTable[i] = source.chainedTable[i];
    }
}

// assignment overload
hashTable &hashTable::operator=(const hashTable &source)
{
    if(this != &source) {
		delete []chainedTable;
        
        currentTableSize = source.currentTableSize;
        chainedTable = new linkedList [source.currentTableSize];

		for (int i = 0; i < currentTableSize; i++) {
			chainedTable[i] = source.chainedTable[i];
   		}
    }

    return *this;
}

// hash function
// with mod of the size of the whole table (array of linked list)
size_t hashTable::hashFunction(string key)
{
	return std::hash<string>{}(key) % currentTableSize;
}

// Function insert
// Parameters: A string and an integer
// Returns: Nothing
// Does: Hashes the passed in key, and calls insert on the linked list
//       at the index of the hashed key. 
//       Expands if loading factor is reached.
void hashTable::insert(string key, int index)
{
	string loweredString;

	for(unsigned long i=0; i<key.length(); i++) 
		loweredString += tolower(key[i]);
	
	size_t hashIndex = hashFunction(loweredString);
	
	if(chainedTable[hashIndex].insert(key, index))
		numItemsInTable++;

	
	int loadingFactor = numItemsInTable/currentTableSize;
	if(loadingFactor >= 0.75)
		expand();
}

// Function search
// Parameters: A string and an output stream
// Returns: A boolean
// Does: Searches the array linked list at index of 
//       the hashed key for the key. Return true if found;
//       false otherwise. Prints to output stream provided.
bool hashTable::search(string key, ofstream &output_source)
{
	string loweredString;

	for(unsigned long i=0; i<key.length(); i++) 
		loweredString += tolower(key[i]);

	size_t hashIndex = hashFunction(loweredString);

	Node *curr = chainedTable[hashIndex].getFront();
	for(int i=0; i<chainedTable[hashIndex].listLength(); ++i) {
		if(curr->key == key) {
			for(size_t j=0; j<curr->indices.size(); j++) {
				bool repeat = false;
				if(j+1 < curr->indices.size() &&
					stringAt(curr->indices.at(j)) == 
					stringAt(curr->indices.at(j+1)) ) {
					
					repeat = true;
				}
				if(!repeat)
					output_source << stringAt(curr->indices.at(j)) << endl;
			}
			return true;
		}
		curr = chainedTable[hashIndex].getNextNode(curr);
	}

	output_source << key << " Not Found. Try with @insensitive or @i." << endl;
	return false;
}

// Function iSearch
// Parameters: A string and an output stream
// Returns: A boolean
// Does: Case insensitively Searches the array linked list at 
//       index of the hashed key for the key. Return true if found; 
//       false otherwise. Prints to output stream provided.
bool hashTable::iSearch(string key, ofstream &output_source)
{
	string loweredString, loweredCompareString;
	bool found = false;

	for(unsigned long i=0; i<key.length(); i++) 
		loweredString += tolower(key[i]);

	size_t hashIndex = hashFunction(loweredString);

	Node *curr = chainedTable[hashIndex].getFront();
	for(int i=0; i<chainedTable[hashIndex].listLength(); ++i) {

		loweredCompareString = "";
		for(unsigned long c=0; c<curr->key.length(); c++) 
			loweredCompareString += tolower(curr->key[c]);
		
		if(loweredCompareString == loweredString) {
			found = true;
			for(size_t j=0; j<curr->indices.size(); j++) {
				bool repeat = false;
				if(j+1 < curr->indices.size() &&
					stringAt(curr->indices.at(j)) == 
					stringAt(curr->indices.at(j+1)) ) {
					
					repeat = true;
				}
				if(!repeat)
					output_source << stringAt(curr->indices.at(j)) << endl;
			}
		}
		curr = chainedTable[hashIndex].getNextNode(curr);
	}

	if(found)
		return true;

	output_source << key << " Not Found.\n" << endl;
	return false;
}

// Function currentMaxSize
// Parameters: None
// Returns: An integer
// Does: Return the total number of linked lists in the table
//       regardless if empty.
int hashTable::currentMaxSize()
{
    return currentTableSize;
}

// Function currentOccup
// Parameters: None
// Returns: An integer
// Does: Return the number of total nodes in the table.
int hashTable::currentOccup()
{
    return numItemsInTable;
}

// Function print
// Parameters: None
// Returns: Nothing
// Does: Prints the entire linked list array to standard cout.
void hashTable::print()
{
	for (int i = 0; i < currentTableSize; i++)
		chainedTable[i].printList();
}

// Function addOutput
// Parameters: A string
// Returns: Nothing
// Does: Adds the given string to the back of the outputs vector.
void hashTable::addOutput(string toAdd)
{
	outputs.push_back(toAdd);
}

// Function addOutput
// Parameters: None
// Returns: A size_t
// Does: Returns the size of the outputs vector.
size_t hashTable::outputsSize()
{
	return outputs.size();
}

// Function stringAt
// Parameters: An integer
// Returns: A string
// Does: Returns the string at the index of the passed in
//       integer in the outputs vector.
string hashTable::stringAt(int i)
{
	return outputs.at(i);
}

// Function expand
// Parameters: None
// Returns: Nothing
// Does: Expands the hash table and re-hashes everything based on
//       the new table size.
void hashTable::expand()
{
	int oldTableSize = currentTableSize;
	currentTableSize *= 2;
	linkedList *newTable = new linkedList [currentTableSize];

	for (int i = 0; i < oldTableSize; ++i) {
		
		Node *curr = chainedTable[i].getFront();
		for (int j = 0; j < chainedTable[i].listLength(); ++j) {
			
			string loweredString;
			for(unsigned long i=0; i<curr->key.length(); i++) {
				loweredString += tolower(curr->key[i]);
			}

			size_t hashIndex = hashFunction(loweredString);
			newTable[hashIndex].insertNode(curr);

			curr = chainedTable[i].getNextNode(curr);
		}
	}
	
	// delete old table
	delete []chainedTable;

	// assign old table to new table
	chainedTable = newTable;
}

