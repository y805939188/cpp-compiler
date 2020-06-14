#include <iostream>
#include <deque>
#include <sstream>
#include <string>
#include <utils/utils.h>
#include "token.h"
#include "lexer.h"

using namespace std;

deque<D_Token> Lexer::analyse(istream& source) {
  deque<D_Token> tokenList;

  char c;
  char previousC;
  Token previdousTemporaryToken;
  while(true) {
    c = source.get();
    if (c == EOF) break;
    if (Utils::anyone(c, ' ', '\n', '\r')) continue;
    if (Utils::anyone(c, '"', '\'', '`')) {
      source.putback(c);
      D_Token t = Token::getString(source);
      previousC = c;
      continue;
    } else if (isdigit(c)) {
      source.putback(c);
      D_Token t = Token::getDouble(source);
      tokenList.push_back(t);
      continue;
    } else if (isalpha(c)) { // isalpha 判断是否是字母
      source.putback(c);
      D_Token t = Token::getVarOrKeyword(source);
      tokenList.push_back(t);
      previousC = c;
      continue;
    } else {
      /**
       * TODO:
       *  这块处理操作符和数字的时候写的有点复杂了
       *  计划重构
       * 
       *  考虑是否可以使用
       *    1 先处理操作符
       *    2 然后发现后面是个数字的话 就 throw 出来
       *    3 之后再 catch 中处理下一步逻辑
       */


      /**
       * 对于数字来讲，情况比较复杂 因为 正负号和小数点开头的都能是数字
       */
      if (ispunct(c)) { // 如果是非数字或者字符的符号的话
        // cout << "尽到了操作符组, 当前的操作符是 " << c;
        if (Utils::anyone(c, '+', '-', '.')) {
          // 如果是这仨的要特殊处理 因为他们可能是 Number
          char temporary;
          bool hasSpace = false;
          while (true) {
            // 把这个正负号或者小数点后面的空格们拿掉
            temporary = source.peek();
            if (temporary == EOF) Utils::panic("这种情况可能是代码写的有问题, 因为流被消费完了");
            if (temporary != ' ') {
              if (Utils::anyone(temporary, '+', '-', '*', '/', '&', '^', '%', '$', '#', '@', '!', '~', '|', '?', '>', '<', ';', ',', ':', '{', '}') &&  hasSpace) {
                // 进入这里说明+ - . 后面有空格并且跟着一个操作符
                // 这种情况是不允许的 需要报错
                Utils::panic("+/-/. 等操作符后面可以有空格但不能空格之后还接操作符");
              }
              break;
            }; // 如果下一个不是空格的话 就停止这个while循环
            if (temporary == ' ') {
              hasSpace = true;
              if (c == '.') {
                // 如果 c 是小数点的话后面还跟着空格那就直接报错
                Utils::panic("小数点后面不能跟着空格");
              }
              temporary = source.get();
              continue;
            }
          }
          /**
           * var x = +6
           * var x = -  8
           * x + 6
           * x + -6
           * x - .1
           * 
           */
          // 如果走到这一步 说明temporary肯定不是空格了
          // 可能是个变量名 数字 字符串 或者 操作符
          // 由于 js 中对于正负号和小数点的运算都不一样 所以要分别判断
          if (c == '+') {
            D_Token prev = tokenList[tokenList.size() - 1];
            if (isdigit(temporary) && !(*prev).isNumber()) {
              // 如果是个数字 那就是类似 +6 酱婶儿的
              // 并且前面的那个 Token 不能是数字 如果是数字的话应该被翻译为 x + y;
              D_Token temporaryToken = Token::getDouble(source);
              string temporaryStr("+");
              temporaryStr += (*temporaryToken).getValue();
              D_Token t = D_Token(new Token((*temporaryToken).getTokenType(), temporaryStr));
              tokenList.push_back(t);
              continue;
            } else {
              /**
               * 这里不能直接putback
               * 因为上面为了把空格干掉 可能 get 了好几次
               * 所以这里 putback 的话 可能会和上一次的不匹配
               */
              /**
               * temporary == '[' 或 引号 是两种特殊情况
               * 一般情况下 + 后面跟着操作符 如果中间有空格就应该报错
               * 但是对于 x + [y] 这种情况 有些语言比如python或者js可以处理
               * 如: 1 + [1,2,3] => "11,2,3"
               */
              if (isalpha(temporary) || isdigit(temporary) || Utils::anyone(temporary, '\'', '"', '`', '[')) {
                string temporaryStr("+");
                D_Token t = D_Token(new Token(TokenType::OPERATOR, temporaryStr));
                tokenList.push_back(t);
                continue;
              } else {
                // 如果能进入这里 说明 putback 肯定不会出错
                source.putback(c);
                D_Token t = Token::getOperator(source);
                tokenList.push_back(t);
                continue;
              }
            }
          } else if (c == '-') {
            D_Token prev = tokenList[tokenList.size() - 1];
            if (isdigit(temporary) && !(*prev).isNumber()) {
              // 如果是个数字 那就是类似 -7 酱婶儿的
              D_Token temporaryToken = Token::getDouble(source);
              string temporaryStr("-");
              temporaryStr += (*temporaryToken).getValue();
              D_Token t = D_Token(new Token((*temporaryToken).getTokenType(), temporaryStr));
              tokenList.push_back(t);
              continue;
            } else {
              // x - [] => NaN
              if (isalpha(temporary) || isdigit(temporary) || Utils::anyone(temporary, '\'', '"', '`', '[')) {
                string temporaryStr("-");
                D_Token t = D_Token(new Token(TokenType::OPERATOR, temporaryStr));
                tokenList.push_back(t);
                continue;
              } else {
                // 如果能进入这里 说明 putback 肯定不会出错
                source.putback(c);
                D_Token t = Token::getOperator(source);
                tokenList.push_back(t);
                continue;
              }
            }
          } else if (c == '.') {
            if (isdigit(temporary)) {
              // 如果是个数字 那就是类似 .8 酱婶儿的
              D_Token t = Token::getDouble(source);
              tokenList.push_back(t);
              continue;
            } else {
              // 其他情况可以直接报错
              Utils::panic("小数点后面不能瞎TM写, 只能写数字");
            }
          }
        } else {
          // 走到这里可能是一些特殊符号或者操作符
          source.putback(c); // 把操作符给放回去
          D_Token t = Token::getOperator(source);
          tokenList.push_back(t);
          continue;
        }
      }
    }
    // 走到这里说明没有匹配到上面任何一个 就要报错了
    Utils::panic("在提取 Token 的过程中没有匹配到做任何一种");
  }

  return tokenList;
}
