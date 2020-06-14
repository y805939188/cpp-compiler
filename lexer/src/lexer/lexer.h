#include <iostream>
#include <istream>
#include <deque>
#include "token.h"

using namespace std;

class Lexer {
  public:
    static deque<shared_ptr<Token> > analyse(istream& source);
};
