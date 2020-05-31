#include <iostream>
#include <string>
#include "token.h"

using namespace std;

Token::Token(TokenType type, string value): _type(type), _value(value){};
TokenType Token::getType() { return this -> _type; };
bool Token::isVariable() { return this -> _type == TokenType::VARIABLE; };
bool Token::isScalar() { return ( this -> _type == TokenType::INTEGER || this -> _type == TokenType::BOOLEAN || this -> _type == TokenType::STRING || this -> _type == TokenType::FLOAT); };
void Token::toString() { cout << "类型是: " << this -> _type << " 值是: " << this -> _value << endl; };
