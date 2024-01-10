#ifndef BASE_H
#define BASE_H

#include <algorithm>
#include <cmath>
#include <stack>
#include <string>
#include <vector>

#define EPS 1E-6

/**
 * @brief Enum for coding math operators (mod, sqrt) and functions
 * (sin, cos, etc.).
 */
enum class FuncCode {
  NUM = '\0',
  SBRACKET = '(',
  EBRACKET = ')',
  PLUS = '+',
  MINUS = '-',
  MULT = '*',
  DIV = '/',
  SIN = 's',
  COS = 'c',
  TAN = 't',
  ASIN = 'S',
  ACOS = 'C',
  ATAN = 'T',
  SQRT = 'q',
  LOG = 'l',
  LN = 'L',
  MOD = 'm',
  POW = '^',
  X = 'x'
};

/**
 * @brief Enum for type math operators (binary, unary).
 */
enum class FuncType { BINARY, UNARY, NONE };

#endif  // BASE_H