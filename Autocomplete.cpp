#include "Autocomplete.h"

TrieNode::TrieNode() : isWord(false) {}

Autocomplete::Autocomplete() : root(new TrieNode) {}

Autocomplete::~Autocomplete() { destroyTrie(root); }

void Autocomplete::insert(string word) {
  if (word.empty()) {
    return;  // do not insert empty string
  }
  TrieNode* current = root;
  for (char c : word) {
    if (isalpha(c)) {
      return;  // do not insert non alphabetic characters
    }
    if (!current->children.count(c)) {
      current->children[c] = new TrieNode();
    }
    current = current->children[c];
  }
  current->isWord = true;
}

vector<string> Autocomplete::getSuggestions(string partWord) {
  TrieNode* current = root;
  for (char c : partWord) {
    if (!current->children.count(c)) {
      return {};  // no suggestion
    }
    current = current->children[c];
  }
  return collectSuggestions(current, partWord);
}

void Autocomplete::destroyTrie(TrieNode* node) {
  for (auto& child : node->children) {
    destroyTrie(child.second);
  }
  delete node;
}

vector<string> Autocomplete::collectSuggestions(TrieNode* node, string prefix) {
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