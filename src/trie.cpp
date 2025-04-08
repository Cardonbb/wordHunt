#include "trie.h"


TrieNode::TrieNode()
{
    wordEnd = false;
    for(int i = 0; i < 26; i++)
    {
        child[i] = NULL;
    }
}

Trie::Trie()
{
    root = new TrieNode();
}

void Trie::insertWord(string word)
{
    TrieNode* curr = root;
    
    for(char c : word)
    {
        int i = c - 'a';
        if(curr->child[i] == NULL)
        {
            curr->child[i] = new TrieNode();
        }
        curr = curr->child[i];
    }
    curr->wordEnd = true;
}

bool Trie::searchWord(string word)
{
    TrieNode* curr = root;

    for(char c : word)
    {
        int i  = c - 'a';
        if(curr->child[i] == NULL)
        {
            return false;
        }
        curr = curr->child[i];
    }
    return curr->wordEnd;
}


bool Trie::startsWith(string word)
{
    TrieNode* curr = root;
    for(char c : word)
    {
        int i = c - 'a';
        if(curr->child[i] == NULL)
        {
            return false;
        }
        curr = curr->child[i];
    }
    return true;
}
