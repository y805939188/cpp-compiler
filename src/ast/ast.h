#include <iostream>
#include <string>
#include <deque>
#include <token.h>

class Record {
  int line = -1;
  int column = -1;
  public:
    Record(int line, int column) : line(line), column(column) {};
    virtual void toString() { cout << "第 " << this -> line << " 行," << "第 " << this -> column << " 列 发生了错误" << endl; };
};

/**
 * 抽象语法树大致可以分为三类
 *  1. 表达式(Expression)
 *     表达式可以是语句 比如 a = 1 + 1 赋值表达式
 *     同时也是一段可执行的语句
 *        BoolExpr 布尔表达式
 *        FunCallExpr 函数调用表达式
 *        AssignExpr 赋值表达式
 *        NullExpr 空值表达式
 *        UndefinedExpr undefined表达式
 *        NanExpr 非数表达式
 *        IntExpr 整形表达式
 *        DoubleExpr 浮点表达式
 *        NumberExpr 数字表达式 综合int和double
 *        StringExpr 字符串表达式
 *        ArrayExpr 数组表达式
 *        ObjectExpr 对象表达式
 *        Symbol 符号表达式
 *        BinaryExpr 二元运算表达式
 *  2. 语句(Statement)
 *     语句不能是表达式 表达式表示了一句“命令”
 *     告诉解释器要执行一条“命令”
 *     比如 a = 1 + 1 告诉解释器执行一条加法命令
 *     但是 1 + 1 只是单纯的得到一个值 并没有执行一个命令的“被动”意思
 *         AssignStmt 赋值语句
 *         FunctionStmt 函数定义语句
 *         BlockStmt 块儿语句
 *         Declare 声明语句
 *         BreakStmt break语句
 *         ContinueStmt continue语句
 *         ExpressionStmt 表达式语句
 *         ReturnStmt 返回语句
 *         IfStmt if语句
 *         SwitchStmt switch语句
 *         ForStmt for循环语句
 *         WhileStmt while循环语句
 *         DowhileStmt do-whilt循环语句
 *         WithStmt with语句
 *         evalStmt eval语句
 *  3. 值/声明
 *     比如const或者let或者var或一些常量值
 * 
 */

class ASTNode {
  protected:
    ASTNode _parent;
    deque<ASTNode*> _children;
    Token lexeme;
  public:
    ASTNode(ASTNode& parent);
};

