/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSSICAL PRINCIPLES
 * ASSIGNMENT 1 : TOWERS OF HANOI
 * RECURSIVE SOLUTION
 * @author INES CABRERA BETANCOR
 * @date 2025-09-04
 * @brief Recursive solution for the Towers of Hanoi problem.
 * The program reads the number of disks (n) from standard input,
 * checks if n is between 1 and 10, and prints the initial state of the
 * towers. It then solves the problem recursively, printing the state of
 * the towers after each move, and finally prints the total number of moves.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

// Variables globales para las torres y contador de movimientos
std::stack<int> towerA, towerB, towerC;
int moveCount = 0;

// Función para obtener referencia a la torre por su nombre
std::stack<int>& getTower(char name) {
  switch(name) {
    case 'A': return towerA;
    case 'B': return towerB;
    case 'C': return towerC;
    default: return towerA; // nunca debería llegar aquí
  }
}

// Función para imprimir el contenido de una torre
void printTower(char name) {
  std::stack<int> temp = getTower(name);
  std::vector<int> disks;
  // Extraer todos los discos para poder imprimirlos
  while (!temp.empty()) {
    disks.push_back(temp.top());
    temp.pop();
  }
  std::cout << name << "=(";
  for (int i = disks.size() - 1; i >= 0; i--) {
    std::cout << disks[i];
    if (i > 0) std::cout << ",";
  }
  std::cout << ")";
}

// Función para imprimir el estado actual de todas las torres
void printState() {
  printTower('A');
  std::cout << ", ";
  printTower('B');
  std::cout << ", ";
  printTower('C');
  std::cout << ".";
}

// Función recursiva para resolver Torres de Hanoi
void ht(char x, char y, char z, int n) {
  // x – from, y – intermediary, z – onto
  if (n > 0) {
    ht(x, z, y, n-1); // 1. Move n-1 disks onto intermediary
    // 2. Move disk n from x to z
    moveCount++;
    int disk = getTower(x).top();
    getTower(x).pop();
    getTower(z).push(disk);
    std::cout << std::setw(4) << moveCount << ". Move disk " << disk << " from " << x << " to " << z << ". ";
    printState();
    std::cout << std::endl;
    ht(y, x, z, n-1); // 3. Move n-1 disks onto target
  }
}

int main() {
  std::cout << "Enter the number of disks; n = ";
  int n = 0;
  std::cin >> n;
  // (1) Read and print n, check if n is between 1 and 10
  std::cout << "n = " << n << std::endl;
  if (n < 1 || n > 10) {
    std::cout << "Error: n must be between 1 and 10." << std::endl;
    return 1;
  }
  // Inicializar torre A con n discos (del más grande al más pequeño)
  for (int i = n; i >= 1; i--) {
    towerA.push(i);
  }
  // (2) Print initial state
  std::cout << "Initial state: ";
  printState();
  std::cout << std::endl;
  // (3) Solve and print state after each move
  ht('A', 'B', 'C', n);
  std::cout << "Total moves: " << moveCount << std::endl;
  return 0;
}