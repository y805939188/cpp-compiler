#ifndef _KEYWORDS_
#define _KEYWORDS_

#include <iostream>
#include <string>
#include <map>

using namespace std;


enum KEYWORDS {
  VAR = 0,
  LET,
  CONST,
  IF,
  ELSE,
  FOR,
  WHILE,
  BREAK,
  FUNCTION,
  RETURN,
  CONTINUE,
  NONE,
  NAN
};

typedef map<string, KEYWORDS> KeywordsMap;

class Keywords {

  public:
    static KeywordsMap keywords;

    static bool isKeyword (string word);

    static KeywordsMap CreateInitMap() {
      KeywordsMap temp_map;
      temp_map.insert(std::pair<string, KEYWORDS>("var", VAR));
      temp_map.insert(std::pair<string, KEYWORDS>("let", LET));
      temp_map.insert(std::pair<string, KEYWORDS>("const", CONST));
      temp_map.insert(std::pair<string, KEYWORDS>("if", IF));
      temp_map.insert(std::pair<string, KEYWORDS>("else", ELSE));
      temp_map.insert(std::pair<string, KEYWORDS>("while", WHILE));
      temp_map.insert(std::pair<string, KEYWORDS>("null", NONE));
      temp_map.insert(std::pair<string, KEYWORDS>("for", FOR));
      temp_map.insert(std::pair<string, KEYWORDS>("function", FUNCTION));
      temp_map.insert(std::pair<string, KEYWORDS>("return", RETURN));
      temp_map.insert(std::pair<string, KEYWORDS>("break", BREAK));
      temp_map.insert(std::pair<string, KEYWORDS>("continue", CONTINUE));
      temp_map.insert(std::pair<string, KEYWORDS>("NaN", NAN));
      return temp_map;
    };
};

// KeywordsMap Keywords::keywords = Keywords::CreateInitMap();

#endif
