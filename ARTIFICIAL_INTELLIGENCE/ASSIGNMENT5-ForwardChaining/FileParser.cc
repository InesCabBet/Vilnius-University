/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 02 NOV 2025 
 * @brief Assignment 5 - Forward Chaining File Parser class
 */

#include "Rule.cc"
#include "forwardChaining.cc"
#include <fstream>

#ifndef __FILEPARSER__
#define __FILEPARSER__

/**
 * @brief Function to trim a string
 * @param str string to trim
 */
std::string trim(const std::string &str) {
  size_t primero = str.find_first_not_of(" \t\n\r");
  if (primero == std::string::npos) {
    return "";
  }
  size_t ultimo = str.find_last_not_of(" \t\n\r");
  return str.substr(primero, ultimo - primero + 1);
}

/**
 * @brief Functions to split a string
 * @param str string to split
 * @param delimiter where to stop to trim
 */
std::vector<std::string> split (const std::string &str, char delimiter) {
  std::vector<std::string> elems;
  std::stringstream ss(str);
  std::string elem;
  while (getline(ss, elem, delimiter)) {
    std::string trimed = trim(elem);
    if (!trimed.empty()) {
      elems.push_back(trimed);
    }
  }
  return elems;
}

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