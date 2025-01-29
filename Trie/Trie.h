#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string>


struct TrieNode {
    TrieNode* children[26];
    bool endOfWord = false;

    TrieNode() {
        for (int i = 0; i < 26; ++i) children[i] = NULL;
    }
};

void insertWord(TrieNode* root, const std::string& word);
bool searchWord(TrieNode* root, const std::string& word);

#endif