#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "trie.h"
#include "boardSolver.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() 
{
    boardSolver solver;
    
    for(auto& wp : solver.foundWords) 
    {
        cout << wp.word << " ";
        for(auto& p : wp.path) 
        {
            cout << p.first << "," << p.second << " ";
        }
        cout << endl;
    }

    return 0;
}
