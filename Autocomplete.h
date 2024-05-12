#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class TrieNode {
 public:
  bool isWord;
  unordered_map<char, TrieNode*> children;

  TrieNode();
};

class Autocomplete {
 private:
  TrieNode* root;

 public:
  Autocomplete();

  ~Autocomplete();

  void insert(string word);

  vector<string> getSuggestions(string partWord);

 private:
  void destroyTrie(TrieNode* node);

  vector<string> collectSuggestions(TrieNode* node, string prefix);
};

#endif