#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class TrieNodeC {
 public:
  bool isWord;
  unordered_map<char, TrieNodeC*> children;

  TrieNodeC();
};

class Autocomplete {
 private:
  TrieNodeC* root;

 public:
  Autocomplete();

  ~Autocomplete();

  void insert(string word);

  vector<string> getSuggestions(string partWord);

 private:
  void destroyTrie(TrieNodeC* node);

  vector<string> collectSuggestions(TrieNodeC* node, string prefix);
};

#endif