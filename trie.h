#ifndef TRIE_H
#define TRIE_H
#include <string>

using namespace std;


class TrieNode {
public:
    TrieNode* child[26];
    bool wordEnd;
    TrieNode();
};

class Trie {
public:
    TrieNode* root;
    Trie();
    void insertWord(string word);
    bool searchWord(string word);
    bool startsWith(string word);
};

#endif // TRIE_H
