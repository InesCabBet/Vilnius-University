/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 02 NOV 2025 
 * @brief Assignment 5 - Forward Chaining File Parser class
 */

#include "Rule.cc"
#include "forwardChaining.cc"
#include "utils.h"
#include <fstream>

#ifndef __FILEPARSER__
#define __FILEPARSER__

class FileParser {
  public:
    static bool parseFile(const std::string &filename, std::vector<Rule> &rules, std::vector<std::string> &facts, std::string &goal, std::string &studentInfo, std::string &testName) {
      std::ifstream file(filename);
      if(!file.is_open()) {
        std::cerr << "Error. Cannot open file " << filename << std::endl;
        return false;
      }
      std::string line;
      int section{0};
      int ruleNum{1};
      while (getline(file,line)) {
        line = trim(line);
        if (line.empty()) {
          continue;
        }
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos) {
          line = trim(line.substr(0, commentPos));
        }
        if (line.find("Student") != std::string::npos) {
          studentInfo = line;
          continue;
        }
        if (line.find("Test") != std::string::npos) {
          testName = line;
          continue;
        }
        if (line.find("1) RUles") != std::string::npos) {
          section = 1;
          continue;
        } else if (line.find("2) Facts") != std::string::npos){
          section = 2;
          continue;
        } else if (line.find("3) Goal") != std::string::npos) {
          section = 3;
          continue;
        }

        if (section == 1) {
          std::vector<std::string> elems = split(line, ' ');
          if (elems.size() < 2) {
            continue;
          }
          std::string rhs = elems[0];
          std::vector<std::string> lhs(elems.begin() + 1, elems.end());
          std::string ruleName = "R" + std::to_string(ruleNum++);
          rules.emplace_back(ruleName, lhs, rhs);
        } else if (section == 2) {
          std::vector<std::string> factTokens = split(line, ' ');
          facts.insert(facts.end(), factTokens.begin(), factTokens.end());
        } else if (section == 3) {
          goal = line;
        }
      }
      file.close();
      return !rules.empty() && !goal.empty();
    }
};

#endif