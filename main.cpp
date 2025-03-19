#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "trie.h"
#include "boardSolver.h"

using namespace std;

int main() 
{
    boardSolver solver;

    // Now you can print the found words after the constructor has done all the work
    cout << "Found words: " << solver.foundWords.size() << endl;


    
    return 0;
}
