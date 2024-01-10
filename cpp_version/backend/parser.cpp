#include "parser.hpp"

#include <iostream>
using namespace s21;

/**
 * @brief Func for parse token from string equation
 */
std::vector<Token> Parser::parseTokens(const std::string equation) {
  std::vector<Token> tokens;
  int ind = 0;
  while (ind < (int)equation.size()) {
    if (equation[ind] == ' ')
      ind++;
    else if (equation[ind] >= '0' && equation[ind] <= '9') {
      std::string doubleStr = parseDouble(equation, ind);
      tokens.push_back(Token(std::stod(doubleStr)));
      ind += doubleStr.size();
    } else {
      if (equation[ind] == (char)FuncCode::MINUS && checkMinus(tokens)) {
        tokens.push_back(Token(0.0));
      }
      Token token = parseToken(equation, ind);
      tokens.push_back(token);
      ind += shift(token);
    }
  }
  if (!checkBrackets(tokens)) {
    throw std::invalid_argument("Incorrect brackets count");
  }
  return tokens;
}

/**
 * @brief Check unary minus function
 */
bool Parser::checkMinus(std::vector<Token> tokens) {
  if (tokens.size() == 0) return true;
  if (tokens[tokens.size() - 1].get<FuncCode>() == FuncCode::SBRACKET)
    return true;
  return false;
}

/**
 * @brief Convert token from infix notation to postfix
 */
std::vector<Token> Parser::toPostfix(std::vector<Token> parsedTokens,
                                     double x) {
  std::stack<Token> stk;
  std::vector<Token> tokens;
  int ind = 0;
  while (ind < (int)parsedTokens.size()) {
    if (parsedTokens[ind].isNum())
      tokens.push_back(parsedTokens[ind]);
    else if (parsedTokens[ind].get<FuncCode>() == FuncCode::X)
      tokens.push_back(Token(x));
    else {
      if (parsedTokens[ind].get<FuncCode>() == FuncCode::SBRACKET)
        stk.push(parsedTokens[ind]);
      else if (parsedTokens[ind].get<FuncCode>() == FuncCode::EBRACKET) {
        while (stk.top().get<FuncCode>() != FuncCode::SBRACKET) {
          tokens.push_back(stk.top());
          stk.pop();
        }
        stk.pop();
      } else {
        if (!stk.empty() &&
            stk.top().getPriority() >= parsedTokens[ind].getPriority()) {
          tokens.push_back(stk.top());
          stk.pop();
          ind--;
        } else
          stk.push(parsedTokens[ind]);
      }
    }
    ind++;
  }
  while (!stk.empty()) {
    tokens.push_back(stk.top());
    stk.pop();
  }
  return tokens;
}

std::string Parser::parseDouble(const std::string string, int startIndex) {
  bool dotFinded = false;
  int endIndex = startIndex;
  while (endIndex < (int)string.size()) {
    if (string[endIndex] >= '0' && string[endIndex] <= '9')
      endIndex++;
    else if (string[endIndex] == '.') {
      if (dotFinded)
        throw std::invalid_argument(
            "Parse double value error. Dot already finded");
      dotFinded = true;
      endIndex++;
    } else
      break;
  }
  return string.substr(startIndex, endIndex - startIndex);
}

bool Parser::checkBrackets(std::vector<Token> tokens) {
  int count_brackets = 0;
  for (size_t i = 0; i < tokens.size(); i++) {
    if (tokens[i].get<FuncCode>() == FuncCode::SBRACKET) count_brackets++;
    if (tokens[i].get<FuncCode>() == FuncCode::EBRACKET) count_brackets--;
  }
  return count_brackets == 0;
}

int Parser::shift(Token token) {
  switch (token.get<FuncCode>()) {
    case FuncCode::MINUS:
    case FuncCode::MULT:
    case FuncCode::PLUS:
    case FuncCode::DIV:
    case FuncCode::EBRACKET:
    case FuncCode::SBRACKET:
    case FuncCode::POW:
    case FuncCode::X:
      return 1;
    case FuncCode::LN:
      return 2;
    case FuncCode::ACOS:
    case FuncCode::ASIN:
    case FuncCode::ATAN:
    case FuncCode::SQRT:
      return 4;
    case FuncCode::LOG:
    case FuncCode::MOD:
    case FuncCode::COS:
    case FuncCode::SIN:
    case FuncCode::TAN:
      return 3;
    default:
      throw std::invalid_argument("Token shift error. Invalid FuncCode");
  }
}

int Parser::priority(const FuncCode code) {
  switch (code) {
    case FuncCode::NUM:
    case FuncCode::X:
      return -1;
    case FuncCode::SBRACKET:
    case FuncCode::EBRACKET:
      return 0;
    case FuncCode::PLUS:
    case FuncCode::MINUS:
      return 2;
    case FuncCode::MULT:
    case FuncCode::DIV:
    case FuncCode::MOD:
      return 3;
    case FuncCode::POW:
    case FuncCode::SIN:
    case FuncCode::COS:
    case FuncCode::TAN:
    case FuncCode::ASIN:
    case FuncCode::ACOS:
    case FuncCode::ATAN:
    case FuncCode::SQRT:
    case FuncCode::LOG:
    case FuncCode::LN:
      return 4;
    default:
      throw std::invalid_argument("Token priority error. Invalid FuncCode");
  }
}

Token Parser::parseToken(const std::string string, int startIndex) {
  switch (string[startIndex]) {
    case 'x':
      return Token(FuncCode::X, FuncType::NONE);
    case '*':
      return Token(FuncCode::MULT, FuncType::BINARY);
    case '+':
      return Token(FuncCode::PLUS, FuncType::BINARY);
    case '-':
      return Token(FuncCode::MINUS, FuncType::BINARY);
    case '/':
      return Token(FuncCode::DIV, FuncType::BINARY);
    case '(':
      return Token(FuncCode::SBRACKET, FuncType::NONE);
    case ')':
      return Token(FuncCode::EBRACKET, FuncType::NONE);
    case '^':
      return Token(FuncCode::POW, FuncType::BINARY);
    case 'a':
      if (string.compare(startIndex, 4, "asin") == 0)
        return Token(FuncCode::ASIN, FuncType::UNARY);
      else if (string.compare(startIndex, 4, "acos") == 0)
        return Token(FuncCode::ACOS, FuncType::UNARY);
      else if (string.compare(startIndex, 4, "atan") == 0)
        return Token(FuncCode::ATAN, FuncType::UNARY);
    case 'm':
      if (string.compare(startIndex, 3, "mod") == 0)
        return Token(FuncCode::MOD, FuncType::BINARY);
    case 's':
      if (string.compare(startIndex, 4, "sqrt") == 0)
        return Token(FuncCode::SQRT, FuncType::UNARY);
      else if (string.compare(startIndex, 3, "sin") == 0)
        return Token(FuncCode::SIN, FuncType::UNARY);
    case 'l':
      if (string.compare(startIndex, 2, "ln") == 0)
        return Token(FuncCode::LN, FuncType::UNARY);
      else if (string.compare(startIndex, 3, "log") == 0)
        return Token(FuncCode::LOG, FuncType::UNARY);
    case 'c':
      if (string.compare(startIndex, 3, "cos") == 0)
        return Token(FuncCode::COS, FuncType::UNARY);
    case 't':
      if (string.compare(startIndex, 3, "tan") == 0)
        return Token(FuncCode::TAN, FuncType::UNARY);
    default:
      throw std::invalid_argument("Parse equation tokens error");
  }
}
