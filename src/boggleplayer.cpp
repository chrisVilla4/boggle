// Michael Chen <mhc002>

#include "boggleplayer.h"

void BogglePlayer::buildLexicon(const set<string>& word_list) { 
    if(isLexiconBuilt) {
        delete lexicon;
        lexicon = new TST();
    }

    for(set<string>::iterator it = word_list.begin(); it != word_list.end(); ++it) {
        lexicon->add(*it);
    }

    isLexiconBuilt = true;
}   

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
    if(isBoardSet) {
        board->resetBoard();
    }

    board->setBoard(rows, cols, diceArray);

    isBoardSet = true;
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
    if(!isBoardSet || !isLexiconBuilt) {
        return false;
    }

    set<string> wordList = board->getAllValidWords(minimum_word_length, lexicon);
    
    *words = wordList;

    return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
    return isLexiconBuilt && lexicon->contains(word_to_check);
}

vector<int> BogglePlayer::isOnBoard(const string& word_to_check) {
    vector<int> path;

    if(!isBoardSet || !isLexiconBuilt) {
        return path;
    }

    path = board->isOnBoard(word_to_check);

    return path;
}

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
    new_board = new string*[*rows];
    
    for(unsigned int i = 0; i < *rows; ++i) {
        new_board[i] = new string[*cols];
    }
}
