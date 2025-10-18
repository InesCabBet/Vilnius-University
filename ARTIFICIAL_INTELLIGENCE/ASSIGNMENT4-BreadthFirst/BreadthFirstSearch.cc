/**
 * VILNIUS UNIVERSITY
 * ARTIFICIAL INTELLIGENCE : CLASSICAL PRINCIPLES
 * @author INES CABRERA BETANCOR
 * @date 04 OCT 2025 
 * @brief Assignment 3 - BFS Version with Wave Format
 */

#include <bits/stdc++.h>
using namespace std;

int w, h, start_x, start_y, MARK; // Maze width, height, start position, and mark value
vector<vector<int>> lab;          // 2D vector representing the maze
vector<pair<int,int>> nodes;      // Nodes visited along the path
vector<int> rules;                // Directions taken to reach the solution

int dx[4] = {-1, 0, 1, 0}; // Left, Down, Right, Up
int dy[4] = {0, -1, 0, 1};

struct Node {
  int x, y, depth, direction;
  Node* parent;
  Node(int x, int y, int depth, int dir, Node* p = nullptr) 
    : x(x), y(y), depth(depth), direction(dir), parent(p) {}
};

/**
 * @brief Checks if a cell (x,y) is inside the maze boundaries
 */
bool is_valid(int x, int y) {
  return (x >= 1 && x <= w && y >= 1 && y <= h);
}

/**
 * @brief Check if a cell (x,y) is on the border of the maze
 */
bool on_border(int x, int y) {
  return x == 1 || y == 1 || x == w || y == h;
}

/**
 * @brief Prints the current maze board to the output file
 */
void print_board(ofstream &out) {
  int max_width = 0;
  for (int y = 1; y <= h; ++y) {
    for (int x = 1; x <= w; ++x) {
      max_width = max(max_width, (int)to_string(lab[y][x]).size());
    }
  }
  int cell_width = max(3, max_width);
  out << "     Y, V\n";
  out << "      ^\n";
  for (int y = h; y >= 1; --y) {
    out << setw(5) << y << " | ";
    for (int x = 1; x <= w; ++x) {
      out << setw(cell_width) << lab[y][x] << " ";
    }
    out << "\n";
  }
  out << "     " << string(w * (cell_width + 1) + 7, '-') << "> X, U \n";
  out << " " << string(7, ' ');
  for (int x = 1; x <= w; ++x) {
    out << setw(cell_width) << x << " ";
  }
  out << "\n";
}

/**
 * @brief Reconstruct path from goal to start
 */
void reconstruct_path(Node* goal) {
  Node* current = goal;
  while (current->parent != nullptr) {
    nodes.push_back({current->x, current->y});
    rules.push_back(current->direction);
    current = current->parent;
  }
}

/**
 * @brief Performs Breadth-First Search (BFS) using wave expansion
 * 
 * Explores the maze starting from the given initial position to find the shortest 
 * path to the nearest border cell. The search expands in waves, marking each cell 
 * with the current wave (depth) level. Each step is logged in a wave-based format 
 * to the output stream.
 * 
 * If a terminal (border) cell is reached, the path is reconstructed by backtracking 
 * from the goal to the starting node using parent pointers. All directions explored 
 * are reported, including whether each neighbor is out of bounds, a wall, visited, 
 * or free.
 * 
 * @param out Output file stream to log the BFS trace
 * @param start_x Starting x-coordinate (1-based)
 * @param start_y Starting y-coordinate (1-based)
 * 
 * @return true if a path to the border is found, false otherwise
 */
bool bfs(ofstream &out, int start_x, int start_y) {
    // Check if start is on border
    if (on_border(start_x, start_y)) {
        out << "WAVE 0, label L=\"2\". Initial position X=" << start_x 
            << ", Y=" << start_y << ", NEWN=1\n";
        out << "Terminal at starting position.\n";
        return true;
    }

    queue<Node*> q;
    Node* start_node = new Node(start_x, start_y, 2, 0, nullptr);
    q.push(start_node);
    
    vector<Node*> all_nodes;
    all_nodes.push_back(start_node);
    
    int newn = 1; // Counter for new nodes
    int close_counter = 1; // Counter for closed nodes
    int current_depth = 2;
    
    // Print initial wave
    out << "WAVE 0, label L=\"" << current_depth << "\". Initial position X=" 
        << start_x << ", Y=" << start_y << ", NEWN=" << newn << "\n";

    queue<Node*> current_wave;
    current_wave.push(start_node);
    
    while (!current_wave.empty()) {
        queue<Node*> next_wave;
        current_depth++;
        
        out << "\nWAVE " << current_depth - 2 << ", label L=\"" << current_depth << "\"\n";
        
        while (!current_wave.empty()) {
            Node* current = current_wave.front();
            current_wave.pop();
            
            out << "   Close CLOSE=" << close_counter++ << ", X=" << current->x 
                << ", Y=" << current->y << ".\n";
            
            // Explore all 4 directions
            for (int direction = 0; direction < 4; ++direction) {
                int nx = current->x + dx[direction];
                int ny = current->y + dy[direction];
                
                out << "      R" << direction + 1 << ". X=" << nx << ", Y=" << ny << ". ";
                
                if (!is_valid(nx, ny)) {
                    out << "Out of bounds.\n";
                    continue;
                }

                int cell = lab[ny][nx];
                
                if (cell == 0) { // Free cell
                    lab[ny][nx] = current_depth;
                    newn++;
                    out << "Free. NEWN=" << newn << ".\n";

                    Node* new_node = new Node(nx, ny, current_depth, direction, current);
                    all_nodes.push_back(new_node);
                    next_wave.push(new_node);
                    
                    if (on_border(nx, ny)) { // Terminal node found
                        out << "      Terminal.\n";
                        reconstruct_path(new_node);
                        
                        // Free memory
                        for (Node* n : all_nodes) delete n;
                        return true;
                    }
                }
                else if (cell == 1) { // Wall
                    out << "Wall.\n";
                }
                else { // Already visited (CLOSED or OPEN)
                    out << "CLOSED or OPEN.\n";
                }
            }
        }
        
        current_wave = next_wave;
    }

    // Free memory
    for (Node* n : all_nodes) delete n;
    return false;
}

/**
 * @brief Read input maze from file
 */
void read_input(const string &filename) {
  ifstream in(filename);
  if (!in.is_open()) {
    cout << "Error. File does not exists.\n";
    exit(1);
  }
  in >> w >> h;
  lab.assign(h + 1, vector<int>(w + 1, 0));
  for (int i = h; i >= 1; --i) {
    for (int j = 1; j <= w; ++j) {
      in >> lab[i][j];
    }
  }
  in >> start_x >> start_y;
  lab[start_y][start_x] = 2;
  in.close();
}

/**
 * @brief Print initial maze and starting position
 */
void part1(ofstream &out) {
  out << "PART 1. Data\n";
  out << "   1.1. Labyrinth\n\n";
  print_board(out);
  out << "\n   1.2. Initial position X=" << start_x << ", Y=" << start_y << ". L=2.\n\n";
}

/**
 * @brief Print DFS results, path, rules and visited nodes
 */
void part3(ofstream &out, bool found) {
  out << "\nPART 3. Results\n";
  if (!found) {
    out << "   3.1 Path is not found\n";
    return;
  }
  out << "   3.1 Path is found\n";
  out << "   3.2 Path graphically\n\n";
  print_board(out);
  // --- Rules ---
  out << "\n   3.3. Rules: ";
  if (!rules.empty()) {
    int count = 0;
    string indent = string(15, ' '); // Alinea debajo de "Rules:"
    for (int i = (int)rules.size() - 1; i >= 0; --i) {
      out << "R" << rules[i] + 1 << " ";
      count++;
      if (count % 10 == 0 && i != 0)
        out << "\n" << indent;
    }
    out << "\n\n";
  } else out << "(none)\n\n";
    // --- Nodes ---
    out << "   3.4. Nodes: ";
    if (!nodes.empty()) {
      int count = 0;
      string indent = string(15, ' '); // Alinea debajo de "Nodes:"
      for (int i = (int)nodes.size() - 1; i >= 0; --i) {
        out << "[X=" << nodes[i].first << ",Y=" << nodes[i].second << "] ";
        count++;
        if (count % 10 == 0 && i != 0)
          out << "\n" << indent;
      }
    out << "\n";
  } else out << "(none)\n";
}

int main() {
  string input_file;
  cout << "Enter the input filename: ";
  cin >> input_file;  
  ifstream in(input_file);
  if (!in.is_open()) {
    cout << "Error. File does not exists.\n";
    return 1;
  }
  in.close();
  string output_file = "output_" + input_file.substr(0, input_file.size() - 4) + ".txt";
  ofstream out(output_file);
  if (!out.is_open()) {
    cerr << "Error: cannot open output file.\n";
    return 1;
  }
  read_input(input_file);
  part1(out);
  out << "PART 2. Trace\n";
  nodes.clear();
  rules.clear();
  bool found = bfs(out, start_x, start_y);
  nodes.push_back({start_x, start_y});
  part3(out, found);
  out.close();
  cout << "Output written to " << output_file << endl;
  return 0;
}