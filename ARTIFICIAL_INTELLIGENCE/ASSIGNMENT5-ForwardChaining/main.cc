/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 02 NOV 2025 
 * @brief Assignment 5 - Forward Chaining main program
 */

#include "Rule.cc"
#include "forwardChaining.cc"
#include <sstream>
#include <iostream>

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

int main() {
  std::string filename;
  std::cout << "Enter input filename: ";
  getline(std::cin, filename);
  std::vector<Rule> rules;
  std::vector<std::string> facts;
  std::string goal;
  std::string studentInfo;
  std::string testName;
  //ForwardChaining fc(rules, facts, goal, studentInfo, testName);
}