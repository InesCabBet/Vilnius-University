/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 14 NOV 2025 
 * @brief Assignment 6 - Backward Chaining BC class file
 */

#include "utils.h"

std::vector<std::string> BackwardChaining::buildFactsList(const std::string &current, const std::string &type) const {
  std::vector<std::string> list;
  for (const auto &f : initialFactsOrdered) {
    list.push_back(f);
  }
  if (type == "initial") {
    return list;
  } else if (type == "earlier") {
    if (find(list.begin(), list.end(), current) == list.end()) {
      list.push_back(current);
    }
    return list;
  } else {
    for (const auto &f : inferredOrder) {
      if (find(list.begin(), list.end(), f) == list.end()) {
        list.push_back(f);
      }
      if (f == current) {
        break;
      }
    }
    if (find(list.begin(), list.end(), current) == list.end()){
      list.push_back(current);
    }
    return list;
  }
}

bool BackwardChaining::proveGoal(const std::string &currentGoal, int depth, std::set<std::string> &inProgress, std::vector<std::string> &outPath) {
  std::string indent = getIndent(depth);
}