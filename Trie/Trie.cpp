#include <cctype>
#include "Trie.h"

void insertWord(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for (char ch : word) {
        char c = tolower(ch);
        if (curr->children[c - 'a'] == nullptr) {
            curr->children[c - 'a'] = new TrieNode();
        } 
        curr = curr->children[c - 'a'];
    }
    curr->endOfWord = true;
}

bool searchWord(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for (char ch : word) {
        char c = tolower(ch);
        if (curr->children[c - 'a'] == nullptr) {
            return false;
        }
        curr = curr->children[c -'a'];
    }
    return curr->endOfWord;
}