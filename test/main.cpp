#include <iostream>
#include <fstream>
#include <sstream>
#include <lexer/token.h>
using namespace std;

/**
 * 
 */

int main(void) {
  ifstream fs_makeVarOrKeyword;

  /**
   * 这里open 会直接在根目录下找 不会找相对路径
   * 有待改善
   */
  fs_makeVarOrKeyword.open("./test/makeVarOrKeyword.test.txt");

  /**
   * 文件流可以用以下方式转换为字符流
   * 
   */
  // std::istream* istreamObj = static_cast<std::istream*>(&fs);
  // cout << static_cast<char>((*istreamObj).get()) << endl;
  // cout << static_cast<char>((*istreamObj).get()) << endl;
  // istream* ss = static_cast< istream* >(fs);
  // cout << ss.peek() << endl;

  Token token = Token::makeVarOrKeyword(fs_makeVarOrKeyword);
  token.toString();

  ifstream fs_makeString;
  fs_makeString.open("./test/makeString.test.txt");
  Token token2 = Token::makeString(fs_makeString);
  token2.toString();
  // cout << token2.getValue() << endl;


  fs_makeVarOrKeyword.close();
  fs_makeString.close();
  return 0;
}
