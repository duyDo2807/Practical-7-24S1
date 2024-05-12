#ifndef PREFIXMATCHER_H
#define PREFIXMATCHER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class TrieNodeM {
 public:
  int routerNumber;
  unordered_map<char, TrieNodeM*> children;

  TrieNodeM();
};
class PrefixMatcher {
 private:
  TrieNodeM* root;

 public:
  PrefixMatcher();

  ~PrefixMatcher();

  int selectRouter(string networkAddress);

  void insert(string address, int routerNumber);

 private:
  void destroyTrie(TrieNodeM* node);
};

#endif