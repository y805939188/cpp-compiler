#include <iostream>
#include <fstream>
#include <lexer/token.h>
using namespace std;

/**
 * 
 */

int main(void) {
  cout << "ding-test" << endl;
  ifstream fs;
  fs.open("./ding.test.txt");
  cout << "hahahah" << endl;
  Token::makeVarOrKeyword(fs);
  // Token to(TokenType::BOOLEAN, "true");
  // to.toString();
  // Token::hehe();

  

  fs.close();
  // hello::say_hello();
  // cout << "由于main.cpp链接了say-hello 所以这里面也可以用这个宏" << SAY_HELLO_VERSION << endl;
  return 0;
}
