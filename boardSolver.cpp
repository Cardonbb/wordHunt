#include "boardSolver.h"

boardSolver::boardSolver()
{
    buildDictionary();
    //getBoard();
    // testing
    letters = { 
        'c', 'a', 't', 's', 
        'r', 'e', 'd', 'o', 
        'g', 'o', 'd', 'a', 
        'n', 'e', 't', 'p' 
    };
    int mapType = 1;
    createBoard(letters, mapType);
    findWords();

}



void boardSolver::getBoard()
{
    // this is placeholder for when i read into it 
    // this part will be done another day since 
    // i have to read board using opencv // another service
    int thisMap = 0;
    wordHuntMap = thisMap;
    vector<char> letter;
    letters = letter;
}

void boardSolver::buildDictionary()
{
    ifstream infile("filtered.txt");
    string word;    

    if(!infile.is_open()) 
    {

        cout << "Error: Could not open file." << endl;
    }
    while(getline(infile, word)) 
    {
        Dictionary.insertWord(word);
    }
    cout << "Tree Completed";

    infile.close();
}

void boardSolver::createBoard(const vector<char>& letters, const int wordHuntMap)
{
    int ROWS = 0;
    int COLS = 0;
    int index = 0;

    if(wordHuntMap == 1)
    {
        ROWS = 4;
        COLS = 4;
    }
    else
    {
        ROWS = 5;
        COLS = 5;
    }

    board.resize(ROWS, vector<char>(COLS));

    for(int i = 0; i < ROWS; i++) 
    {
        for(int j = 0; j < COLS; j++) 
        {
            board[i][j] = letters[index++];
        }
    }

    if(wordHuntMap == 3) 
    {
        board[0][0] = '#';
        board[0][4] = '#';
        board[4][0] = '#';
        board[4][4] = '#';
        board[2][2] = '#';
    } 
    
    if(wordHuntMap == 4) 
    {
        board[0][2] = '#';
        board[2][0] = '#';
        board[4][2] = '#';
        board[2][4] = '#';
    }

}

void boardSolver::findWords()
{
    int ROWS = board.size();
    int COLS = board[0].size();
    
    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS; c++)
        {
            if(board[r][c] != '#')
            {
                vector<pair<int,int>> path;
                dfs(r, c, Dictionary.root, "", path);
            }
        }
    }
}

void boardSolver::dfs(int r, int c, TrieNode* node, string currentWord, vector<pair<int, int>>& path) 
{
    if(r < 0 || c < 0 || r >= board.size() || c >= board[0].size() 
             || board[r][c] == '#' || !node->child[board[r][c] - 'a'])
    {
        return;
    }


    char letter = board[r][c];
    currentWord += letter;
    node = node->child[letter - 'a'];

    board[r][c] = '#';
    path.push_back({r, c});


    if(node->wordEnd)
    {
        WordPath wp;
        wp.word = currentWord;
        wp.path = path;
        foundWords.push_back(wp);

        node->wordEnd = false;

    }

    vector<pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, 
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} 
    };

    for(auto [dr, dc] : directions) 
    {
        dfs(r + dr, c + dc, node, currentWord, path);
    }
    

    path.pop_back();
    board[r][c] = letter;


    return;
}
