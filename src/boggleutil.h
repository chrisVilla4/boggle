// Michael Chen <mhc002>

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class TSTNode {
public:
	TSTNode* left;
	TSTNode* middle;
	TSTNode* right;  
	const char data;
	bool end;
	bool prefix;

	TSTNode(const char& l): data(l), end(false), prefix(false){
		left = middle = right = nullptr;
	}
};



class TST {
private:
	TSTNode* root; 

	void makeEmpty(TSTNode* parent);
public:
	TST(): root(nullptr) {}

	~TST();
	// Takes in a string and adds it to itself
	void add(string word);

	// Takes in a string and returns true if it is a valid word
	bool contains(string word);

	// Takes in a string and returns true if it is a prefix to a valid word
	bool isPrefix(string pre);
};



class BoggleBoardNode {
public:
	vector<int> adjList;
	string data;
	int index;
	bool done;

	BoggleBoardNode(int i, string s){
		index = i;
		data = s;
		done = false;
	}
};



class BoggleBoardGraph {
private:
	vector<BoggleBoardNode*> nodeList;
	unsigned int rowCount;
	unsigned int colCount;
	int totalCount;

	// Get a nodes adjacent node indices
	vector<int>getAdjacentIndexList(unsigned int index);

	// Add a node to the board
	void addNode(BoggleBoardNode* node);

	// Assign a path to make a word on the board if it exists
	bool setPath(const string& word, int index, unsigned int cursor, vector<int> &path);

	// Add all valid words that can be found on the board to a set
	void addAllValidWords(set<string>& validWordSet, string prefix, int index, unsigned int minimum_word_length, TST* lexicon);
public:
	BoggleBoardGraph() {
		rowCount = 0;
		colCount = 0;
		totalCount = 0;
	};

	// Removes all nodes on the board and resets counts
	void resetBoard();

	// Implementation of setBoard in boggleplayer.h
	void setBoard(unsigned int rows, unsigned int cols, string** diceArray);

	// Implementation of isOnBoard in boggleplayer.h
	vector<int> isOnBoard(const string& word_to_check);

	// Implementation of getAllValidWords in boggleplayer.h
	set<string> getAllValidWords(unsigned int minimum_word_length, TST* lexicon);
};

#endif