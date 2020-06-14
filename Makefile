# NAME: Qijin Chau
# DATE: 12/6/19
#
# Makefile for Project 2 Part 2 (fall 2019)
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 

linkedList: linkedList.o testLL.o
	${CXX} -O2 -o $@ $^

hashTable: linkedList.o hashTable.o testHT.o
	${CXX} -O2 -o $@ $^

gerp: linkedList.o hashTable.o FSTree.o DirNode.o stringProcessing.o gerp.o
	${CXX} -O2 -o $@ $^

clean:
	rm -rf gerp *.o *.dSYM


%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<


provide:
	provide comp15 proj2part2 stringProcessing.h stringProcessing.cpp \
			DirNode.h DirNode.o gerp.cpp hashTable.h hashTable.cpp linkedList.h \
			linkedList.cpp testLL.cpp testHT.cpp FSTree.h FSTree.o README Makefile