/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 14 NOV 2025 
 * @brief Assignment 6 - Backward Chaining utils declaration file
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <iomanip>
#include <unordered_map>

#ifndef __UTILS_H__
#define __UTILS_H__

std::string trim(const std::string &str);
std::vector<std::string> split(const std::string &str, char delimiter);
std::string stepTag(int n, int width = 9);
std::string joinFactsList(const std::vector<std::string> &items);

class Rule {
  public:
    std::string name;
    std::vector<std::string> lhs;
    std::string rhs;
    Rule(std::string n, std::vector<std::string> l, std::string r) : name(std::move(n)), lhs(std::move(l)), rhs(std::move(r)) {}
    std::string toString() const;
};

class BackwardChaining {
  private:
    std::vector<Rule> rules;
    std::set<std::string> initialFacts;
    std::vector<std::string> initialFactsOrdered;
    std::string goal;
    std::vector<std::string> finalPath;
    std::vector<std::string> trace;
    int traceCounter;
    std::set<std::string> memoTrue;
    std::unordered_map<std::string, std::vector<std::string>> memoProofTrue;
    std::vector<std::string> inferredOrder;
    std::string getIndent(int depth) const {return std::string(depth, '-');}
    std::vector<std::string> buildFactsList(const std::string &current, const std::string &type) const;
    bool proveGoal(const std::string &currentGoal, int depth, std::set<std::string> &inProgress, std::vector<std::string> &outPath);
  
  public:
    BackwardChaining (std::vector<Rule> r, std::vector<std::string> facts, std::string g) : rules(std::move(r)), goal(std::move(g)), traceCounter(1) {
      initialFacts.insert(facts.begin(), facts.end());
      initialFactsOrdered.assign(initialFacts.begin(), initialFacts.end());
      sort(initialFactsOrdered.begin(), initialFactsOrdered.end());
    }
    bool solve();
    void printResults();
};

class FileParser {
  public: 
    static bool parseFile(const std::string &filename, std::vector<Rule> &rules, std::vector<std::string> &facts, std::string &goal);
};

#endif