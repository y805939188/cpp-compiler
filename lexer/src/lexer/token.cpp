#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "token.h"
#include "keywords.h"

using namespace std;

struct GetStringException : public exception
{
  const char * what () const throw ()
  {
    return "make string的函数出错";
  }
};
 

Token::Token(TokenType type, string value): _type(type), _value(value){};

Token::Token(const Token & t):_type(t._type), _value(t._value) {
  cout << "发生了拷贝构造" << endl;
};

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
    char c = fs.get();
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) {
      str += c;
    } else {
      break;
    }
  }

  if (str == "true" || str == "false") {
    Token t(TokenType::BOOLEAN, str);
    return t;
  }

  /**
   * 要给 Token 添加拷贝构造
   * 否则返回引用的时候调用默认的拷贝构造
   * 默认的拷贝构造比较sb有可能会造成_value丢值
   * 但是很奇怪的是如果传进来一个 true就会丢
   * 但是传个类似var的其他字符就不会丢
   * 真他娘的神奇
   * 有待研究......
   */
  if (Keywords::isKeyword(str)) {
    Token t(TokenType::KEYWORD, str);
    return t;
  };

  Token t(TokenType::VARIABLE, str);
  return t;
};

Token& Token::makeString(ifstream& fs) {
  string str("");
  char quotationMarks = fs.get(); // quotationMarks是引号的意思 应该是 " 或 ' 或 `
  str += quotationMarks;

  while (fs.peek() != EOF) {
    char c = fs.get();
    if (c == quotationMarks) {
      str += c;
      Token t(TokenType::STRING, str);
      return t;
    };
    str += c;
  }
  // 走到这里说明没有结束的引号 要抛出异常 先临时用cout代替
  cout << "获取字符串这块儿报错了" << endl;
  throw GetStringException();
}

