#ifndef PREFIXMATCHER_H
#define PREFIXMATCHER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Autocomplete.h"

using namespace std;

class PrefixMatcher {
 private:
  struct TrieNode {
    int routerNumber;
    unordered_map<char, TrieNode*> children;

    TrieNode();
  };

  TrieNode* root;

 public:
  PrefixMatcher();

  ~PrefixMatcher();

  int selectRouter(string networkAddress);

  void insert(string address, int routerNumber);

 private:
  void destroyTrie(TrieNode* node);
};

#endif