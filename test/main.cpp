#include <iostream>
#include <fstream>
#include <sstream>
#include <lexer/token.h>
#include <lexer/lexer.h>
using namespace std;

/**
 * 
 */

int main(void) {
  ifstream fs_getVarOrKeyword;

  /**
   * 这里open 会直接在根目录下找 不会找相对路径
   * 有待改善
   */
  fs_getVarOrKeyword.open("./test/getVarOrKeyword.test.txt");

  /**
   * 文件流可以用以下方式转换为字符流
   * 
   */
  // std::istream* istreamObj = static_cast<std::istream*>(&fs);
  // cout << static_cast<char>((*istreamObj).get()) << endl;
  // cout << static_cast<char>((*istreamObj).get()) << endl;
  // istream* ss = static_cast< istream* >(fs);
  // cout << ss.peek() << endl;
  // istream

  // Token token = Token::getVarOrKeyword(fs_getVarOrKeyword);
  // token.toString();

  // ifstream fs_getString;
  // fs_getString.open("./test/getString.test.txt");
  // Token token2 = Token::getString(fs_getString);
  // token2.toString();
  // cout << token2.getValue() << endl;

  // string str1("ding1");
  // istringstream is1(str1);
  // Token token1 = Token::getVarOrKeyword(is1);
  // token1.toString();

  // string str2("true");
  // istringstream is2(str2);
  // Token token2 = Token::getVarOrKeyword(is2);
  // token2.toString();


  // string str3("\"ding1\"");
  // istringstream is3(str3);
  // Token token3 = Token::getString(is3);
  // token3.toString();

  // /**
  //  * TODO:
  //  *  处理转义字符
  //  */
  // // string str4("\"ding2 \' \" ding3\"");
  // // istringstream is4(str4);
  // // Token token4 = Token::getString(is4);
  // // token4.toString();

  // string str5("+= ding1");
  // istringstream is5(str5);
  // Token token5 = Token::getOperator(is5);
  // token5.toString();

  // string str6("%= ding1");
  // istringstream is6(str6);
  // Token token6 = Token::getOperator(is6);
  // token6.toString();

  // string str7("-- ding1");
  // istringstream is7(str7);
  // Token token7 = Token::getOperator(is7);
  // token7.toString();


  // string str8("!== ding1");
  // istringstream is8(str8);
  // Token token8 = Token::getOperator(is8);
  // token8.toString();

  // string str9("!= ding1");
  // istringstream is9(str9);
  // Token token9 = Token::getOperator(is9);
  // token9.toString();

  // string str10("=== ding1");
  // istringstream is10(str10);
  // Token token10 = Token::getOperator(is10);
  // token10.toString();

  // // string str11("ding");
  // // istringstream is11(str11);
  // // Token token11 = Token::getDouble(is11);
  // // token11.toString();

  // string str12[] = {
  //   "+66 ding",
  //   "-88.888 ding2",
  //   "777 ding3",
  //   "666",
  //   "999.9",
  //   ".15926",
  //   ".15926 ding",
  //   "+.99887 ding",
  //   "+98876*654321"
  // };
  // for (string str: str12) {
  //   istringstream is12(str);
  //   // cout << "这里的字符串是" << str << endl;
  //   Token token12 = Token::getDouble(is12);
  //   token12.toString();
  // }



  /**
   * 
   * Lexer 词法分析器测试
   * 
   */

  /**
   * TODO:
   *  1. 有些空格的情况需要处理
   *  2. 怎么把Token往tokensList数组中放
   */
  string str13("( a + b ) * [ 666.6 - 1 ] === -7 + `ding2` - [1,2] || 8 + 9 - 'ding ye niubi' * ding / liu % wang  + [1,2 ,4, 6, 'd' ] ");
  istringstream is12(str13);
  Lexer::analyse(is12);

  cout << "----------------------------------------" << endl;


  ifstream fs_getfunc;
  fs_getfunc.open("./test/lexer.test.txt");
  Lexer::analyse(fs_getfunc);

  /**
   * TODO:
   *  在读到 + 号的时候 需要特殊处理
   *  读到+号时会先判断是不是数字
   *  但当为 += 的时候会有问题
   */

  // fs_getVarOrKeyword.close();
  // fs_getString.close();
  return 0;
}
