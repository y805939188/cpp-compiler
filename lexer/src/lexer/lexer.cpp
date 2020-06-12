#include <iostream>
#include <deque>
#include <sstream>
#include <string>
#include <utils/utils.h>
#include "token.h"
#include "lexer.h"

using namespace std;

deque<Token*> Lexer::analyse(istream& source) {
  deque<Token*> tokensList;

  // char t = source.get();
  // source.putback(t);
  // cout << static_cast<char>(source.peek()) << endl; 
  // return tokensList;
  char c;
  char previousC;
  Token previdousTemporaryToken;
  while(true) {
    c = source.get();
    // cout << "这里跌字符是哈哈哈哈" << static_cast<char>(c) << endl;
    if (c == EOF) {
      // cout << "进入了这里可以return了" << endl;
      break;
    };
    if (Utils::anyone(c, ' ', '\n', '\r')) continue;
    if (Utils::anyone(c, '"', '\'', '`')) {
      // tokensList.push_back(&(previdousTemporaryToken = Token::getString(source)));
      // cout << "进入了拿字符串的逻辑中 " << c << endl;
      source.putback(c);
      // cout << source.peek() << endl;
      Token t = Token::getString(source);
      tokensList.push_back(&t);
      previousC = c;
      t.toString();
      continue;
    } else if (isdigit(c)) {
      // cout << "尽到了数字组中, 这里的数字第一个字符是 " << c << endl;
      source.putback(c);
      // tokensList.push_back(&(previdousTemporaryToken = Token::getDouble(source)));
      Token t = Token::getDouble(source);
      tokensList.push_back(&t);
      previousC = c;
      // cout << "下一个字符是 " << static_cast<char>(source.peek()) << endl;
      t.toString();
      continue;
    } else if (isalpha(c)) { // isalpha 判断是否是字母
      // cout << "尽到了字母组, 当前字母是 " << c << endl;
      source.putback(c);
      // tokensList.push_back(&(previdousTemporaryToken = Token::getVarOrKeyword(source)));
      Token t = Token::getVarOrKeyword(source);
      tokensList.push_back(&t);
      // cout << "下一个符号是 " << static_cast<char>(source.peek()) << endl;
      previousC = c;
      t.toString();
      continue;
    } else {
      /**
       * 对于数字来讲，情况比较复杂 因为 正负号和小数点开头的都能是数字
       */
      if (ispunct(c)) { // 如果是非数字或者字符的符号的话
        // cout << "尽到了操作符组, 当前的操作符是 " << c;
        if (Utils::anyone(c, '+', '-', '.')) {
          // 如果是这仨的要特殊处理 因为他们可能是 Number
          // cout << "进到了 + - . 组中, 当前的符号是 " << c << endl;
          char temporary;
          // cout << "temporary的值是 " << temporary << endl;
          while (true) {
            // 把这个正负号或者小数点后面的空格们拿掉
            temporary = source.peek();
            // cout << "这里下一个temp是  " << temporary << endl;
            if (temporary == EOF) Utils::panic("这种情况可能是代码写的有问题, 因为流被消费完了");
            if (temporary != ' ') break; // 如果下一个不是空格的话 就停止这个while循环
            if (temporary == ' ') {
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
            // cout << "尽到了字符组的 + 组中, 上一个Token的Type是 " << previdousTemporaryToken.getTokenType() << endl;
            Token* prev = tokensList[tokensList.size() - 1];
            // cout << "尽到了字符组中的 + 组中 上一个Token的tyoe是 " << (*prev).getValue() << endl;
            if (isdigit(temporary) && !(*prev).isNumber()) {
              // 如果是个数字 那就是类似 +6 酱婶儿的
              // 并且前面的那个 Token 不能是数字 如果是数字的话应该被翻译为 x + y
              // source.putback(c); // 如果temporary是数字的话就把 + 号放回去
              // tokensList.push_back(&(previdousTemporaryToken = Token::getDouble(source)));
              Token temporaryToken = Token::getDouble(source);
              string temporaryStr("+");
              temporaryStr += temporaryToken.getValue();
              // TokenType temporaryType = temporaryToken.getTokenType();
              Token t(temporaryToken.getTokenType(), temporaryStr);
              // cout << "这里拿到的number是哈哈哈哈  " << t.getValue() << endl;
              tokensList.push_back(&t);
              t.toString();
              continue;
            }
            // else if (isalpha(temporary)) {
            //   // 如果是个字母的话 可能是个变量或关键字
            //   source.putback(c); // 这种情况下就把加号放进去就行了
            //   tokensList.push_back(previdousTemporaryToken = Token::getOperator(source));
            //   continue;
            // } else if (Utils::anyone(temporary, '"', '\'', '`')) {
            //   // 如果是个引号的话 可能是加了一个字符串
            //   source.putback(c); // 这种情况下也把加号放进去就行了
            //   tokensList.push_back(previdousTemporaryToken = Token::getOperator(source));
            //   continue;
            // }
            else {
              // 其他情况就是加个操作符了
              // cout << "在 + 组中 进入了其他操作符组 " << c << endl;
              // cout << "99988877  " << static_cast<char>(source.peek()) << endl;
              // cout << "这里的temporary是   " << temporary << endl;
              // source.putback('o'); // 这种情况下也把加号放进去就行了
  
              // tokensList.push_back(&(previdousTemporaryToken = Token::getOperator(source)));
              // cout << "下一个是 " << source.peek() << endl;
              // cout << "下一个是 " << source.peek() << endl;
              // Token t = Token::getOperator(source);

              /**
               * 这里不能直接putback
               * 因为上面为了把空格干掉 可能 get 了好几次
               * 所以这里 putback 的话 可能会和上一次的不匹配
               */

              // Token temporaryToken = Token::getOperator(source);

              // Token t = Token::getOperator(source);

              // string temporaryStr("+");

              // cout << "这里的临死时候死你 " << temporaryToken.getValue() << endl;

              // temporaryStr += temporaryToken.getValue();

              // source.putback('+');

              // cout << "kkkkkkkkkk   " << source.peek() << endl;



              Token t(TokenType::OPERATOR, "+");
              tokensList.push_back(&t);
              // cout << "下一个字符是 " << static_cast<char>(source.peek()) << endl;
              t.toString();
              continue;
            }
          } else if (c == '-') {
            // cout << "尽到了字符组的 - 组中, 上一个Token的Type是 " << previdousTemporaryToken.getTokenType() << endl;
            Token* prev = tokensList[tokensList.size() - 1];
            if (isdigit(temporary) && !(*prev).isNumber()) {
              // 如果是个数字 那就是类似 -7 酱婶儿的
              // source.putback(c); // 如果temporary是数字的话就把 - 号放回去
              // tokensList.push_back(&(previdousTemporaryToken = Token::getDouble(source)));
              // Token t = Token::getDouble(source);
              
              Token temporaryToken = Token::getDouble(source);
              string temporaryStr("-");
              temporaryStr += temporaryToken.getValue();

              Token t(TokenType::OPERATOR, temporaryStr);

              // cout << "这里拿到的减号的值是 " << t.getValue() << endl;
              
              tokensList.push_back(&t);
              t.toString();
              continue;
            } else {
              // 其他情况 就是以上注释掉的那些情况
              // source.putback(c); // 这种情况下也把减号放进去就行了
              // tokensList.push_back(&(previdousTemporaryToken = Token::getOperator(source)));
              // Token t = Token::getOperator(source);
              string temporaryStr("-");
              Token t(TokenType::OPERATOR, temporaryStr);
              tokensList.push_back(&t);
              t.toString();
              continue;
            }
          } else if (c == '.') {
            if (isdigit(temporary)) {
              // 如果是个数字 那就是类似 .8 酱婶儿的
              // source.putback(c); // 如果temporary是数字的话就把 - 号放回去
              // tokensList.push_back(&(previdousTemporaryToken = Token::getDouble(source)));
              Token t = Token::getDouble(source);
              tokensList.push_back(&t);
              t.toString();
              continue;
            } else {
              // 其他情况可以直接报错
              Utils::panic("小数点后面不能瞎TM写, 只能写数字");
            }
          }
        } else {
          // 走到这里可能是一些特殊符号或者操作符
          // cout << "进入了其他操作符组, 当前符号是 " << c << endl;
          source.putback(c); // 把操作符给放回去
          // cout << static_cast<char>(source.peek()) << endl;
          // previdousTemporaryToken = Token::getOperator(source);
          Token t = Token::getOperator(source);
          tokensList.push_back(&t);
          // cout << "下一个字符是 " << static_cast<char>(source.peek()) << endl;
          t.toString();
          continue;
        }
      }
    }
    // 走到这里说明没有匹配到上面任何一个 就要报错了
    Utils::panic("在提取 Token 的过程中没有匹配到做任何一种");
  }

    // deque<Token>::iterator (iter*);
    cout << "一共有 " << tokensList.size() << " 个 Token" << endl;
    // for (iter = tokensList.begin(); iter != *tokensList.end(); iter++) {
    //   (*iter).toString();
    // }
    // for (Token* token: tokensList) {
    //   (*token).toString();
    // }
    // (*tokensList[0]).toString();
  return tokensList;
}

