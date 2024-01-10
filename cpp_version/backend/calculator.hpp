#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "base.hpp"
#include "parser.hpp"
#include "token.hpp"

namespace s21 {
class Calculator {
 public:
  Calculator(s21::Parser parser);
  double calculate(const std::string expression, const double x);

 private:
  double calculatePostfix(std::vector<Token> postfixTokens);
  double calcUnary(FuncCode func, double val);
  double calcBinary(FuncCode func, double first, double second);
  Parser parser;
};
}  // namespace s21

#endif  // CALCULATOR_H