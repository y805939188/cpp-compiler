#include <iostream>
#include <fstream>
#include <sstream>
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

  // std::ifstream* myStream;
  // std::istream* myOtherStream = static_cast<std::istream*>(myStream);
  // myOtherStream = myStream;

  /**
   * 文件流可以用以下方式转换为字符流
   * 
   */
  // std::istream* istreamObj = static_cast<std::istream*>(&fs);
  // cout << static_cast<char>((*istreamObj).get()) << endl;
  // cout << static_cast<char>((*istreamObj).get()) << endl;

  // istream* ss = static_cast< istream* >(fs);

  // cout << ss.peek() << endl;

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
