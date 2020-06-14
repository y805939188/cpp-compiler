/**
 * 该文件用来随便测试点东西
 * 可以直接用vscode的task执行
 */

#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <deque>
#include <exception>

using namespace std;

class Test {
  public:
    string _value;
    Test(string value);
    Test(const Test & t);
};

Test::Test(string value):_value(value){
  cout << " 这里的value是 " << value << endl;
};

Test::Test(const Test& t): _value(t._value) {
  cout << "发生了拷贝构造  " << t._value << endl;
};

Test& test_func() {
  string str("test test test test test");
  Test t(str);
  return t;
}

bool is_inzyzifu(const string &str) {
static string caps("//");
string::size_type pos = 0;
pos = str.find_first_of(caps, pos);
if (pos != string::npos)
{
return true;
}
else
{
return false;
}
}

// class myException:public exception  
// {  
// public:  
//    myException():exception("ERROR! Don't divide a number by integer zero.n")  
//     {  
//     }  
// };  

[[noreturn]] void panic(char const* const format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

class MyTest {
  string str;
  public:
    MyTest(string s): str(s) {};
    static MyTest* setStr(string str) { return (new MyTest(str)); }
    void getStr() { cout << "这里的str是" << this -> str << endl; }
};
deque<MyTest*> test_func2() {
  deque<MyTest*> myList;
  for (unsigned i = 0; i < 10; i++) {
    string tempStr("ding test");
    MyTest* m = MyTest::setStr(tempStr);
    myList.push_back(m);
  }
  return myList;
}
int main () {
  deque<MyTest*> testList = test_func2();
  deque<MyTest*>::iterator iter;
  cout << "一共有 " << testList.size() << " 个" << endl;
  for (MyTest* test: testList) {
    (*test).getStr();
  }
  for (MyTest* test: testList) {
    delete test;
  }

  // cout << isdigit('0') << endl;
  // cout << isalpha('a') << endl;
  // cout << isalpha('b') << endl;
  // cout << isalpha('C') << endl;
  // cout << isalpha('6') << endl;

  // deque<int> test;
  // int a;
  // test.push_back(a = 888);
  // cout << a << endl;
  // cout << test[0] << endl;

  // cout << ispunct('a') << endl;
  // cout << ispunct('0') << endl;
  // cout << ispunct('*') << endl;
  // cout << ispunct('\\') << endl;
  // cout << ispunct('(') << endl;
  // cout << ispunct('$') << endl;
  // cout << ispunct('"') << endl;
  // cout << ispunct('+') << endl;

  // istringstream ding("ding");
  // char c = ding.get();
  // ding.putback('q');
  // cout << static_cast<char>(ding.peek()) << endl;

  // cout << '+' + "ddd" << endl;

  // instr

  

  // istringstream str("+       88");
  // char f = str.get();
  // char a;
  // string test("");
  // test += f;
  // while(a = str.peek()) {
  //   if (a == EOF) break;
  //   if (isdigit(a)) { test += a; break; };
  //   if (a == ' ') {
  //     a = str.get();
  //     continue;
  //   };
  //   test += a;
  // }
  // cout << test << endl;

  // cout << EOF << endl;

  // panic("asdfasdfasdfasdfasdf");
  // cout << is_inzyzifu("ding ding \" ding") << endl;
  // cout << is_inzyzifu("ding ding \' ding") << endl;
  // cout << is_inzyzifu("ding ding  ding") << endl;
  // Test ty = test_func();
  // cout << ty._value << endl; // test test test test test
  // Test ty2 = ty; // 会发生拷贝构造
  // Test ty3(ty); // 会发生拷贝构造
  // Test ty4 = test_func(); // 不会发生拷贝构造
  // Test ty5;
  // ty5 = ty; // 不会发生拷贝构造 因为这个是单纯的赋值操作 是函数重载在起作用
  // cout << ty._value << endl;
  // cout << test_func()._value << endl;

  // istream::peek 和 cin.peek 基本上就是一个东西 istream 是 cin的别名
  // ifstream readFile("ding.txt");
  // ifstream fs;
  // string contents;

  // fs.open("./ding.txt");

  // // cout << (char)fs.get() << endl; // 编译器不会检查C风格的转换 可能会报错
  // cout << static_cast<char>(fs.get()) << endl; // 编译器会检查C++风格的转换
  // cout << static_cast<char>(fs.get()) << endl;
  // cout << static_cast<char>(fs.get()) << endl;
  // cout << static_cast<char>(fs.get()) << endl;
  // cout << static_cast<char>(fs.peek()) << endl;
  // cout << static_cast<char>(fs.peek()) << endl;
  // cout << static_cast<char>(fs.peek()) << endl;
  // cout << static_cast<char>(fs.peek()) << endl;
  // cout << static_cast<char>(fs.get()) << endl;
  
  // char test = fs.get();
  // cout << test << endl; // 这个和下面的是一样的
  // fs.putback(test);
  // cout << static_cast<char>(fs.get()) << endl; // 和上面的test是一样的

  // fs.close();

  // enum Token {
  //   VAR = 0,
  //   IF,
  //   ELSE,
  //   FOR,
  //   WHILE,
  //   BREAK,
  //   FUNC,
  //   RETURN,
  //   CONTINUE,
  //   NONE,
  // };
  // const map<string, Token> keywords(
  //   {
  //     {"var", VAR},
  //     {"if", IF},
  //     {"else", ELSE},
  //     {"while", WHILE},
  //     {"null", NONE},
  //     {"for", FOR},
  //     {"func", FUNC},
  //     {"return", RETURN},
  //     {"break", BREAK},
  //     {"continue", CONTINUE}
  //   }
  // );

  // map<string, Token>::const_iterator result = keywords.find("if");
  // if (result != keywords.end()) {
  //   cout << "有result" << " " << result -> first << endl;
  //   cout << "有result" << " " << result -> second << endl;
  // }

  // ifstream fs;
  // string str("ding1");
  // // cout << static_cast<char>((*istreamObj).get()) << endl;
  // // istream* ss = static_cast< istream* >(fs);
  // ifstream fs = static_cast< ifstream >(str);
  // ifstream fs2;
  // // str >> fs2;
  // fs2 << str;


  return 0;
}

