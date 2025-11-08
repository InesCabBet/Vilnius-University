/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 14 NOV 2025 
 * @brief Assignment 6 - Backward Chaining main program
 */

#include "utils.h"

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string filename;
  if (argc > 1) {
    filename = argv[1];
  } else {
    std::cout << "Enter input file name: ";
    getline(std::cin, filename);
  }
  std::vector<Rule> rules;
  std::vector<std::string> facts;
  std::string goal;
  if (!FileParser::parseFile(filename, rules, facts, goal)){
    std:: cerr << "Error. Failed to parse file" << std::endl;
    return 1;
  }
  BackwardChaining bc(rules, facts, goal);
  bc.solve();
  std::string outputFile = "output_" + filename;
  std::ofstream out(outputFile);
  if (!out.is_open()) {
    std::cerr << "Error. Cannot open output file " << filename << std::endl;
    return 1;
  }
  std::streambuf *coutBuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());
  bc.printResults();
  std::cout.rdbuf(coutBuf);
  std::cout << "\nOutput saved to " << outputFile << std::endl;
  return 0;
}