#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Graph {
    int vnum;
    std::vector<bool> visited;
    std::vector<int> path;
    std::vector<std::vector<std::pair<int, int> > > adj;
    std::srand(std::time(NULL));
public:
    Graph(int _vnum) : vnum(_vnum), adj(_vnum), visited(_vnum, false) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v,w});
    }
    int dfs(int vx, int obj, int current_cost) {
        path.push_back(vx);
        visited[vx] = true;
        if (vx == obj) {
            printStats(current_cost);
            return current_cost;
        }
        
        for (int i = 0; i < adj[vx].size(); i++) {
            if (!visited[adj[vx][i].first]) {
                int path_cost = dfs(adj[vx][i].first, obj, current_cost + adj[vx][i].second);
                if (path_cost != -1) {
                    return path_cost;
                }
            }
        }
        path.pop_back(); 
        return -1; 
    }
    void printStats(int cost) {
        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i < path.size() - 1) std::cout << " -> ";
        }
        std::cout << "\nCosto: " << cost << "\n";
    }
    void printSelf() {
        for (int i = 0; i < adj.size(); i++) {
            for (int j = 0; j < adj[i].size(); j++) {
                std::cout << i << " " << adj[i][j].first << " " << adj[i][j].second << "\n";
            }
        }
    }
};

int main() {
    /*
    *   Se lee el archivo test.txt, donde los nodos son representados con numeros empezando con el A = 0 hasta el H = 7
    */
    std::ifstream myfile("test.txt"); 
    
    if (myfile.is_open()) {
        std::string line;
        getline(myfile, line); 
        int init = stoi(line.substr(5)); 
        
        getline(myfile, line); 
        int goal = stoi(line.substr(5)); 
        
        std::vector<std::pair<int, int>> nodes; 
        std::vector<std::vector<int>> abc_values; 
        
        while (getline(myfile, line)) { 
            if (line.find(',') != std::string::npos) { 
                int a, b, c;
                sscanf(line.c_str(), "%d,%d,%d", &a, &b, &c); 
                abc_values.push_back({a,b,c});
            } else { 
                int index, value;
                sscanf(line.c_str(), "%d %d", &index, &value); 
                nodes.push_back({index, value}); 
            }
        }
        
        myfile.close(); 

        Graph gp(nodes.size());
        
        for (int i = 0; i < abc_values.size(); i++) {
            gp.addEdge(abc_values[i][0], abc_values[i][1], abc_values[i][2]);
        }
        gp.dfs(init,goal,0);
        
    } else {
        std::cout << "No se puede abrir el archivo" << "\n"; 
    }
    
    return 0;
}


