/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 02 NOV 2025 
 * @brief Assignment 5 - Forward Chaining main program
 */

#include "Rule.cc"
#include <sstream>

#ifndef __FORWARD__
#define __FORWARD__

class ForwardChaining {
  private: 
  std::vector<Rule> rules;
  std::set<std::string> facts;
  std::string goal;
  std::vector<std::string> path;
  std::vector<std::string> trace;
  std::string studentInfo;
  std::string testName;
  std::string setToString(const std::set<std::string> &set) const {
    std::string result;
    bool first = true;
    for (const auto &item : set) {
      if (!first) {
        result += ", ";
      }
      result += item;
      first += false;
    }
    return result;
  }
  std::string vectorToString(const std::vector<std::string> &vector) const {
    std::string result;
    for (size_t i = 0; i < vector.size(); i++){
      result += vector[i];
      if (i < vector.size() - 1){
        result += ", ";
      }
    }
    return result;
  }
};

#endif

