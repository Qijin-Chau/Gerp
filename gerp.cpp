/* Comp 15 - Fall 2019
 * Project 2 Part 2
 * NAME: Qijin Chau
 * DATE: 12/6/19
 *
 * gerp.cpp
 * Main driver for Project 2 Part 2
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "stringProcessing.h"
#include "linkedList.h"
#include "hashTable.h"
#include "DirNode.h"
#include "FSTree.h" 


void createHashTable(string directory, DirNode *treeRoot, hashTable &table);


int main(int argc, char *argv[])
{
	string input, iString, processedString, directory, filename;
	hashTable myTable;
	ofstream outfile;

	if(argc == 3) { 
		directory = argv[1];
		filename = argv[2];
		outfile.open(filename);

		FSTree t = FSTree(directory);
		DirNode *tRoot = t.getRoot();
		createHashTable(directory, tRoot, myTable);
	
		bool flag = true;
		while(flag) {
			cout <<  "Query? ";
			if(cin >> input) {
				if(input == "@q" || input == "@quit") {
					cerr << "\nGoodbye! Thank you and have a nice day.";
					flag = false;
				} else if(input == "@i" || input == "@insensitive") {
					if(flag) {
						cin >> iString;
						processedString = stripNonAlphaNum(iString);
						myTable.iSearch(processedString, outfile);
					}
				} else if(input == "@f") {
		    		cin >> filename;
		    		outfile.close();
		    		outfile.open(filename);
				} else {
					if(flag) {
						processedString = stripNonAlphaNum(input);
						myTable.search(processedString, outfile);
					}
				}		
			}
			cout << endl;
		}
	} else {
		cerr << "Usage: ./gerp inputDirectory outputFile\n";
	}

	return 0;
}

// Function createHashTable
// Parameters: A string, a pointer to a DirNode, 
//             and the address of a hashTable class
// Returns: Nothing
// Does: Takes directory as a command line argument, using the root of the
//       directory tree, finds all the files and creates a hash table using
//       all the words in each file. 
void createHashTable(string directory, DirNode *treeRoot, hashTable &table)
{
	string line, word;
	ifstream infile;

	if(treeRoot->hasFiles()) {
		int numFiles = treeRoot->numFiles();
		for(int i = 0; i < numFiles; ++i) {
			string filename = treeRoot->getFile(i);
			string finalFile = directory + "/" + filename;
			infile.open(finalFile);
			
			int count = 0;
			while(not getline(infile, line).fail()) {
				count++;
				stringstream ss;
				ss << line;	
				string lineNum = to_string(count);
				string toAdd = finalFile + ":" + lineNum + ": " + line;
				if(line != "" && line.length() != 1) {
					table.addOutput(toAdd);
					while(!ss.eof()) {
						ss >> word;
						table.insert(stripNonAlphaNum(word), table.outputsSize()-1);
					}
				}
			}
			infile.close();
		}
	}
	
	if(treeRoot->hasSubDir()) {
		int numSubDir = treeRoot->numSubDirs();
		for(int j = 0; j < numSubDir; ++j) {
			DirNode *temp = treeRoot->getSubDir(j); 
			string subDirName = temp->getName();

			createHashTable(directory+"/"+subDirName, treeRoot->getSubDir(j), table);
		}
	}
}