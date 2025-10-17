/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * ASSIGNMENT 2 : KNIGHT'S TOUR
 * @author INES CABRERA BETANCOR
 * @date 2025-09-20
 * @brief Solution for the Knight's Tour problem using backtracking.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

int CX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int CY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int N;
std::vector<std::vector<int>> board;
long long trace_counter = 0;
bool found = false;

std::ofstream foutShort;
std::ofstream foutLong;

const std::string YELLOW = "\033[33m";
const std::string RESET  = "\033[0m";

/**
 * Prints a message to both standard output and the short output file.
 * @param os The output stream (typically std::cout).
 * @param s The message to print.
 */
void printShort(std::ostream &os, const std::string &s) {
  std::cout << s << std::endl;
  foutShort << s << std::endl;
  foutLong << s << std::endl;
}

/**
 * Prints a message to the long output file.
 * @param os The output stream (typically std::cout).
 * @param s The message to print.
 */
void printLong(std::ostream &os, const std::string &s) {
  foutLong << s << std::endl;
}

/**
 * Attempts to find a knight's tour using backtracking.
 * @param L The current move number.
 * @param x The current x-coordinate of the knight.
 * @param y The current y-coordinate of the knight.
 * @param depth The current depth in the recursion (for tracing).
 * @param total The total number of moves needed to complete the tour.
 * @return True if a solution is found, false otherwise.
 */
bool try_move(int L, int x, int y, int depth, int total) {
  for (int k = 0; k < 8; k++) {
    int u = x + CX[k];
    int v = y + CY[k];
    trace_counter++;
    foutLong << std::endl << std::setw(9) << trace_counter << ") "
             << std::string(depth, '-')
             << "R" << (k + 1)
             << ". U=" << (u + 1) << ", V=" << (v + 1)
             << ". L=" << L << ". ";
    if (u < 0 || u >= N || v < 0 || v >= N) {
      foutLong << "Out.";
      continue;
    }
    if (board[u][v] != 0) {
      foutLong << "Thread.";
      continue;
    }
    foutLong << "Free. BOARD[" << (u + 1) << "," << (v + 1) << "] := " << L << ".";
    board[u][v] = L;
    if (L == total) {
      found = true;
      return true;
    }
    if (try_move(L + 1, u, v, depth + 1, total)) {
      return true;
    }
    // Si llegamos aquí, significa que el movimiento no llevó a solución → backtrack
    board[u][v] = 0;
    foutLong << " --- > Backtrack";
  }
  return false;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <out-short.txt> <out-long.txt>" << std::endl;
    return 1;
  }
  foutShort.open(argv[1]);
  foutLong.open(argv[2]);
  int x, y;
  std::cout << YELLOW << "Board size N: ";
  std::cin >> N;
  std::cout << "Start X: ";
  std::cin >> x;
  std::cout << "Start Y: ";
  std::cin >> y;
  std::cout << RESET << std::endl;
  board.assign(N, std::vector<int>(N, 0));
  int total = N * N;
  board[x - 1][y - 1] = 1;
  // PART 1
  printShort(std::cout, "PART 1. Data");
  printShort(std::cout, " 1) Board: " + std::to_string(N) + "x" + std::to_string(N) + ".");
  printShort(std::cout, " 2) Initial position: X=" + std::to_string(x) + ", Y=" + std::to_string(y) + ". L=1.\n");
  // PART 2
  foutLong << "PART 2. Trace";
  try_move(2, x - 1, y - 1, 1, total);
  // PART 3
  printShort(std::cout, "\n\nPART 3. Results");
  if (found) {
    printShort(std::cout, " 1) Path is found. Trials = " + std::to_string(trace_counter) + ".");
    printShort(std::cout, " 2) Path graphically:");

    int maxVal = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (board[i][j] > maxVal) {
          maxVal = board[i][j];
        }
      }
    }
    int width = std::to_string(maxVal).length();
    printShort(std::cout, "  Y, V ^");
    for (int row = N; row >= 1; row--) {
      std::cout << std::setw(6) << row << " |";
      foutShort << std::setw(6) << row << " |";
      foutLong << std::setw(6) << row << " |";
      for (int col = 1; col <= N; col++) {
        std::cout << std::setw(width + 1) << board[col - 1][row - 1];
        foutShort << std::setw(width + 1) << board[col - 1][row - 1];
        foutLong << std::setw(width + 1) << board[col - 1][row - 1];
      }
      std::cout << std::endl;
      foutShort << std::endl;
      foutLong << std::endl;
    }
    std::string sep = "        " + std::string(3 + N * (width + 1), '-') + "> X, U";
    printShort(std::cout, sep);
    std::cout << "        ";
    foutShort << "        ";
    foutLong << "        ";
    for (int col = 1; col <= N; col++) {
      std::cout << std::setw(width + 1) << col;
      foutShort << std::setw(width + 1) << col;
      foutLong << std::setw(width + 1) << col;
    }
    std::cout << std::endl;
    foutShort << std::endl;
    foutLong << std::endl;
  } else {
    printShort(std::cout, " 1) Path does not exist. Trials = " + std::to_string(trace_counter) + ".");
  }
  foutShort.close();
  foutLong.close();
  return 0;
}

