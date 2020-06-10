#ifndef _TOKEN_
#define _TOKEN_

#include <iostream>
#include <string>

using namespace std;

typedef enum {
  KEYWORD = 0,
  VARIABLE,
  BOOLEAN,
  FLOAT,
  STRING,
  BRACKET,
  OPERATOR,
  INTEGER
} TokenType;

class Token {
  TokenType _type;
  string _value;
  static string getTypeName(int index) {
    switch(index) {
      case 0: return "KEYWORD";
      case 1: return "VARIABLE";
      case 2: return "BOOLEAN";
      case 3: return "FLOAT";
      case 4: return "STRING";
      case 5: return "BRACKET";
      case 6: return "OPERATOR";
      case 7: return "INTEGER";
    }
  }
  public:
    Token() {};
    Token(TokenType type, string value);
    Token(const Token & t);
    TokenType getType();
    bool isVariable();
    bool isScalar();
    void toString();
    string getValue () const;
    TokenType getTokenType () const;
    static Token getVarOrKeyword(istream& is);
    static Token getString(istream& is);
    static Token getOperator(istream& is);
};

#endif
