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
    static Token makeVarOrKeyword(ifstream& fs);
    static Token makeString(ifstream& fs);
};

#endif
