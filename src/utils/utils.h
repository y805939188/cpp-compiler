#include <iostream>

using namespace std;

namespace Utils {
  void panic(char const* const format, ...);

  template <typename T, typename... K>
  inline bool anyone(T t, K... args) {
    return ((args == t) || ...); // 折叠表达式
  }
}
