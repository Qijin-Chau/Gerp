/* Comp 15 - Fall 2019
 * Project 2 Part 1
 * NAME: Qijin Chau
 * DATE: 11/20/19
 *
 * stringProcessing.cpp
 * Implementation of the stripNonAlphaNum function 
 * declared in stringProcessing.h
 */

#include <iostream>
#include "stringProcessing.h"

using namespace std;

int findStart(string toProcess, string alphabetLow, string allNums);
int findEnd(string toProcess, string alphabetLow, string allNums);
bool isAlphaNum(char toProcess, string alphabetLow, string allNums);

// Function stripNonAlphaNum
// Parameters: A string
// Returns: A string
// Does: Removes all leading and trailing non-alphanumeric characters
//       from the string then returns the processed string.
string stripNonAlphaNum(string toProcess)
{
	string alphabetLow = "abcdefghijklmnopqrstuvwxyz";
	string allNums = "0123456789";
	string processedString;
	unsigned long begin = 0, end = toProcess.length()-1, i; 
	bool hasAlphaNum = false;

	for(i=0; i<toProcess.length(); ++i) {
		if(isAlphaNum(toProcess[i], alphabetLow, allNums)) {
			hasAlphaNum = true;
			i = toProcess.length();
		}
	}

	if(hasAlphaNum) {
		if(!isAlphaNum(toProcess[begin], alphabetLow, allNums)) 
			begin = findStart(toProcess, alphabetLow, allNums);

		if(!isAlphaNum(toProcess[end], alphabetLow, allNums)) 
			end = findEnd(toProcess, alphabetLow, allNums);
	}

	if(hasAlphaNum) {
		for(i=begin; i<end+1; ++i)
			processedString += toProcess[i];
	}

	return processedString;
}

// Function findStart
// Parameters: Three strings
// Returns: An integer
// Does: Returns the index of where the first alphabet letter or number
//       is on the first string passed in.
int findStart(string toProcess, string alphabetLow, string allNums)
{
	int begin = 0;

	for(unsigned long i=0; i<toProcess.length(); ++i) {
		for(unsigned long j=0; j<allNums.length(); ++j) {
			if (tolower(toProcess[i]) == alphabetLow[j] || 
				toProcess[i] == allNums[j]) {
			
				begin = i;
				return begin;
			}
		}

		for(unsigned long j=allNums.length(); j<alphabetLow.length(); ++j) {
			if (tolower(toProcess[i]) == alphabetLow[j]) {
			
				begin = i;
				return begin;
			}
		}
	}

	return begin;
}

// Function findEnd
// Parameters: Three strings
// Returns: An integer
// Does: Returns the index of where the last alphabet letter or number
//       is on the first string passed in.
int findEnd(string toProcess, string alphabetLow, string allNums)
{
	int end = toProcess.length()-1;

	for(unsigned long i=toProcess.length()-1; i>=0; --i) {
		for(unsigned long j=0; j<allNums.length(); ++j) {
			if (tolower(toProcess[i]) == alphabetLow[j] ||
				toProcess[i] == allNums[j]) {
				
				end = i;
				return end;
			}
		}

		for (unsigned long j=allNums.length(); j<alphabetLow.length(); ++j)
		{
			if (tolower(toProcess[i]) == alphabetLow[j]) {
				
				end = i;
				return end;
			}
		}
	}

	return end;
}

// Function isAlphaNum
// Parameters: A character and two strings
// Returns: A boolean
// Does: Returns true if the character passed in is an alphabet letter
//       or a number; false otherwise. 
bool isAlphaNum(char toProcess, string alphabetLow, string allNums)
{
	for (unsigned long i = 0; i < alphabetLow.length(); ++i) {
		if(tolower(toProcess) == alphabetLow[i]) 
			return true;
	}

	for (unsigned long j = 0; j < allNums.length(); ++j) {
		if(toProcess == allNums[j]) 
			return true;
	}

	return false;
}

/*
int main()
{
	string s, newString;
	
	while(cin >> s) {
		newString = stripNonAlphaNum(s);
		cout << "Old string: " << s << endl;;
		cout << "Processed string: " << newString << endl;
	}

	return 0;
}
*/