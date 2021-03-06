#ifndef _TOKEN_
#define _TOKEN_

#include <iostream>
#include <string>

using namespace std;

typedef enum {
  KEYWORD = 0,
  VARIABLE,
  BOOLEAN,
  DOUBLE,
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
    bool isNumber();
    bool isVariable();
    bool isScalar();
    bool isOperator();
    bool isString();
    bool isBracket();
    bool isKeyword();
    void toString();
    string getValue () const;
    TokenType getTokenType () const;
    static shared_ptr<Token> getVarOrKeyword(istream& is);
    static shared_ptr<Token> getDouble(istream& is); // js或者python中的数字全都是double
    static shared_ptr<Token> getString(istream& is);
    static shared_ptr<Token> getOperator(istream& is);
};

typedef shared_ptr<Token> D_Token;

#endif
