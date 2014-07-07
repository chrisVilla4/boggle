// Michael Chen <mhc002>

#include "boggleutil.h"   

string toLowerCase(string s) {
    for(unsigned int i = 0; i < s.size(); ++i) {
        s[i] = tolower(s[i]);
    }

    return s;
}

bool isPrefix(string word, string prefix, int start) {
    if(prefix.size() > word.size() - start) {
        return false;
    }

    for(unsigned int i = 0; i < prefix.size(); ++i) {
        if(word.at(i + start) != prefix.at(i)) {
            return false;
        }
    }

    return true;
}

//=============================================================================
// TST
//=============================================================================
void TST::makeEmpty(TSTNode* parent) {
	if(parent != nullptr) {
		makeEmpty(parent->left);
		makeEmpty(parent->middle);
		makeEmpty(parent->right);
		delete parent;
	}

	parent = nullptr;
}

TST::~TST() {
	makeEmpty(root);
}

void TST::add(string word) {
	if(root == nullptr) {
		root = new TSTNode(word.at(0));
	}

	TSTNode* prev = nullptr;
	TSTNode* current = root;

	// For each letter in word
	for(unsigned int i = 0; i < word.size(); ++i) {
		while(current != nullptr && current->data != word.at(i)) {
			if(current->data > word.at(i)) {		
				if(current->left == nullptr) {
					current->left = new TSTNode(word.at(i));
				}

				current = current->left;
			} else if (current->data < word.at(i)) {
				if(current->right == nullptr) {
					current->right = new TSTNode(word.at(i));
				}

				current = current->right;
			}
		}

		if(current == nullptr) {
			current = new TSTNode(word.at(i));
		}

		if(prev != nullptr) {
			if(prev->middle == nullptr) {
				prev->middle = current;
			}
		}

		prev = current;
		current->prefix = true;
		current = current->middle;
	}

	if(prev->middle == nullptr) {
		prev->prefix = false;
	}

	prev->end = true;
}

bool TST::contains(string word) {
	if(root == nullptr) {
		return false;
	}

	TSTNode* prev = nullptr;
	TSTNode* current = root;

	for(unsigned int i = 0; i < word.size(); ++i) {
		while(current != nullptr && current->data != word.at(i)) {
			if(current->data > word.at(i)) {
				if(current->left == nullptr) {
					return false;
				} else {
					current = current->left;
				}
			} else {
				if(current->right == nullptr) {
					return false;
				} else {
					current = current->right;
				}
			}
		}

		prev = current;
		current = current->middle;
	}

	return prev->end;
}

bool TST::isPrefix(string word) {
	if(root == nullptr) {
		return false;
	}

	TSTNode* prev = nullptr;
	TSTNode* current = root;

	for(unsigned int i = 0; i < word.size(); ++i) {
		while(current != nullptr && current->data != word.at(i)) {
			if(current->data > word.at(i)) {
				if(current->left == nullptr) {
					return false;
				} else {
					current = current->left;
				}
			} else {
				if(current->right == nullptr) {
					return false;
				} else {
					current = current->right;
				}
			}
		}

		prev = current;
		current = current->middle;
	}

	return prev->prefix;
}

//=============================================================================
// Boggle Board
//=============================================================================
vector<int> BoggleBoardGraph::getAdjacentIndexList(unsigned int index) {
	vector<int> adjIndexList;

	int top = index - colCount;
	int bottom = index + colCount;

	if(top >= 0) {
		adjIndexList.push_back(top);
	}

	if((index % colCount) != 0) {
		adjIndexList.push_back(index - 1);

		if(top >= 0) {
			adjIndexList.push_back(top - 1);
		}

		if(bottom < totalCount) {
			adjIndexList.push_back(bottom - 1);
		}
	}

	if((index % colCount) != (colCount - 1)) {
		adjIndexList.push_back(index + 1);

		if(top >= 0) {
			adjIndexList.push_back(top + 1);
		}

		if(bottom < totalCount) {
			adjIndexList.push_back(bottom + 1);
		}
	}

	if(bottom < totalCount) {
		adjIndexList.push_back(bottom);
	}

	return adjIndexList;
}

void BoggleBoardGraph::addNode(BoggleBoardNode* node) {
	nodeList.push_back(node);
}

void BoggleBoardGraph::resetBoard() {
	for(unsigned int i = 0; i < nodeList.size(); ++i) {
		delete nodeList[i];
	}

	nodeList.clear();
}

void BoggleBoardGraph::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
	unsigned int index = 0;
	rowCount = rows;
	colCount = cols;
	totalCount = rows * cols;

	for(unsigned int i = 0; i < rows; ++i) {
		for(unsigned int j = 0; j < cols; ++j) {
			BoggleBoardNode* newNode = new BoggleBoardNode(index, toLowerCase(diceArray[i][j]));
			newNode->adjList = getAdjacentIndexList(index);
			addNode(newNode);
			++index;
		}
	}
}

bool BoggleBoardGraph::setPath(const string& word, int index, unsigned int cursor, vector<int> &path) {
	BoggleBoardNode* current = nodeList[index];
	string prefix = current->data;
	vector<int> adjIndexList = current->adjList;

	if(isPrefix(word, prefix, cursor)) {
		current->done = true;
		path.push_back(index);

		for(unsigned int i = 0; i < adjIndexList.size(); ++i) {
			bool checked = nodeList[adjIndexList[i]]->done;

			if(cursor + prefix.size() == word.size()) {
				current->done = false;
				return true;
			}

			if(!checked) {
				if(setPath(word, adjIndexList[i], cursor + prefix.size(), path)) {
					current->done = false;
					return true;
				}
			}
		}

		current->done = false;
		path.pop_back();
	}
	
	return false;
}

vector<int> BoggleBoardGraph::isOnBoard(const string& word_to_check) {
	vector<int> path;

	for(unsigned int i = 0; i < nodeList.size(); ++i) {
		if(setPath(word_to_check, i, 0, path)) {
			return path;
		}
	}

	return path;
}

void BoggleBoardGraph::addAllValidWords(set<string>& validWordSet, string prefix, int index, unsigned int minimum_word_length, TST* lexicon) {
	BoggleBoardNode* current = nodeList[index];
	string word = prefix + current->data;
	vector<int> adjIndexList = current->adjList;

	if(lexicon->contains(word)) {
		if(word.size() >= minimum_word_length) {
			validWordSet.insert(word);
		}
	}

	if(lexicon->isPrefix(word)) {
		current->done = true;

		for(unsigned int i = 0; i < adjIndexList.size(); ++i) {
			bool checked = nodeList[adjIndexList[i]]->done;

			if(!checked) {
				addAllValidWords(validWordSet, word, adjIndexList[i], minimum_word_length, lexicon);
			}
		}

		current->done = false;
	}
}

set<string> BoggleBoardGraph::getAllValidWords(unsigned int minimum_word_length, TST* lexicon) {
	set<string> validWordSet;

	for(unsigned int i = 0; i < nodeList.size(); ++i) {
		addAllValidWords(validWordSet, "", i, minimum_word_length, lexicon);
	}

	return validWordSet;
};
