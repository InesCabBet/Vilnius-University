/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSSICAL PRINCIPLES
 * ASSIGNMENT 1 : TOWERS OF HANOI
 * RECURSIVE SOLUTION
 * @author INES CABRERA BETANCOR
 * @date 2025-09-04
 * @brief Iterative solution for the Towers of Hanoi problem.
 * The program reads the number of disks (n) from standard input,
 * checks if n is between 1 and 10, and prints the initial state of the
 * towers. It then solves the problem iteratively, printing the state of
 * the towers after each move, and finally prints the total number of moves.
 */

#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

/**
 * Removes the top element from the stack and returns it.
 * Assumes the stack is not empty.
 */
int removeAndReturn(std::stack<int>& stack) {
  int moving = stack.top();
  stack.pop();
  return moving;
}

/**
 * Populates the stack with integers from n down to 1.
 */
void populate(std::stack<int>& stack, int n) {
  for (int i = n; i >= 1; i--) {
    stack.push(i);
  }
}

/**
 * Checks if a number is odd.
 */
bool isOdd(int n) {
  return n % 2 != 0;
}

/**
 * Returns the character name of the peg given its index.
 */
char pegName(int idx) {
  return 'A' + idx;
}

/**
 * Converts the contents of a stack to a string representation.
 */
std::string stackToString(std::stack<int> s) {
  std::vector<int> elems;
  while (!s.empty()) {
    elems.push_back(s.top());
    s.pop();
  }
  reverse(elems.begin(), elems.end());
  std::string res = "(";
  for (int i = 0; i < elems.size(); i++) {
    res += std::to_string(elems[i]);
    if (i + 1 < elems.size()) res += ", ";
  }
  res += ")";
  return res;
}

/**
 * Prints the details of a move including the state of all pegs.
 */
void printMove(int moveNum, int disk, int from, int to, const std::vector<std::stack<int>>& pegs) {
  std::cout << std::setw(4) << moveNum << ". "
  << "Move disk " << disk << " from " << pegName(from)
  << " to " << pegName(to) << ".   "
  << "A = " << std::setw(24) << stackToString(pegs[0]) << "   "
  << "B = " << std::setw(24) << stackToString(pegs[1]) << "   "
  << "C = " << std::setw(24) << stackToString(pegs[2]) << "\n";
}

/**
 * Moves the top disk from one stack to another if the move is valid.
 * Returns the disk moved, or -1 if the move is invalid.
 */
int moveDisk(std::stack<int>& from, std::stack<int>& to) {
  if (from.empty()) return -1;
  if (to.empty() || from.top() < to.top()) {
    int disk = from.top();
    from.pop();
    to.push(disk);
    return disk;
  }
  return -1;
}

/**
 * Solves the Towers of Hanoi problem iteratively.
 */
void ht(int n) {    
  std::vector<std::stack<int>> pegs(3);
  populate(pegs[0], n);
  std::vector<int> order;
  if (isOdd(n)) order = {0, 2, 1};
  else order = {0, 1, 2};
  int pos = 0;
  int moveNum = 1;
  std::cout << "Initial state:\n";
  std::cout << "A = " << stackToString(pegs[0]) << "   "
  << "B = " << stackToString(pegs[1]) << "   "
  << "C = " << stackToString(pegs[2]) << "\n\n";
  for (int i = 1; i <= pow(2, n) - 1; i++) {
    if (i % 2 == 1) {
      int from = order[pos];
      int to   = order[(pos + 1) % 3];
      int disk = moveDisk(pegs[from], pegs[to]);
      printMove(moveNum++, disk, from, to, pegs);
      pos = (pos + 1) % 3;
    } else {
      int a = order[(pos + 1) % 3];
      int b = order[(pos + 2) % 3];
      int disk;
      if ((disk = moveDisk(pegs[a], pegs[b])) != -1) {
        printMove(moveNum++, disk, a, b, pegs);
      } else if ((disk = moveDisk(pegs[b], pegs[a])) != -1) {
        printMove(moveNum++, disk, b, a, pegs);
      }
    }
  }
  std::cout << "Total moves: " << moveNum - 1 << std::endl;
}

int main() {
  int n;
  std::cout << "Enter the number of disks; n = ";
  std::cin >> n;
  if (n < 1 || n > 10) {
    std::cout << "Error: n must be between 1 and 10." << std::endl;
    return 1;
  }
  ht(n);
  return 0;
}