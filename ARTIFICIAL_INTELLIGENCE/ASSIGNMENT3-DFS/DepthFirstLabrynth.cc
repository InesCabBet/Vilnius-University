// Inclusiones portables que reemplazan el no-estándar <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>
#include <sstream>
using namespace std;

// Celda del laberinto con coordenadas 1-basadas: X (columna) y Y (fila)
struct Cell { int x; int y; };

// Estructura de laberinto: M columnas (X), N filas (Y) y matriz 'lab'
// Convención de índices: lab[y][x] con 1..N y 1..M (se reserva N+1 x M+1)
// Valores: 1=pared, 0=libre no visitado, >=2=visitado (nivel L), -1=cerrado (variante 1)
struct Maze {
    int M{0};
    int N{0};
    vector<vector<int>> lab;
};

// Resultado de una ejecución
struct RunResult {
    bool pathExists{false};
    long long trials{0};
    long long ms{0};
    vector<Cell> pathNodes;
    vector<int> ruleSeq;
};

// Desplazamientos cardinales: índices 1..4 mapean a (W,S,E,N)
static const int CX[5] = {0, -1, 0, 1, 0};
static const int CY[5] = {0, 0, -1, 0, 1};

// Contexto DFS
struct DFSContext {
    Maze *maze;
    int variant{1};
    int L{2};
    long long trials{0};
    int stepNo{0};
    bool verbose{true};
    bool yes{false};
    int depth{0};
    vector<Cell> callStack;
    vector<string> traceLines;
};

// Funciones auxiliares
static inline bool inBounds(const Maze &mz, int x, int y) {
    return x >= 1 && x <= mz.M && y >= 1 && y <= mz.N;
}

static void printExplore(DFSContext &ctx, int rule, int u, int v, int L) {
    ctx.stepNo++;
    string s;
    s.append(ctx.depth, '-');
    {
        ostringstream oss;
        oss << "R" << rule << ". U=" << u << ", V=" << v
            << ". Free. L:=L+1=" << L << ". LAB[" << u << "," << v << "]:=" << L << ".";
        s += oss.str();
    }
    ctx.traceLines.push_back(s);
}

static void printWall(DFSContext &ctx, int rule, int u, int v) {
    ctx.stepNo++;
    string s;
    s.append(ctx.depth, '-');
    {
        ostringstream oss;
        oss << "R" << rule << ". U=" << u << ", V=" << v << ". Wall.";
        s += oss.str();
    }
    ctx.traceLines.push_back(s);
}

static void printThread(DFSContext &ctx, int rule, int u, int v) {
    ctx.stepNo++;
    string s;
    s.append(ctx.depth, '-');
    {
        ostringstream oss;
        oss << "R" << rule << ". U=" << u << ", V=" << v << ". Thread.";
        s += oss.str();
    }
    ctx.traceLines.push_back(s);
}

static void printTerminal(DFSContext &ctx, int u, int v) {
    ctx.stepNo++;
    string s;
    s.append(ctx.depth, '-');
    {
        ostringstream oss;
        oss << "U=" << u << ", V=" << v << ". Terminal.";
        s += oss.str();
    }
    ctx.traceLines.push_back(s);
}

static void printBacktrack(DFSContext &ctx, int x, int y, int L, int newVal) {
    string s = "      ";
    s.append(ctx.depth, '-');
    {
        ostringstream oss;
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

static void printMaze(const Maze &mz, const string &title) {
    cout << title << "\n";
    cout << "Y, V ^\n";
    for (int y = mz.N; y >= 1; --y) {
        cout << (y < 10 ? " " : "") << y << " |";
        for (int x = 1; x <= mz.M; ++x) {
            cout << " " << setw(3) << mz.lab[y][x];
        }
        cout << " \n";
    }
    cout << "    ";
    for (int i = 0; i < mz.M * 4; ++i) cout << "-";
    cout << "> X, U\n";
    cout << "      ";
    for (int x = 1; x <= mz.M; ++x) cout << setw(4) << x;
    cout << "\n";
}

static vector<Cell> reconstructPath(const Maze &mz, int xStart, int yStart) {
    int bestX=-1,bestY=-1,bestL=-1;
    for (int x=1;x<=mz.M;++x)
        for (int y:{1,mz.N}) {
            int val=mz.lab[y][x];
            if(val>=2&&val>bestL){bestL=val;bestX=x;bestY=y;}
        }
    for (int y=1;y<=mz.N;++y)
        for (int x:{1,mz.M}) {
            int val=mz.lab[y][x];
            if(val>=2&&val>bestL){bestL=val;bestX=x;bestY=y;}
        }
    vector<Cell> path;
    if(bestL<2)return path;
    int curX=bestX,curY=bestY,curL=bestL;
    path.push_back({curX,curY});
    while(!(curX==xStart&&curY==yStart)){
        bool moved=false;
        for(int k=1;k<=4;++k){
            int nx=curX-CX[k],ny=curY-CY[k];
            if(!inBounds(mz,nx,ny))continue;
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

static vector<int> reconstructRules(const vector<Cell> &nodes) {
    vector<int> rules;
    for (size_t i = 1; i < nodes.size(); ++i) {
        int dx = nodes[i].x - nodes[i-1].x;
        int dy = nodes[i].y - nodes[i-1].y;
        for (int r = 1; r <= 4; ++r)
            if (CX[r] == dx && CY[r] == dy) { rules.push_back(r); break; }
    }
    return rules;
}

static void printRules(const vector<int> &rules) {
    cout << "Rules:\n";
    const int perLine = 10;
    int onLine = 0;
    for (size_t i = 0; i < rules.size(); ++i) {
        if (onLine == 0) cout << "  ";
        ostringstream oss; oss << 'R' << rules[i];
        cout << setw(3) << oss.str();
        onLine++;
        if (onLine == perLine || i + 1 == rules.size()) {
            cout << "\n"; onLine = 0;
        } else cout << ' ';
    }
}

static void printNodes(const vector<Cell> &nodes) {
    cout << "Nodes:\n";
    const int perLine = 10;
    int onLine = 0;
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (onLine == 0) cout << "  ";
        cout << "[X=" << setw(3) << nodes[i].x << ",Y=" << setw(3) << nodes[i].y << "]";
        onLine++;
        if (onLine == perLine || i + 1 == nodes.size()) {
            cout << "\n"; onLine = 0;
        } else cout << ' ';
    }
}

static bool loadMazeFromFile(const string &path, Maze &mz, int &x0, int &y0) {
    ifstream in(path);
    if (!in) return false;
    in >> mz.M >> mz.N;
    if (!in) return false;
    mz.lab.assign(mz.N+1, vector<int>(mz.M+1, 1));
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
        cout << "Error: start outside bounds.\n";
        return rr;
    }
    if (mz.lab[y0][x0] != 0) {
        cout << "Error: start is not free (must be 0).\n";
        return rr;
    }
    DFSContext ctx; ctx.maze = &mz; ctx.variant = variant; ctx.verbose = verbose;
    ctx.L = 2; ctx.trials = 0; ctx.stepNo = 0; ctx.depth = 0; ctx.yes = false;

    cout << "PART 1. Data\n";
    cout << "Maze size: M=" << mz.M << ", N=" << mz.N << "\n";
    cout << "Variant: " << variant << "\n";
    cout << "Start (X,Y): (" << x0 << "," << y0 << ")\n";
    printMaze(mz, "Initial labyrinth:");
    cout << "\n";

    int &startCell = mz.lab[y0][x0]; startCell = ctx.L;
    cout << "Initial position X=" << x0 << ", Y=" << y0 << ". L:=" << ctx.L << ".\n";

    cout << "\nPART 2. Trace\n";
    auto t0 = chrono::steady_clock::now();
    ctx.callStack.push_back({x0, y0});
    ctx.depth = 0;
    tryDfs(ctx, x0, y0);

    int total = ctx.stepNo;
    int width = 1;
    while (total >= 10) { width++; total /= 10; }
    for (int i = 0; i < (int)ctx.traceLines.size(); ++i) {
        cout << setw(width) << (i+1) << ") " << ctx.traceLines[i] << "\n";
    }
    ctx.callStack.pop_back();
    auto t1 = chrono::steady_clock::now();
    rr.pathExists = ctx.yes;
    rr.trials = ctx.trials;
    rr.ms = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();

    cout << "\nPART 3. Results\n";
    if (rr.pathExists) cout << "Path exists\n"; else cout << "Path does not exist\n";
    cout << "Trials: " << rr.trials << "\n";
    cout << "Time (ms): " << rr.ms << "\n";
    printMaze(mz, "Final labyrinth:");
    if (rr.pathExists) {
        rr.pathNodes = reconstructPath(mz, x0, y0);
        rr.ruleSeq = reconstructRules(rr.pathNodes);
        printRules(rr.ruleSeq);
        printNodes(rr.pathNodes);
    }
    return rr;
}

// ------------------ MAIN -------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter path to labyrinth file (e.g., lab1.txt): " << flush;
    string path;
    if (!(cin >> path)) return 0;

    cout << "Select variant (V1 or V2): " << flush;
    string variantStr;
    cin >> variantStr;

    int variant = 1;
    string variantSuffix = "v1";
    if (variantStr == "V1" || variantStr == "v1" || variantStr == "1") {
        variant = 1;
        variantSuffix = "v1";
    } else if (variantStr == "V2" || variantStr == "v2" || variantStr == "2") {
        variant = 2;
        variantSuffix = "v2";
    }

    Maze mz; int x0 = 1, y0 = 1;
    if (!loadMazeFromFile(path, mz, x0, y0)) {
        cerr << "Failed to read file.\n";
        return 0;
    }

    // Crear nombre de fichero de salida
    string baseName = path;
    size_t slashPos = baseName.find_last_of("/\\");
    if (slashPos != string::npos)
        baseName = baseName.substr(slashPos + 1);
    size_t dotPos = baseName.find_last_of(".");
    if (dotPos != string::npos)
        baseName = baseName.substr(0, dotPos);
    string outputFile = "output_" + baseName + "_" + variantSuffix + ".txt";

    ofstream out(outputFile);
    if (!out) {
        cerr << "Cannot open " << outputFile << " for writing.\n";
        return 0;
    }

    // Redirigir cout
    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());

    cout << "Running file '" << path << "' - Variant " << variant << "\n";
    runOnce(mz, x0, y0, variant, true);

    // Restaurar cout
    cout.rdbuf(coutbuf);
    out.close();

    cout << "Results written to " << outputFile << "\n";
    return 0;
}
