#include <iostream>
#include <deque>
#include <sstream>
#include <string>
#include "token.h"

using namespace std;

// class Lexer {
//   public:
//     deque<Token> analyse(istream source) {
//       // return ;
      
//     }
// };

int main () {
  // istream::peek 和 cin.peek 基本上就是一个东西 istream 是 cin的别名
  int a;
  int sum;
       
  while(cin >> a) {
      sum += a;
      while(cin.peek() == ' ') {
        cin.get();
      };
      if(cin.peek() == '\n') break;
  }
      
  cout<<"结果是："<<sum<<endl;
  return 0;
}

