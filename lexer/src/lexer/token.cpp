#include <iostream>
#include <fstream>
#include <string>
#include "token.h"
#include "keywords.h"

using namespace std;

Token::Token(TokenType type, string value): _type(type), _value(value){};
TokenType Token::getType() { return this -> _type; };
bool Token::isVariable() { return this -> _type == TokenType::VARIABLE; };
bool Token::isScalar() {
  return (
    this -> _type == TokenType::INTEGER
    || this -> _type == TokenType::BOOLEAN
    || this -> _type == TokenType::STRING
    || this -> _type == TokenType::FLOAT
  );
};
void Token::toString() {
  cout << "类型是: " << this -> _type << " 值是: " << this -> _value << endl;
};

Token& Token::makeVarOrKeyword(ifstream& fs) {
  string str("");
  // 提取一个字符串
  while (fs.peek() != EOF) {
    char lookahead = fs.get();
    if ((lookahead >= 'a' && lookahead <= 'z') || (lookahead >= 'A' && lookahead <= 'Z') || (lookahead == '_')) {
      str += lookahead;
    } else {
      break;
    }
  }

  if (str == "true" || str == "false") {
    Token t(TokenType::BOOLEAN, str);
    return t;
  }

  if (Keywords::isKeyword(str)) {
    Token t(TokenType::KEYWORD, str);
    return t;
  };

  Token t(TokenType::VARIABLE, str);
  return t;
};


