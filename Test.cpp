#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class TrieNode {
 public:
  bool isWord;
  unordered_map<char, TrieNode*> children;

  TrieNode() : isWord(false) {}
};

class Autocomplete {
 private:
  TrieNode* root;

 public:
  Autocomplete() : root(new TrieNode()) {}

  ~Autocomplete() { destroyTrie(root); }

  void insert(string word) {
    if (word.empty()) {
      return;  // do not insert empty strings
    }
    TrieNode* current = root;
    for (char c : word) {
      if (!isalpha(c)) {
        return;  // do not insert non-alphabetic characters
      }
      if (!current->children.count(c)) {
        current->children[c] = new TrieNode();
      }
      current = current->children[c];
    }
    current->isWord = true;
  }

  vector<string> getSuggestions(string partialWord) {
    TrieNode* current = root;
    for (char c : partialWord) {
      if (!current->children.count(c)) {
        return {};  // no suggestions
      }
      current = current->children[c];
    }
    return collectSuggestions(current, partialWord);
  }

 private:
  void destroyTrie(TrieNode* node) {
    for (auto& child : node->children) {
      destroyTrie(child.second);
    }
    delete node;
  }

  vector<string> collectSuggestions(TrieNode* node, string prefix) {
    vector<string> suggestions;
    if (node->isWord) {
      suggestions.push_back(prefix);
    }
    for (auto& child : node->children) {
      string newPrefix = prefix + child.first;
      vector<string> childSuggestions =
          collectSuggestions(child.second, newPrefix);
      suggestions.insert(suggestions.end(), childSuggestions.begin(),
                         childSuggestions.end());
    }
    return suggestions;
  }
};

class PrefixMatcher {
 private:
  struct TrieNode {
    int routerNumber;
    unordered_map<char, TrieNode*> children;

    TrieNode() : routerNumber(-1) {}
  };

  TrieNode* root;

 public:
  PrefixMatcher() : root(new TrieNode()) {}

  ~PrefixMatcher() { destroyTrie(root); }

  int selectRouter(string networkAddress) {
    TrieNode* current = root;
    for (char c : networkAddress) {
      if (!current->children.count(c)) {
        return -1;  // no match
      }
      current = current->children[c];
    }
    return current->routerNumber;
  }

  void insert(string address, int routerNumber) {
    if (address.empty()) {
      return;  // do not insert empty addresses
    }
    TrieNode* current = root;
    for (char c : address) {
      if (!isalnum(c)) {
        return;  // do not insert non-alphanumeric characters
      }
      if (!current->children.count(c)) {
        current->children[c] = new TrieNode();
      }
      current = current->children[c];
    }
    current->routerNumber = routerNumber;
  }

 private:
  void destroyTrie(TrieNode* node) {
    for (auto& child : node->children) {
      destroyTrie(child.second);
    }
    delete node;
  }
};