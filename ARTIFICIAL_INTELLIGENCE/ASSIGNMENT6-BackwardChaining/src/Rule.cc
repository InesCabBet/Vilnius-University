/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 14 NOV 2025 
 * @brief Assignment 6 - Backward Chaining Rule class file
 */

#include "utils.h"

std::string Rule::toString() const {
  std::string result = name + ": ";
  for (size_t i = 0; i < lhs.size(); i++){
    result += lhs[i];
    if (i < lhs.size() - 1) {
      result += ", ";
    }
  }
  result += " -> "+ rhs;
  return result;
}