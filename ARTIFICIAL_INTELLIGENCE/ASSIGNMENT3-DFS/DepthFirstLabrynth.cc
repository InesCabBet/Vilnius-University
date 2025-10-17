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
	int M{0}; // columns (X)
	int N{0}; // rows (Y)
	vector<vector<int>> lab; // 1..M, 1..N via 1-based indexing (we will allocate N+1 by M+1)
};

// Resultado de una ejecución: existencia de camino, intentos, ms, nodos y reglas
struct RunResult {
	bool pathExists{false};
	long long trials{0};
	long long ms{0};
	vector<Cell> pathNodes; // in order from start to exit
	vector<int> ruleSeq; // R1..R4 along final path
};

// Desplazamientos cardinales: índices 1..4 mapean a (W,S,E,N)
static const int CX[5] = {0, -1, 0, 1, 0}; // 1..4: W,S,E,N
static const int CY[5] = {0, 0, -1, 0, 1};

// Contexto del DFS para traza, conteo de pruebas y control de variante
struct DFSContext {
	Maze *maze;
	int variant{1};
	int L{2};
	long long trials{0};
	int stepNo{0};
	bool verbose{true};
	bool yes{false};
	int depth{0};
	vector<Cell> callStack; // track current recursion stack (cells)
	vector<string> traceLines; // líneas de traza (sin número de paso)
};

// Comprueba si (x,y) está dentro de los límites del laberinto
static inline bool inBounds(const Maze &mz, int x, int y) {
	return x >= 1 && x <= mz.M && y >= 1 && y <= mz.N;
}

// Imprime guiones para visualizar el nivel de recursión en la traza
static void printIndent(int depth) {
	for (int i = 0; i < depth; ++i) cout << "-";
}

// Traza: explorar celda libre (se incrementa L y se marca la celda)
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

// Traza: celda es pared
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

// Traza: celda ya visitada/hilo (>=2 o -1)
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

// Traza: se alcanza una celda terminal (en el borde)
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

// Traza: backtracking; variante 1 marca -1 (cerrado), variante 2 restaura a 0
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

// DFS recursivo: intenta encontrar salida llegando al borde
static void tryDfs(DFSContext &ctx, int x, int y) {
	if (ctx.yes) return;
	// Caso terminal: si (x,y) está en el borde, hay salida
	if (x == 1 || x == ctx.maze->M || y == 1 || y == ctx.maze->N) {
		printTerminal(ctx, x, y);
		ctx.yes = true;
		return;
	}

	for (int k = 1; k <= 4 && !ctx.yes; ++k) {
		int u = x + CX[k];
		int v = y + CY[k];
		if (!inBounds(*ctx.maze, u, v)) continue; // fuera de límites => como pared
		int &cell = ctx.maze->lab[v][u]; // note [y][x]
		if (cell == 0) {
			// Celda libre: explorar y profundizar
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
				int newVal = (ctx.variant == 1 ? -1 : 0); // marcar cerrado o restaurar
				cell = newVal;
				printBacktrack(ctx, u, v, ctx.L, newVal);
				ctx.L--;
			} else {
				return; // success propagate
			}
		} else if (cell == 1) {
			printWall(ctx, k, u, v); // pared
		} else {
			printThread(ctx, k, u, v); // ya visitada / hilo
		}
	}
}

// Imprime el laberinto final tras la ejecución (de arriba hacia abajo)
static void printMazeFinal(const Maze &mz) {
	cout << "Final labyrinth:\n";
	for (int y = mz.N; y >= 1; --y) {
		for (int x = 1; x <= mz.M; ++x) {
			if (x > 1) cout << ' ';
			cout << mz.lab[y][x];
		}
		cout << "\n";
	}
}

// Imprime un laberinto con ejes y valores alineados (como el ejemplo)
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

// Reconstruye el camino desde la celda terminal con mayor L en el borde
static vector<Cell> reconstructPath(const Maze &mz, int xStart, int yStart) {
	// Buscar en el borde la mayor L alcanzada (lab>=2)
	int bestX = -1, bestY = -1, bestL = -1;
	for (int x = 1; x <= mz.M; ++x) {
		for (int y : {1, mz.N}) {
			int val = mz.lab[y][x];
			if (val >= 2 && val > bestL) { bestL = val; bestX = x; bestY = y; }
		}
	}
	for (int y = 1; y <= mz.N; ++y) {
		for (int x : {1, mz.M}) {
			int val = mz.lab[y][x];
			if (val >= 2 && val > bestL) { bestL = val; bestX = x; bestY = y; }
		}
	}
	vector<Cell> path;
	if (bestL < 2) return path;
	int curX = bestX, curY = bestY, curL = bestL;
	path.push_back({curX, curY});
	while (!(curX == xStart && curY == yStart)) {
		bool moved = false;
		for (int k = 1; k <= 4; ++k) {
			int nx = curX - CX[k];
			int ny = curY - CY[k];
			if (!inBounds(mz, nx, ny)) continue;
			int val = mz.lab[ny][nx];
			if (val == curL - 1 && val >= 2) {
				curX = nx; curY = ny; curL = val; path.push_back({curX, curY});
				moved = true; break;
			}
		}
		if (!moved) break; // no se puede reconstruir más
	}
	reverse(path.begin(), path.end());
	return path;
}

// Traduce la secuencia de nodos a reglas R1..R4 según delta (dx,dy)
static vector<int> reconstructRules(const vector<Cell> &nodes) {
	vector<int> rules;
	for (size_t i = 1; i < nodes.size(); ++i) {
		int dx = nodes[i].x - nodes[i-1].x;
		int dy = nodes[i].y - nodes[i-1].y;
		// Map to rule index: CX[rule], CY[rule]
		for (int r = 1; r <= 4; ++r) {
			if (CX[r] == dx && CY[r] == dy) { rules.push_back(r); break; }
		}
	}
	return rules;
}

// Imprime la secuencia de reglas del camino
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
			cout << "\n";
			onLine = 0;
		} else {
			cout << ' ';
		}
	}
}

// Imprime la secuencia de nodos (coordenadas) del camino
static void printNodes(const vector<Cell> &nodes) {
	cout << "Nodes:\n";
	const int perLine = 10;
	int onLine = 0;
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (onLine == 0) cout << "  ";
		cout << "[X=" << setw(3) << nodes[i].x << ",Y=" << setw(3) << nodes[i].y << "]";
		onLine++;
		if (onLine == perLine || i + 1 == nodes.size()) {
			cout << "\n";
			onLine = 0;
		} else {
			cout << ' ';
		}
	}
}

// Laberinto de prueba 1 (7x7) fijo
static Maze makeTest1() {
	// 7x7 from sample. Coordinate system: 1-based, lab[y][x]
	Maze mz; mz.M = 7; mz.N = 7; mz.lab.assign(mz.N+1, vector<int>(mz.M+1, 1));
	int a[7][7] = {
		{1,1,1,1,1,1,1},
		{1,0,0,0,1,1,1},
		{1,0,1,0,1,1,1},
		{1,0,0,0,0,1,1},
		{1,1,1,1,0,1,1},
		{0,0,0,0,0,0,0},
		{1,1,1,1,1,0,1}
	};
	for (int y = 1; y <= 7; ++y)
		for (int x = 1; x <= 7; ++x)
			mz.lab[y][x] = a[y-1][x-1];
	return mz;
}

// Laberinto de prueba 2 (17x9) fijo
static Maze makeTest2() {
	// 17x9 from figure 7.5 (example placeholder; user should adjust to exact exercise matrix if different)
	Maze mz; mz.M = 17; mz.N = 9; mz.lab.assign(mz.N+1, vector<int>(mz.M+1, 1));
	vector<vector<int>> a = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
		{1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,0,1},
		{1,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,1},
		{1,0,1,0,1,1,0,1,1,1,0,1,0,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	for (int y = 1; y <= mz.N; ++y)
		for (int x = 1; x <= mz.M; ++x)
			mz.lab[y][x] = a[y-1][x-1];
	return mz;
}

// Carga laberinto desde archivo de texto: M N, luego N filas con M enteros; opcional x0 y0
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

// Genera laberinto aleatorio con probabilidad de celdas libres y "islas" rodeadas
static Maze generateRandomMaze(int M, int N, int seed, int islandsTarget) {
	Maze mz; mz.M = M; mz.N = N; mz.lab.assign(N+1, vector<int>(M+1, 1));
	mt19937 rng(seed);
	uniform_int_distribution<int> d(0, 99);
	for (int y = 2; y < N; ++y) {
		for (int x = 2; x < M; ++x) {
			mz.lab[y][x] = (d(rng) < 60 ? 0 : 1); // 60% free
		}
	}
	// Crear "islas": grupos libres rodeados de paredes para aumentar complejidad
	for (int k = 0; k < islandsTarget; ++k) {
		int cx = 2 + (rng() % (M-3));
		int cy = 2 + (rng() % (N-3));
		for (int yy = cy-1; yy <= cy+1; ++yy)
			for (int xx = cx-1; xx <= cx+1; ++xx)
				mz.lab[yy][xx] = 0;
		for (int yy = cy-2; yy <= cy+2; ++yy)
			for (int xx = cx-2; xx <= cx+2; ++xx)
				if (inBounds(mz, xx, yy)) if (xx==cx-2||xx==cx+2||yy==cy-2||yy==cy+2) mz.lab[yy][xx] = 1;
	}
	return mz;
}

// Ejecuta una vez el algoritmo desde (x0,y0) con la variante dada
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
	DFSContext ctx; ctx.maze = &mz; ctx.variant = variant; ctx.verbose = verbose; ctx.L = 2; ctx.trials = 0; ctx.stepNo = 0; ctx.depth = 0; ctx.yes = false;
    // PART 1. Data
    cout << "PART 1. Data\n";
    cout << "Maze size: M=" << mz.M << ", N=" << mz.N << "\n";
    cout << "Variant: " << variant << "\n";
    cout << "Start (X,Y): (" << x0 << "," << y0 << ")\n";
    // Mostrar el laberinto inicial ANTES de modificar celdas
    printMaze(mz, "Initial labyrinth:");
    cout << "\n";
	// Marcar inicio y anunciarlo
	int &startCell = mz.lab[y0][x0]; startCell = ctx.L; // mark start with 2
	cout << "Initial position X=" << x0 << ", Y=" << y0 << ". L:=" << ctx.L << ".\n";
    // PART 2. Trace
    cout << "\nPART 2. Trace\n";
	auto t0 = chrono::steady_clock::now();
	ctx.callStack.push_back({x0, y0});
	ctx.depth = 0;
    tryDfs(ctx, x0, y0);
    // imprimir traza con ancho dinámico según número de pasos
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
    // PART 3. Results
    cout << "\nPART 3. Results\n";
    if (rr.pathExists) cout << "Path exists\n"; else cout << "Path does not exist\n";
    cout << "Trials: " << rr.trials << "\n";
    cout << "Time (ms): " << rr.ms << "\n";
	// 3) Mostrar el laberinto final tras la búsqueda
	printMaze(mz, "Final labyrinth:");
	if (rr.pathExists) {
		rr.pathNodes = reconstructPath(mz, x0, y0);
		rr.ruleSeq = reconstructRules(rr.pathNodes);
		printRules(rr.ruleSeq);
		printNodes(rr.pathNodes);
	}
	return rr;
}

// Programa principal: menú para seleccionar prueba y variante
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << "Enter path to labyrinth file (e.g., lab1.txt): " << flush;
	string path; if (!(cin >> path)) return 0;
	cout << "Select variant (V1 or V2): " << flush;
	string variantStr; cin >> variantStr;
	int variant = 1;
	if (variantStr == "V1" || variantStr == "v1" || variantStr == "1") variant = 1;
	else if (variantStr == "V2" || variantStr == "v2" || variantStr == "2") variant = 2;
    Maze mz; int x0 = 1, y0 = 1;
    if (!loadMazeFromFile(path, mz, x0, y0)) {
        cout << "Failed to read file.\n";
        return 0;
    }
    cout << "Running file '" << path << "' - Variant " << variant << "\n";
    runOnce(mz, x0, y0, variant, true);
    return 0;
}