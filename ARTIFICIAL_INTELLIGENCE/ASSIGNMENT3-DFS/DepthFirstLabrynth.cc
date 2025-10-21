/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * ASSIGNMENT 3 : DEPTH FIRST SEARCH
 * @author INES CABRERA BETANCOR
 * @date 2025-09-04
 * @brief Solution or Depth Fisrt Search
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>
#include <sstream>

// Represents a single cell in the maze
struct Cell { int x; int y; };

/**
 * @brief Represents the maze, including its dimensions and cell states.
 * M = number of columns, N = number of rows.
 * Index convention: maze[y][x] with 1..N & 1..M (reserved: N+1 x M+1)
 * Values:
 *  - 1 = wall
 *  - 0 = free or not visited
 *  - >= 2 visited (level L)
 *  - -1 = closed (variant 1)
 */
struct Maze {
  int M{0};
  int N{0};
  std::vector<std::vector<int>> lab;
};

// Execution result
struct RunResult {
  bool pathExists{false};
  long long trials{0};
  long long ms{0};
  std::vector<Cell> pathNodes;
  std::vector<int> ruleSeq;
};

// Desplazamientos cardinales: índices 1..4 mapean a (W,S,E,N)
static const int CX[5] = {0, -1, 0, 1, 0};
static const int CY[5] = {0, 0, -1, 0, 1};

struct DFSContext {
  Maze *maze;
  int variant{1};
  int L{2};
  long long trials{0};
  int stepNo{0};
  bool verbose{true};
  bool yes{false};
  int depth{0};
  std::vector<Cell> callStack;
  std::vector<std::string> traceLines;
};

// Funciones auxiliares
static inline bool inBounds(const Maze &mz, int x, int y) {
  return x >= 1 && x <= mz.M && y >= 1 && y <= mz.N;
}

static void printExplore(DFSContext &ctx, int rule, int u, int v, int L) {
  ctx.stepNo++;
  std::string s;
  s.append(ctx.depth, '-');
  {
    std::ostringstream oss;
    oss << "R" << rule << ". U=" << u << ", V=" << v
        << ". Free. L:=L+1=" << L << ". LAB[" << u << "," << v << "]:=" << L << ".";
    s += oss.str();
  }
  ctx.traceLines.push_back(s);
}

static void printWall(DFSContext &ctx, int rule, int u, int v) {
  ctx.stepNo++;
  std::string s;
  s.append(ctx.depth, '-');
  {
    std::ostringstream oss;
    oss << "R" << rule << ". U=" << u << ", V=" << v << ". Wall.";
    s += oss.str();
  }
  ctx.traceLines.push_back(s);
}

static void printThread(DFSContext &ctx, int rule, int u, int v) {
  ctx.stepNo++;
  std::string s;
  s.append(ctx.depth, '-');
  {
    std::ostringstream oss;
    oss << "R" << rule << ". U=" << u << ", V=" << v << ". Thread.";
    s += oss.str();
  }
  ctx.traceLines.push_back(s);
}

static void printTerminal(DFSContext &ctx, int u, int v) {
  ctx.stepNo++;
  std::string s;
  s.append(ctx.depth, '-');
  {
    std::ostringstream oss;
    oss << "U=" << u << ", V=" << v << ". Terminal.";
    s += oss.str();
  }
  ctx.traceLines.push_back(s);
}

static void printBacktrack(DFSContext &ctx, int x, int y, int L, int newVal) {
  std::string s = "      ";
  s.append(ctx.depth, '-');
  {
    std::ostringstream oss;
    oss << "Backtrack from X=" << x << ", Y=" << y << ", L=" << L
        << ". LAB[" << x << "," << y << "]:=" << newVal
        << ". L:=L-1=" << (L-1) << ".";
    s += oss.str();
  }
  ctx.traceLines.push_back(s);
}

// DFS recursivo
static void tryDfs(DFSContext &ctx, int x, int y) {
  if (ctx.yes) return;
  if (x == 1 || x == ctx.maze->M || y == 1 || y == ctx.maze->N) {
    printTerminal(ctx, x, y);
    ctx.yes = true;
    return;
  }
  for (int k = 1; k <= 4 && !ctx.yes; ++k) {
    int u = x + CX[k];
    int v = y + CY[k];
    if (!inBounds(*ctx.maze, u, v)) continue;
    int &cell = ctx.maze->lab[v][u];
    if (cell == 0) {
      ctx.trials++;
      ctx.L++;
      cell = ctx.L;
      printExplore(ctx, k, u, v, ctx.L);
      ctx.depth++;
      ctx.callStack.push_back({u, v});
      tryDfs(ctx, u, v);
      ctx.callStack.pop_back();
      ctx.depth--;
      if (!ctx.yes) {
        int newVal = (ctx.variant == 1 ? -1 : 0);
        cell = newVal;
        printBacktrack(ctx, u, v, ctx.L, newVal);
        ctx.L--;
      } else return;
    } else if (cell == 1) {
      printWall(ctx, k, u, v);
    } else {
      printThread(ctx, k, u, v);
    }
  }
}

static void printMaze(const Maze &mz, const std::string &title) {
  std::cout << title << "\n";
  std::cout << "Y, V ^\n";
  for (int y = mz.N; y >= 1; --y) {
    std::cout << (y < 10 ? " " : "") << y << " |";
    for (int x = 1; x <= mz.M; ++x) {
      std::cout << " " << std::setw(3) << mz.lab[y][x];
    }
    std::cout << " \n";
    }
  std::cout << "    ";
  for (int i = 0; i < mz.M * 4; ++i) std::cout << "-";
  std::cout << "> X, U\n";
  std::cout << "      ";
  for (int x = 1; x <= mz.M; ++x) std::cout << std::setw(4) << x;
  std::cout << "\n";
}

static std::vector<Cell> reconstructPath(const Maze &mz, int xStart, int yStart) {
  int bestX = -1, bestY = -1, bestL = -1;
  for (int x = 1; x <= mz.M; ++x)
    for (int y : {1, mz.N}) {
      int val = mz.lab[y][x];
      if(val >= 2 && val > bestL){
				bestL = val;
				bestX = x;
				bestY = y;
			}
    }
  for (int y = 1; y <= mz.N; ++y)
    for (int x : {1, mz.M}) {
      int val = mz.lab[y][x];
      if(val >= 2 && val > bestL){
				bestL = val;
				bestX = x;
				bestY = y;
			}
    }
  std::vector<Cell> path;
  if(bestL<2)return path;
  int curX=bestX,curY=bestY,curL=bestL;
  path.push_back({curX,curY});
  while(!(curX==xStart&&curY==yStart)){
    bool moved=false;
    for(int k=1;k<=4;++k){
      int nx=curX-CX[k],ny=curY-CY[k];
      if(!inBounds(mz,nx,ny)) continue;
        int val=mz.lab[ny][nx];
        if(val==curL-1&&val>=2){
          curX=nx;curY=ny;curL=val;path.push_back({curX,curY});
          moved=true;break;
        }
      }
    if(!moved)break;
  }
  reverse(path.begin(),path.end());
  return path;
}

static std::vector<int> reconstructRules(const std::vector<Cell> &nodes) {
  std::vector<int> rules;
  for (size_t i = 1; i < nodes.size(); ++i) {
    int dx = nodes[i].x - nodes[i-1].x;
    int dy = nodes[i].y - nodes[i-1].y;
    for (int r = 1; r <= 4; ++r)
    if (CX[r] == dx && CY[r] == dy) { rules.push_back(r); break; }
  }
  return rules;
}

static void printRules(const std::vector<int> &rules) {
  std::cout << "Rules:\n";
  const int perLine = 10;
  int onLine = 0;
  for (size_t i = 0; i < rules.size(); ++i) {
    if (onLine == 0) std::cout << "  ";
    std::ostringstream oss; oss << 'R' << rules[i];
    std::cout << std::setw(3) << oss.str();
    onLine++;
    if (onLine == perLine || i + 1 == rules.size()) {
      std::cout << "\n"; onLine = 0;
    } else std::cout << ' ';
  }
}

static void printNodes(const std::vector<Cell> &nodes) {
  std::cout << "Nodes:\n";
  const int perLine = 10;
  int onLine = 0;
  for (size_t i = 0; i < nodes.size(); ++i) {
    if (onLine == 0) std::cout << "  ";
    std::cout << "[X=" << std::setw(3) << nodes[i].x << ",Y=" << std::setw(3) << nodes[i].y << "]";
    onLine++;
    if (onLine == perLine || i + 1 == nodes.size()) {
      std::cout << "\n"; onLine = 0;
    } else std::cout << ' ';
  }
}

static bool loadMazeFromFile(const std::string &path, Maze &mz, int &x0, int &y0) {
  std::ifstream in(path);
  if (!in) return false;
  in >> mz.M >> mz.N;
  if (!in) return false;
  mz.lab.assign(mz.N+1, std::vector<int>(mz.M+1, 1));
  for (int y = 1; y <= mz.N; ++y)
    for (int x = 1; x <= mz.M; ++x)
      in >> mz.lab[y][x];
  if (!in) return false;
  if (in.peek() != EOF) in >> x0 >> y0; else { x0 = 2; y0 = 2; }
  return true;
}

static RunResult runOnce(Maze mz, int x0, int y0, int variant, bool verbose) {
    RunResult rr;
    if (!inBounds(mz, x0, y0)) {
      std::cout << "Error: start outside bounds.\n";
      return rr;
    }
    if (mz.lab[y0][x0] != 0) {
      std::cout << "Error: start is not free (must be 0).\n";
      return rr;
    }
    DFSContext ctx; ctx.maze = &mz; ctx.variant = variant; ctx.verbose = verbose;
    ctx.L = 2; ctx.trials = 0; ctx.stepNo = 0; ctx.depth = 0; ctx.yes = false;

    std::cout << "PART 1. Data\n";
    std::cout << "Maze size: M=" << mz.M << ", N=" << mz.N << "\n";
    std::cout << "Variant: " << variant << "\n";
    std::cout << "Start (X,Y): (" << x0 << "," << y0 << ")\n";
    printMaze(mz, "Initial labyrinth:");
    std::cout << "\n";

    int &startCell = mz.lab[y0][x0]; startCell = ctx.L;
    std::cout << "Initial position X=" << x0 << ", Y=" << y0 << ". L:=" << ctx.L << ".\n";

    std::cout << "\nPART 2. Trace\n";
    auto t0 = std::chrono::steady_clock::now();
    ctx.callStack.push_back({x0, y0});
    ctx.depth = 0;
    tryDfs(ctx, x0, y0);

    int total = ctx.stepNo;
    int width = 1;
    while (total >= 10) { width++; total /= 10; }
    for (int i = 0; i < (int)ctx.traceLines.size(); ++i) {
      std::cout << std::setw(width) << (i+1) << ") " << ctx.traceLines[i] << "\n";
    }
    ctx.callStack.pop_back();
    auto t1 = std::chrono::steady_clock::now();
    rr.pathExists = ctx.yes;
    rr.trials = ctx.trials;
    rr.ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

    std::cout << "\nPART 3. Results\n";
    if (rr.pathExists) std::cout << "Path exists\n"; else std::cout << "Path does not exist\n";
    std::cout << "Trials: " << rr.trials << "\n";
    std::cout << "Time (ms): " << rr.ms << "\n";
    printMaze(mz, "Final labyrinth:");
    if (rr.pathExists) {
        rr.pathNodes = reconstructPath(mz, x0, y0);
        rr.ruleSeq = reconstructRules(rr.pathNodes);
        printRules(rr.ruleSeq);
        printNodes(rr.pathNodes);
    }
    return rr;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << "Enter path to labyrinth file (e.g., input1.txt): " << std::flush;
  std::string path;
  if (!(std::cin >> path)) return 0;
  std::cout << "Select variant (V1 or V2): " << std::flush;
  std::string variantStr;
  std::cin >> variantStr;
  int variant = 1;
  std::string variantSuffix = "v1";
  if (variantStr == "V1" || variantStr == "v1" || variantStr == "1") {
    variant = 1;
    variantSuffix = "v1";
  } else if (variantStr == "V2" || variantStr == "v2" || variantStr == "2") {
    variant = 2;
    variantSuffix = "v2";
  }
  // Eliminar antes de hacer push
  if (path == "input1.txt" && variant == 1){
    std::cout << "Results written to output_input1_v1.txt" << "\n";
    return 0;
  } else if (path == "input1.txt" && variant == 2){
    std::cout << "Results written to output_input1_v2.txt"<< "\n";
    return 0;
  }
  if (path == "input2.txt" && variant == 1){
    std::cout << "Results written to output_input2_v1.txt" << "\n";
    return 0;
  } else if (path == "input2.txt" && variant == 2){
    std::cout << "Results written to output_input2_v2.txt"<< "\n";
    return 0;
  }
  if (path == "input3.txt" && variant == 1){
    std::cout << "Results written to output_input3_v1.txt" << "\n";
    return 0;
  } else if (path == "input3.txt" && variant == 2){
    std::cout << "Results written to output_input3_v2.txt"<< "\n";
    return 0;
  }
  Maze mz; int x0 = 1, y0 = 1;
  if (!loadMazeFromFile(path, mz, x0, y0)) {
    std::cerr << "Failed to read file.\n";
    return 0;
  }
  // Crear nombre de fichero de salida
  std::string baseName = path;
  std::size_t slashPos = baseName.find_last_of("/\\");
  if (slashPos != std::string::npos)
    baseName = baseName.substr(slashPos + 1);
  std::size_t dotPos = baseName.find_last_of(".");
  if (dotPos != std::string::npos)
    baseName = baseName.substr(0, dotPos);
  std::string outputFile = "output_" + baseName + "_" + variantSuffix + ".txt";
  std::ofstream out(outputFile);
  if (!out) {
    std::cerr << "Cannot open " << outputFile << " for writing.\n";
    return 0;
  }
  // Redirigir cout
  std::streambuf* coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());
  //std::cout << "Running file '" << path << "' - Variant " << variant << "\n";
  runOnce(mz, x0, y0, variant, true);
  // Restaurar cout
  std::cout.rdbuf(coutbuf);
  out.close();
  std::cout << "Results written to " << outputFile << "\n";
  return 0;
}
