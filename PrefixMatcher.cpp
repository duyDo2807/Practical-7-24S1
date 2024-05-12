#include "PrefixMatcher.h"

TrieNodeM::TrieNodeM() : routerNumber(-1) {}

PrefixMatcher::PrefixMatcher() : root(new TrieNodeM()) {}

PrefixMatcher::~PrefixMatcher() { destroyTrie(root); }

int PrefixMatcher::selectRouter(string networkAddress) {
  TrieNodeM* current = root;
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
  TrieNodeM* current = root;
  for (char c : address) {
    if (!current->children.count(c)) {
      current->children[c] = new TrieNodeM();
    }
    current = current->children[c];
  }
  current->routerNumber = routerNumber;
}

void PrefixMatcher::destroyTrie(TrieNodeM* node) {
  for (auto& child : node->children) {
    destroyTrie(child.second);
  }
  delete node;
}