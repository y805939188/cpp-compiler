#include <iostream>
#include <fstream>
// #include <sstream>
#include <lexer/token.h>
using namespace std;

/**
 * 
 */

int main(void) {
  ifstream fs;

  /**
   * 这里open 会直接在根目录下找 不会找相对路径
   * 有待改善
   */
  fs.open("./ding.test.txt");
  // string str("ding1");
  // Token token = Token::makeTest(fs, str);
  // token.toString();

  // Token token = Token::makeVarOrKeyword(fs);
  // token.toString();
  // string str("true");
  // Token to(TokenType::BOOLEAN, str);
  // to.toString();
  // ostringstream os;
  // const string str("\"这里是字符串\"");
  // os << str;
  
  Token token2 = Token::makeString(fs);
  token2.toString();

  fs.close();
  return 0;
}
