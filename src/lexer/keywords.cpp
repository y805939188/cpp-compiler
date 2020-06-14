#include <iostream>
#include <string>
#include "keywords.h"

using namespace std;

KeywordsMap Keywords::keywords = Keywords::CreateInitMap();

bool Keywords::isKeyword (string word) {
  map<string, KEYWORDS>::const_iterator result = Keywords::keywords.find(word);
  if (result != Keywords::keywords.end()) return true;
  return false;
};
