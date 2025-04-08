#ifndef BOARD_SOLVER_H
#define BOARD_SOLVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "trie.h"
#include <sstream>

using namespace std;

struct WordPath {
    string word;
    vector<pair<int, int>> path; 
};

class boardSolver {
private:
    int wordHuntMap;
    vector<char> letters;
    Trie Dictionary;
    vector<vector<char>> board;


public:
    vector<WordPath> foundWords;
    boardSolver();
    void getBoard();
    void createBoard(const vector<char>& letters, const int wordHuntMap); 
    void buildDictionary(); 
    void findWords(); 
    void dfs(int r, int c, TrieNode* node, string currentWord, vector<pair<int, int>>& path);
};

#endif 
