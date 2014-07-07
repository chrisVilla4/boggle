// Michael Chen <mhc002>
 
#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "baseboggleplayer.h"
#include "boggleutil.h"

class BogglePlayer : public BaseBogglePlayer{
private:
    TST* lexicon;
    BoggleBoardGraph* board;
    bool isBoardSet; 
    bool isLexiconBuilt;

public:
    BogglePlayer() {
        lexicon = new TST();
        board = new BoggleBoardGraph();
        isBoardSet = false;
        isLexiconBuilt = false;
    }

    ~BogglePlayer(){};
    
    // Takes as argument a set containing the words specifying the official 
    // lexicon to be used for the game. Each word in the set will be a string 
    // consisting of lowercase letters a-z only. This function will load words
    // into a ternary search tree (lexicon) and used as needed by the BogglePlayer
    void buildLexicon(const set<string>& word_list);

    // Takes as arguments the number of rows and columns in the board, and an 
    // array of arrays of strings representing what is shown on the face of 
    // dice on a Boggle board. A Boggle board is a rectangular grid of dice; 
    // the height (number of rows) is given by the first argument, the width 
    // of this grid (i.e. number of columns) is given by the second argument. 
    // The elements of the vector specify the contents of the board in row 
    // major order. Each string may be upper or lower case, and may contain 
    // one or more letters; A graph will be used to construct the board 
    void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
    
    // Takes two arguments: an int specifying a minimum word length, and a 
    // pointer to a set of strings. It returns false if either setBoard() or 
    // buildLexicon() have not yet been called for this BogglePlayer. If they 
    // have both been called, it will return true, after filling the set with 
    // all the words that (1) are of at least the given minimum length, 
    // (2) are in the lexicon specified by the most recent call to buildLexicon(), 
    // and (3) can be found by following an acyclic simple path on the board 
    // specified by the most recent call to setBoard().
    bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
    
    // Takes as argument a const string passed by reference, and determines 
    // whether it be found in the lexicon. The function returns true if the 
    // word is in the lexicon, and returns false if it is not in the lexicon 
    // or if buildLexicon() has not yet been called.
    bool isInLexicon(const string& word_to_check);
    
    // Takes as argument a string passed by reference. It determines whether 
    // the string can be found by following an acyclic simple path on the board
    //  specified by the most recent call to setBoard(). If it is possible to 
    //  find the word in the current board, the function returns vector with 
    //  integers specifying the locations of dice that can be used to form the 
    //  word, in the order that spells the word. The integers used to specify 
    //  the locations are row-major-order indices. If is is NOT possible to 
    //  form the word, or if setBoard() has not yet been called the function 
    //  returns an empty vector.
    vector<int> isOnBoard(const string& word_to_check);
    
    // For testing
    void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);
};

#endif