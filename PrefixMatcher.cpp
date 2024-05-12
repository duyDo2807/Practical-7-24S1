#include "PrefixMatcher.h"

PrefixMatcher::PrefixMatcher() : root(new TrieNode()) {}

PrefixMatcher::~PrefixMatcher() { destroyTrie(root); }

int PrefixMatcher::selectRouter(string networkAddress) {
  TrieNode* current = root;
  for (char c : networkAddress) {
    if (!current->children.count(c)) {
      return -1;  // no match
    }
    current = current->children[c];
  }
  return current->routerNumber;
}

void PrefixMatcher::insert(string address, int routerNumber) {
  if (address.empty()) {
    return;  // do not insert empty addresses
  }
  TrieNode* current = root;
  for (char c : address) {
    if (!isalnum(c)) {
      return;  // do not insert non alphanumeric characters
    }
    if (!current->children.count(c)) {
      current->children[c] = new TrieNode();
    }
    current = current->children[c];
  }
  current->routerNumber = routerNumber;
}

void PrefixMatcher::destroyTrie(TrieNode* node) {
  for (auto& child : node->children) {
    destroyTrie(child.second);
  }
  delete node;
}