#include "calculator.hpp"

#include <iostream>

using namespace s21;

/**
 * @brief Calculate expression for x value
 */
double Calculator::calculate(std::string expression, double x) {
  if (expression.empty()) {
    return 0;
  }
  std::vector<Token> tokens = parser.parseTokens(expression);
  if (tokens.empty()) {
    return 0.0;
  }
  tokens = parser.toPostfix(tokens, x);
  return (round(calculatePostfix(tokens) * 1000000) / 1000000);
}

/**
 * @brief Calculate from postfix tokens representation
 */
double Calculator::calculatePostfix(std::vector<Token> postfixTokens) {
  std::stack<double> stk;
  for (int i = 0; i < (int)postfixTokens.size(); i++) {
    if (postfixTokens[i].isNum())
      stk.push(postfixTokens[i].get<double>());
    else if (postfixTokens[i].getType() == FuncType::UNARY) {
      double val = stk.top();
      stk.pop();
      stk.push(calcUnary(postfixTokens[i].get<FuncCode>(), val));
    } else if (postfixTokens[i].getType() == FuncType::BINARY) {
      double first = stk.top();
      stk.pop();
      double second = stk.top();
      stk.pop();
      stk.push(calcBinary(postfixTokens[i].get<FuncCode>(), first, second));
    } else
      throw std::invalid_argument("Illegal token value. Can't calculate.");
  }
  if (stk.size() != 1)
    throw std::invalid_argument("Calculate error. Stack size non equal to 1");
  return fabs(stk.top()) < EPS ? 0 : stk.top();
}

/**
 * @brief Func for calculate binary operation
 */
double Calculator::calcBinary(FuncCode func, double first, double second) {
  switch (func) {
    case FuncCode::PLUS:
      return first + second;
    case FuncCode::MINUS:
      return second - first;
    case FuncCode::MULT:
      return first * second;
    case FuncCode::DIV:
      if (fabs(first) >= EPS) return second / first;
      throw std::invalid_argument("Invalid arguments for FuncCode DIV");
    case FuncCode::MOD:
      if (fabs(first) >= EPS) return fmod(second, first);
      throw std::invalid_argument("Invalid arguments for FuncCode MOD");
    case FuncCode::POW:
      return powl(second, first);
    default:
      throw std::invalid_argument(
          "Calculate binary operation error. Invalid Argument or FuncCode");
  }
}

/**
 * @brief Func for calculate binary operation
 */
double Calculator::calcUnary(FuncCode func, double val) {
  switch (func) {
    case FuncCode::SIN:
      return sin(val);
    case FuncCode::COS:
      return cos(val);
    case FuncCode::LN:
      if (val > EPS) return log(val);
      throw std::invalid_argument("Invalid argument for FuncCode LN");
    case FuncCode::LOG:
      if (val > EPS) return log10(val);
      throw std::invalid_argument("Invalid argument for FuncCode LOG");
    case FuncCode::SQRT:
      if (val >= 0) return sqrt(val);
      throw std::invalid_argument("Invalid argument for FuncCode SQRT");
    case FuncCode::ATAN:
      return atan(val);
    case FuncCode::ACOS:
      return acos(val);
    case FuncCode::ASIN:
      return asin(val);
    case FuncCode::TAN:
      if (fabs(cos(val))) return tan(val);
    default:
      throw std::invalid_argument(
          "Calculate unary operation error. Invalid argument or FuncCode");
  }
}

Calculator::Calculator(Parser parser) { this->parser = parser; }