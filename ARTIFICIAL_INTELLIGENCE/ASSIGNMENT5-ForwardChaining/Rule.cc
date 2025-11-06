/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 02 NOV 2025 
 * @brief Assignment 5 - Forward Chaining - Rule Class
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

#ifndef __RULE__
#define __RULE__

class Rule {
  public:
    std::string name;
    std::vector<std::string> lhs;
    std::string rhs;
    bool flag1;
    bool flag2;
    Rule(std::string _name, std::vector<std::string> _lhs, std::string _rhs) : name(_name), lhs(_lhs), rhs(_rhs), flag1(false), flag2(false) {} 
    Rule(std::string _name, std::string _lhs, std::string _rhs) : name(_name), lhs({_lhs}), rhs(_rhs), flag1(false), flag2(false) {}
    bool canApply(const std::set<std::string> & facts) const {
      for (const auto &fact : lhs) {
        if (facts.find(fact) == facts.end()) {
          return false;
        }
      }
      return true;
    }
    void resetFlag1() {
      flag1 = false;
    }
    std::string toString() const {
      std::string result = name + ": ";
      for (size_t i = 0; i < lhs.size(); i++) {
        result += lhs[i];
        if (i < lhs.size() - 1) {
          result += ", ";
        }
      }
      result += " -> " + rhs;
      return result;
    }
    std::vector<std::string> getMissingFacts(const std::set<std::string> &facts) const {
      std::vector<std::string> missing;
      for (const auto &fact : lhs) {
        if (facts.find(fact) == facts.end()){
          missing.push_back(fact);
        }
      }
      return missing;
    }
};

#endif