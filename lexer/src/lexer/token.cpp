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

Token::Token(const Token& t) {
  /** 先留着吧 */
  cout << "发生了拷贝构造" << endl;
};

bool Token::isVariable() { return this -> _type == TokenType::VARIABLE; };
bool Token::isScalar() {
  return (
    this -> _type == TokenType::INTEGER
    || this -> _type == TokenType::BOOLEAN
    || this -> _type == TokenType::STRING
    || this -> _type == TokenType::FLOAT
  );
};
string Token::getValue() const { return this -> _value; };

TokenType Token::getTokenType() const { return this -> _type; };
void Token::toString() {
  cout << "类型是: " << this -> _type << " 值是: " << this -> _value << endl;
};

Token Token::makeVarOrKeyword(ifstream& fs) {
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
    /**
     * 避免产生临时对象而触发拷贝构造
     */
    return Token(TokenType::BOOLEAN, str);
  }

  /**
   * 如果先定义 Token x(xxx)
   * 再return的话
   * 要给 Token 添加拷贝构造
   * 否则返回引用的时候调用默认的拷贝构造
   * 默认的拷贝构造比较sb有可能会造成_value丢值
   * 但是很奇怪的是如果传进来一个 true就会丢
   * 但是传个类似var的其他字符就不会丢
   * 真他娘的神奇
   * 有待研究......
   */
  if (Keywords::isKeyword(str)) {
    return Token(TokenType::KEYWORD, str);
  };

  return Token(TokenType::VARIABLE, str);
};

Token Token::makeString(ifstream& fs) {
  string str("");
  char quotationMarks = fs.get(); // quotationMarks是引号的意思 应该是 " 或 ' 或 `
  str += quotationMarks;

  while (fs.peek() != EOF) {
    char c = fs.get();
    if (c == quotationMarks) {
      str += c;
      return Token(TokenType::STRING, str);
    };
    str += c;
  }
  // 走到这里说明没有结束的引号 要抛出异常 先临时用cout代替
  cout << "获取字符串这块儿报错了" << endl;
  throw GetStringException();
}

