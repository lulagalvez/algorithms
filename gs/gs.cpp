#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <fstream>
#include <algorithm>

class Graph {
    int vnum;
    std::vector<bool> visited;
    std::vector<int> path;
    std::vector<std::vector<std::pair<int, int> > > adj;
    std::vector<int> hrst;

public:
    Graph(int _vnum) : vnum(_vnum), adj(_vnum), visited(_vnum, false), hrst(_vnum) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v,w});
    }

    void addHeuristic(int node, int heuristic) {
        hrst[node] = heuristic;
    }

    void greedySearch(int start, int goal) {
        int cost = 0;
        int currentNode = start;
        while (true) {
            path.push_back(currentNode);
            if (adj[currentNode].empty()) {
                printStats(cost);
                return;
            }
            int min = adj[currentNode][0].first;
            int pos = 0;
            for (int i = 1; i < adj[currentNode].size(); i++) {
                if (hrst[min] > hrst[adj[currentNode][i].first]) {
                    min = adj[currentNode][i].first;
                    pos = i;
                }
            }
            cost += adj[currentNode][pos].second;
            currentNode = min;
        }
    }
    void printStats(int cost) {
        std::cout << "Encontrado! \nCamino: ";
        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i < path.size() - 1) std::cout << " -> ";
        }
        std::cout << "\nCosto: " << cost << "\n";
    }
    


};

int main() {
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
        
        for (int i = 0; i < nodes.size(); i++) {
            gp.addHeuristic(nodes[i].first, nodes[i].second);
        }
        for (int i = 0; i < abc_values.size(); i++) {
            gp.addEdge(abc_values[i][0], abc_values[i][1], abc_values[i][2]);
        }
        gp.greedySearch(init,goal);
        
    } else {
        std::cout << "No se puede abrir el archivo" << "\n"; 
    }
    
    return 0;
}


