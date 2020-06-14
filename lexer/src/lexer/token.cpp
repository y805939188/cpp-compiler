#include <iostream>
#include <istream>
#include <string>
#include <exception>
#include <utils/utils.h>
#include "token.h"
#include "keywords.h"

using namespace std; 

Token::Token(TokenType type, string value): _type(type), _value(value){};

Token::Token(const Token& t) {
  /** 先留着吧 */
  cout << "发生了拷贝构造" << endl;
};

bool Token::isString() { return this -> _type == TokenType::STRING; };

bool Token::isOperator() { return this -> _type == TokenType::OPERATOR; };

bool Token::isVariable() { return this -> _type == TokenType::VARIABLE; };

bool Token::isBracket() { return this -> _type == TokenType::BRACKET; };

bool Token::isKeyword() { return this -> _type == TokenType::KEYWORD; };

bool Token::isNumber() { return this -> _type == TokenType::INTEGER || this -> _type == TokenType::DOUBLE; };

bool Token::isScalar() {
  return (
    this -> _type == TokenType::INTEGER
    || this -> _type == TokenType::BOOLEAN
    || this -> _type == TokenType::STRING
    || this -> _type == TokenType::DOUBLE
  );
};
string Token::getValue() const { return this -> _value; };

TokenType Token::getTokenType() const { return this -> _type; };
void Token::toString() {
  cout << "类型是: " << this -> _type << "(" << Token::getTypeName(this -> _type) << ")" << " 值是: " << this -> _value << endl;
};

Token* Token::getVarOrKeyword(istream& is) {
  string str("");
  // 提取一个字符串
  while (is.peek() != EOF) {
    char c = is.peek();
    if (isalpha(c) || (c == '_')) {
      str += c;
      c = is.get();
    } else {
      break;
    }
  }

  if (str == "true" || str == "false") {
    /**
     * 避免产生临时对象而触发拷贝构造
     */
    // return Token(TokenType::BOOLEAN, str);
    return new Token(TokenType::BOOLEAN, str);
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
    // return Token(TokenType::KEYWORD, str);
      return new Token(TokenType::KEYWORD, str);
  };
  // return Token(TokenType::VARIABLE, str);
  return new Token(TokenType::VARIABLE, str);
};

Token* Token::getDouble(istream& is) {
  char d = is.peek(); // 先用 peek 传进来的不是数字相关的话 就让它保留在 stream 中
  if (isdigit(d) || d == '.' || d == '+' || d == '-') { // c >= '0' && c <= '9' ← 这么判断是不是数字也objk
    string str("");
    /**
     * 有几种错误的情况要抛出异常
     *  1. 小数点后面跟着小数点
     *  2. 小数点后面跟着数字但是数字后又有小数点
     *  3. 小数点后没跟着数字
     *  4. 正负号后边跟着非小数点或者数字
     *  5. 暂时没想到......
     */
    bool isFloat = false; // 设置一个初始值 用来标识该数字是否是小数
    char previousD; // 设置上一个字符
    while (true) {
      d = is.get();
      if (previousD == '.' && d == '.') Utils::panic("小数点后面跟着小数点");
      if (isdigit(previousD) && isFloat && d == '.') Utils::panic("小数点后面还有小数点");
      if (previousD == '.' && !isdigit(d)) Utils::panic("小数点后面没跟着数字");
      if ((previousD == '+' || previousD == '-') && !isdigit(d) && d != '.') Utils::panic("正负号后边没跟着小数点或者数字");

      if (d == '.' || d == '+' || d == '-' || isdigit(d)) {
        if ((d == '+' || d == '-') && isdigit(previousD)) {
          // 进到这儿说明出现了类似 666.6-1 这种情况
          is.putback(d); // 需要把特殊符号放回去
          // return Token(TokenType::INTEGER, str); // 然后直接返回
          return new Token(TokenType::INTEGER, str); // 然后直接返回
        }
        if (d == '.') isFloat = true;
        str += d;
        previousD = d;
        d = is.peek(); // 拿到下一个
      } else {
        // js 中可以不区分int或者float 但是这里可以简单区分一下
        is.putback(d);
        // if (isFloat) return Token(TokenType::DOUBLE, str);
        if (isFloat) return new Token(TokenType::DOUBLE, str);
        // return Token(TokenType::INTEGER, str);
        return new Token(TokenType::INTEGER, str);
      }
    }
  }

  // string errMsg("getDouble中传进来一个非number的字符 ");
  // string errD(d);
  // Utils::panic(errMsg + errD);
  Utils::panic("getDouble中传进来一个非number的字符 ");
}

Token* Token::getString(istream& is) {
  string str("");
  char quotationMarks = is.get(); // quotationMarks是引号的意思 应该是 " 或 ' 或 `
  str += quotationMarks;

  while (is.peek() != EOF) {
    char c = is.get();
    if (c == '\\') { cout << "nnnnn" << endl; }
    if (c == quotationMarks) {
      str += c;
      return new Token(TokenType::STRING, str);
      // return Token(TokenType::STRING, str);
    };
    str += c;
  }
  // 走到这里说明没有结束的引号 要抛出异常
  Utils::panic("获取字符串这块儿报错了");
}

Token* Token::getOperator(istream& is) {
  char c = is.get();
  string str("");
  str += c;
  if (c == '+') {
    if (is.peek() == '=') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "+=");
      return new Token(TokenType::OPERATOR, "+=");
    } else if (is.peek() == '+') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "++");
      return new Token(TokenType::OPERATOR, "++");
    } else {
      // c = is.get();
      // return Token(TokenType::OPERATOR, "+");
      return new Token(TokenType::OPERATOR, "+");
    }
  } else if (c == '-') {
    if (is.peek() == '=') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "-=");
      return new Token(TokenType::OPERATOR, "-=");
    } else if (is.peek() == '-') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "--");
      return new Token(TokenType::OPERATOR, "--");
    } else {
      // return Token(TokenType::OPERATOR, "-");
      return new Token(TokenType::OPERATOR, "-");
    }
  } else if (c == '*') {
    if (is.peek() == '=') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "*=");
      return new Token(TokenType::OPERATOR, "*=");
    } else if (is.peek() == '*') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "**"); // 取平方
      return new Token(TokenType::OPERATOR, "**"); // 取平方
    } else {
      // return Token(TokenType::OPERATOR, "*");
      return new Token(TokenType::OPERATOR, "*");
    }
  } else if (c == '/') {
    if (is.peek() == '=') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "/=");
      return new Token(TokenType::OPERATOR, "/=");
    } else {
      // return Token(TokenType::OPERATOR, "/");
      return new Token(TokenType::OPERATOR, "/");
    }
  } else if (c == '%') {
    if (is.peek() == '=') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "%=");
      return new Token(TokenType::OPERATOR, "%=");
    } else {
      // return Token(TokenType::OPERATOR, "%");
      return new Token(TokenType::OPERATOR, "%");
    }
  } else if (c == '~') {
    // return Token(TokenType::OPERATOR, "~");
    return new Token(TokenType::OPERATOR, "~");
  } else if (c == '|') {
    if (is.peek() == '|') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "||");
      return new Token(TokenType::OPERATOR, "||");
    }
    // return Token(TokenType::OPERATOR, "|"); 
    return new Token(TokenType::OPERATOR, "|");
  } else if (c == '&') {
    if (is.peek() == '&') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "&&");
      return new Token(TokenType::OPERATOR, "&&");
    }
    // return Token(TokenType::OPERATOR, "&"); 
    return new Token(TokenType::OPERATOR, "&");
  } else if (c == '!') {
    if (is.peek() == '=') {
      c = is.get();
      c = is.peek();
      if (c == '=') {
        // return Token(TokenType::OPERATOR, "!==");
        return new Token(TokenType::OPERATOR, "!==");
      }
      // return Token(TokenType::OPERATOR, "!=");
      return new Token(TokenType::OPERATOR, "!=");
    } else if (is.peek() == '!') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "!!");
      return new Token(TokenType::OPERATOR, "!!");
    } else {
      // return Token(TokenType::OPERATOR, "!");
      return new Token(TokenType::OPERATOR, "!");
    }
  } else if (c == '=') {
    if (is.peek() == '=') {
      c = is.get();
      c = is.peek();
      if (c == '=') {
        c = is.get();
        // return Token(TokenType::OPERATOR, "===");
        return new Token(TokenType::OPERATOR, "===");
      }
      // return Token(TokenType::OPERATOR, "==");
      return new Token(TokenType::OPERATOR, "==");
    }
    // return Token(TokenType::OPERATOR, "=");
    return new Token(TokenType::OPERATOR, "=");
  } else if (c == '>') {
    if (is.peek() == '=') {
      c = is.get();
      // return Token(TokenType::OPERATOR, ">=");
      return new  Token(TokenType::OPERATOR, ">=");
    }
    // return Token(TokenType::OPERATOR, ">");
    return new Token(TokenType::OPERATOR, ">");
  } else if (c == '<') {
    if (is.peek() == '=') {
      c = is.get();
      // return Token(TokenType::OPERATOR, "<=");
      return new Token(TokenType::OPERATOR, "<=");
    }
    // return Token(TokenType::OPERATOR, "<");
    return new Token(TokenType::OPERATOR, "<");
  } else if (c == '[') {
    // return Token(TokenType::OPERATOR, "[");
    return new Token(TokenType::OPERATOR, "[");
  } else if (c == ']') {
    // return Token(TokenType::OPERATOR, "]");
    return new Token(TokenType::OPERATOR, "]");
  } else if (c == '{') {
    // return Token(TokenType::OPERATOR, "{");
    return new Token(TokenType::OPERATOR, "{");
  } else if (c == '}') {
    // return Token(TokenType::OPERATOR, "}");
    return new Token(TokenType::OPERATOR, "}");
  } else if (c == '(') {
    // return Token(TokenType::OPERATOR, "(");
    return new Token(TokenType::OPERATOR, "(");
  } else if (c == ')') {
    // return Token(TokenType::OPERATOR, ")");
    return new Token(TokenType::OPERATOR, ")");
  } else if (c == ',') {
    // return Token(TokenType::OPERATOR, ",");
    return new Token(TokenType::OPERATOR, ",");
  } else if (c == ';') {
    // return Token(TokenType::OPERATOR, ";");
    return new Token(TokenType::OPERATOR, ";");
  }

  Utils::panic("获取Operator时候出错了 检查getOperator");
}
