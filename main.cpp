#include <iostream>

#include "Autocomplete.h"
#include "PrefixMatcher.h"

int main() {
  // Autocomplete demonstration
  Autocomplete autocomplete;
  autocomplete.insert("apple");
  autocomplete.insert("app");
  autocomplete.insert("application");
  autocomplete.insert("banana");
  autocomplete.insert("bat");

  std::vector<std::string> suggestions = autocomplete.getSuggestions("app");
  std::cout << "Autocomplete suggestions for 'app':" << std::endl;
  for (const auto& suggestion : suggestions) {
    std::cout << suggestion << std::endl;
  }

  // Prefix matcher demonstration
  PrefixMatcher prefixMatcher;
  prefixMatcher.insert("192.168.1.0", 1);
  prefixMatcher.insert("192.168.2.0", 2);
  prefixMatcher.insert("10.0.0.0", 3);
  prefixMatcher.insert("10.1.0.0", 4);

  int routerNumber = prefixMatcher.selectRouter("192.168.1.0");
  if (routerNumber != -1) {
    std::cout << "Matched router number: " << routerNumber << std::endl;
  } else {
    std::cout << "No matching router found." << std::endl;
  }

  return 0;
}