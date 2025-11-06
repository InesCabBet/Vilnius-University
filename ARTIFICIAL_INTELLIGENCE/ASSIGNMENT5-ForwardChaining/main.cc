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