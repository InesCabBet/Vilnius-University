/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 02 NOV 2025 
 * @brief Assignment 5 - Forward Chaining - Rule Class
 */

#include <vector>
#include <set>
#include <string>

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
    /**
     * @brief checks if the rule can be applied given known facts. A rule can be applied if all facts on the 
     * left side are present in the current set of facts
     * @param facts set of current facts
     * @return true if all facts necessary are in the set
     * @return false if not all facts necessary are in the set
     */
    bool canApply(const std::set<std::string> & facts) const {
      for (const auto &fact : lhs) {
        if (facts.find(fact) == facts.end()) {
          return false;
        }
      }
      return true;
    }
    /**
     * @brief Resets the state of flag 1 to false
     */
    void resetFlag1() {
      flag1 = false;
    }
    /**
     * @brief Returns a text representation of the rule
     * Format: "name: fact1, fact2 -> result"
     * @return std::string string that represents the rule
     */
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
    /**
     * @brief Obtains the facts we would need to apply the rule
     * It goes through the lhs facts and returns those who are not present in the current fact set
     * @param facts current fact set
     * @return a list of remaining facts
     */
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