#include <iostream>
#include <fstream>
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
  Token token = Token::makeVarOrKeyword(fs);
  token.toString();
  // Token to(TokenType::BOOLEAN, "true");
  // to.toString();

  fs.close();
  return 0;
}
