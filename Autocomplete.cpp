#include "Autocomplete.h"

TrieNodeC::TrieNodeC() : isWord(false) {}

Autocomplete::Autocomplete() : root(new TrieNodeC) {}

Autocomplete::~Autocomplete() { destroyTrie(root); }

void Autocomplete::insert(string word) {
  if (word.empty()) {
    return;  // do not insert empty string
  }
  TrieNodeC* current = root;
  for (char c : word) {
    if (!current->children.count(c)) {
      current->children[c] = new TrieNodeC();
    }
    current = current->children[c];
  }
  current->isWord = true;
}

vector<string> Autocomplete::getSuggestions(string partWord) {
  TrieNodeC* current = root;
  for (char c : partWord) {
    if (!current->children.count(c)) {
      return {};  // no suggestion
    }
    current = current->children[c];
  }
  return collectSuggestions(current, partWord);
}

void Autocomplete::destroyTrie(TrieNodeC* node) {
  for (auto& child : node->children) {
    destroyTrie(child.second);
  }
  delete node;
}

vector<string> Autocomplete::collectSuggestions(TrieNodeC* node,
                                                string prefix) {
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