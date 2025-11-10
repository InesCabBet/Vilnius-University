/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 14 NOV 2025 
 * @brief Assignment 6 - Backward Chaining FileParser class file
 */

#include "utils.h"

bool FileParser::parseFile(const std::string &filename, std::vector<Rule> &rules, std::vector<std::string> &facts, std::string &goal) {
  std::ifstream file(filename);
  if(!file.is_open()) {
    std::cerr << "Error. Cannot open file " << filename << std::endl;
    return false;
  }
  return true;
}