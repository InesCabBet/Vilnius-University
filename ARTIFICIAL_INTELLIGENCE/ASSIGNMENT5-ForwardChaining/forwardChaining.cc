/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 02 NOV 2025 
 * @brief Assignment 5 - Forward Chaining
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

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