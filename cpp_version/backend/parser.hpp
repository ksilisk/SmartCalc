#ifndef PARSER_H
#define PARSER_H

#include "base.hpp"
#include "token.hpp"

namespace s21 {
class Parser {
 public:
  std::vector<Token> parseTokens(const std::string equation);
  std::vector<Token> toPostfix(const std::vector<Token> parsedTokens, double x);
  static int priority(const FuncCode func);
  static bool isUnary(const Token t);
  static bool isBinary(const Token t);

 private:
  bool checkMinus(std::vector<Token> tokens);
  std::string parseDouble(const std::string string, int startIndex);
  Token parseToken(const std::string string, int startIndex);
  int shift(const Token token);
  int priority(const Token token);
  bool checkBrackets(const std::vector<Token> tokens);
};
}  // namespace s21

#endif  // PARSER_H