/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 02 NOV 2025 
 * @brief Assignment 5 - Forward Chaining fc class
 */

#include "Rule.cc"
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>


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
    /**
     * 
     */
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
    /**
     * 
     */
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

  public:
    ForwardChaining(std::vector<Rule> r, std::vector<std::string> initialFacts, std::string _goal, std::string student = "", std::string test="") 
    : rules(r), goal(_goal), studentInfo(student), testName(test) {
      facts.insert(initialFacts.begin(), initialFacts.end());
    }
    bool solve() {
      trace.push_back("PART 1. DATA\n\n");
      trace.push_back("\t1) Rules:\n");
      for (const auto &rule : rules) {
        trace.push_back("\t   " + rule.toString() + "\n");
      }
      trace.push_back("\n\t2) Initial Facts: " + setToString(facts) + "\n");
      trace.push_back("\n\t3) Goal: " + goal + "\n");
      trace.push_back("\nPART 2. TRACE\n");
      if (facts.find(goal) != facts.end()) {
        trace.push_back("\tGoal is already in initial facts.\n");
        return true;
      }
      int iteration = 0;
      while (true) {
        iteration++;
        trace.push_back("\n\tITERATION " + std::to_string(iteration) + "\n");
        bool applied = false;
        for (auto &rule : rules) {
          if (facts.find(rule.rhs) != facts.end()){
            trace.push_back("\t\t" + rule.name + " not applied, because RHS already in facts.\n");
            continue;
          }
          if (rule.canApply(facts)) {
            trace.push_back("\t\t" + rule.toString() + " apply.\n");
            facts.insert(rule.rhs);
            path.push_back(rule.name);
            trace.push_back("\t\tFacts: " + setToString(facts) + "\n");
            applied = true;
            if (facts.find(goal) != facts.end()) {
              trace.push_back("\t\tGoal achieved.\n");
              break;
            }
            break;
          } else {
            std::vector<std::string> missing = rule.getMissingFacts(facts);
            trace.push_back("\t\t" + rule.name + " not applied, because of lack of " + vectorToString(missing) + "\n");
          }
        }
        if (facts.find(goal) != facts.end()) {
          break;
        }
        if (!applied) {
          trace.push_back("\n\tNo new facts derived. Stopping.\n");
          break;
        }
      }
      return facts.find(goal) != facts.end();
    }

    void printResults() const {
      for (const auto &line : trace) {
        std::cout << line;
      }
      std::cout << "\nPART 3. RESULTS" << std::endl;
      if (facts.find(goal) != facts.end()) {
        if (!path.empty()) {
          std::cout << "\t1) Goal " << goal << " achieved. " << std::endl;
          std::cout << "\t2) Path: " << vectorToString(path) << std::endl;
        } else {
          std::cout << "\tThe path is empty, because goal " << goal << " is in the facts." << std::endl;
        }
      } else {
        std::cout << "\tGoal not achieved. The path does not exists." << std::endl;
      }
    }
};

#endif

