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
static inline std::string stepTag(int n, int width = 5);
static inline std::string joinFactsList(const std::vector<std::string> &items);

class Rule {
  public:
    std::string name;
    std::vector<std::string> lhs;
    std::string rhs;
    Rule(std::string n, std::vector<std::string> l, std::string r) : name(std::move(n)), lhs(std::move(l)), rhs(std::move(r)) {}
    std::string toString() const;
};

#endif