#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main () {
  // istream::peek 和 cin.peek 基本上就是一个东西 istream 是 cin的别名
  // ifstream readFile("ding.txt");
  ifstream fs;
  string contents;

  // fs.open("./ding.txt");

  // // cout << (char)fs.get() << endl; // 编译器不会检查C风格的转换 可能会报错
  // cout << static_cast<char>(fs.get()) << endl; // 编译器会检查C++风格的转换
  // cout << static_cast<char>(fs.get()) << endl;
  // cout << static_cast<char>(fs.get()) << endl;
  // cout << static_cast<char>(fs.get()) << endl;
  // cout << static_cast<char>(fs.peek()) << endl;
  // cout << static_cast<char>(fs.peek()) << endl;
  // cout << static_cast<char>(fs.peek()) << endl;
  // cout << static_cast<char>(fs.peek()) << endl;
  // cout << static_cast<char>(fs.get()) << endl;
  
  // char test = fs.get();
  // cout << test << endl; // 这个和下面的是一样的
  // fs.putback(test);
  // cout << static_cast<char>(fs.get()) << endl; // 和上面的test是一样的

  fs.close();

  enum Token {
    VAR = 0,
    IF,
    ELSE,
    FOR,
    WHILE,
    BREAK,
    FUNC,
    RETURN,
    CONTINUE,
    NONE,
  };
  const map<string, Token> keywords(
    {
      {"var", VAR},
      {"if", IF},
      {"else", ELSE},
      {"while", WHILE},
      {"null", NONE},
      {"for", FOR},
      {"func", FUNC},
      {"return", RETURN},
      {"break", BREAK},
      {"continue", CONTINUE}
    }
  );

  map<string, Token>::const_iterator result = keywords.find("if");
  if (result != keywords.end()) {
    cout << "有result" << " " << result -> first << endl;
    cout << "有result" << " " << result -> second << endl;
  }





  return 0;
}

