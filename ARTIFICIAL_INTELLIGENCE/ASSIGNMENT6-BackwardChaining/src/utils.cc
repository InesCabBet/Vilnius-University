/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 14 NOV 2025 
 * @brief Assignment 6 - Backward Chaining utils definition file
 */

#include "utils.h"

std::string trim(const std::string &str) {
  size_t first = str.find_first_not_of(" \t\n\r");
  if (first == std::string::npos)
    return "";
  size_t last = str.find_last_not_of(" \t\n\r");
  return str.substr(first, last - first + 1);
}

std::vector<std::string> split(const std::string &str, char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (getline(ss, token, delimiter)) {
    std::string t = trim(token);
    if (!t.empty())
      tokens.push_back(t);
  }
  return tokens;
}

std::string stepTag(int n, int width) {
  std::ostringstream os;
  os << std::setw(width) << std::setfill(' ') << std::right << n;
  return os.str();
}

// helper: join facts come "A" | "A and B" | "A and B, C, D"
std::string joinFactsList(const std::vector<std::string> &items) {
  if (items.empty())
    return "";
  if (items.size() == 1)
    return items[0];
  std::string out = items[0] + " and " + items[1];
  for (size_t i = 2; i < items.size(); ++i)
    out += ", " + items[i];
  return out;
}