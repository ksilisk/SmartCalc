#include "token.hpp"

#include "parser.hpp"

using namespace s21;

bool Token::isNum() const { return func == FuncCode::NUM; }

int Token::getPriority() { return this->priority; }

FuncType Token::getType() { return this->type; }

Token::Token(FuncCode func, FuncType type)
    : Token(func, 0.0, Parser::priority(func), type){};

Token::Token(double num)
    : Token(FuncCode::NUM, num, Parser::priority(FuncCode::NUM),
            FuncType::NONE){};

Token::Token(FuncCode code, double num, int priority, FuncType type) {
  this->func = code;
  this->numValue = num;
  this->priority = priority;
  this->type = type;
}