#ifndef TOKEN_H
#define TOKEN_H

#include "base.hpp"

namespace s21 {
class Token {
 public:
  Token(FuncCode func, FuncType type);
  Token(double num);
  bool isNum() const;
  int getPriority();
  FuncType getType();
  template <typename T>
  T get() {
    if constexpr (std::is_same<T, FuncCode>::value) {
      return func;
    } else if constexpr (std::is_same<T, double>::value) {
      return numValue;
    }
  }

 private:
  Token(FuncCode func, double num, int priority, FuncType type);
  double numValue;
  int priority;
  FuncCode func;
  FuncType type;
};
}  // namespace s21

#endif  // TOKEN_H