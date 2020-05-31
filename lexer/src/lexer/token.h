#ifndef _TOKEN_
#define _TOKEN_

#include <iostream>
#include <string>

using namespace std;

typedef enum {
  KEYWORD,
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
  public:
    Token(TokenType type, string value);
    TokenType getType();
    bool isVariable();
    bool isScalar();
    void toString();
};

#endif
