/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 02 NOV 2025 
 * @brief Assignment 5 - Forward Chaining main program
 */

#include "Rule.cc"
#include "forwardChaining.cc"
#include "FileParser.h"
#include <fstream>

int main() {
  std::string filename;
  std::cout << "Enter input filename: ";
  getline(std::cin, filename);
  std::vector<Rule> rules;
  std::vector<std::string> facts;
  std::string goal;
  std::string studentInfo;
  std::string testName;
  if (!FileParser::parseFile(filename, rules, facts, goal, studentInfo, testName)) {
    std::cerr << "Error. Failed to parse file" << std::endl;
    return 1;
  }
  ForwardChaining fc(rules, facts, goal, studentInfo, testName);
  fc.solve();
  std::string outputFile = "output_" + filename;
  std::ofstream out (outputFile);
  if (!out.is_open()) {
    std::cerr << "Error. Cannot open output file " << outputFile << std::endl;
    return 1;
  }
  std::streambuf *coutBuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());
  std::cout << "\nOutput saved to " << outputFile << std::endl;
  return 0;
}