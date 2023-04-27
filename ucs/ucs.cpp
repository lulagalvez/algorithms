#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <fstream>
#include <algorithm>

class Graph {
    int vnum;
    std::vector<bool> visited;
    std::vector<int> parents;
    std::vector<std::vector<std::pair<int, int> > > adj;

public:
    Graph(int _vnum) : vnum(_vnum), adj(_vnum), visited(_vnum, false), parents(_vnum) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v,w});
    }

    void ucs(int start, int goal) {
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>> > pq;

        pq.push({0,start});
        parents[start] = -1;

        while (!pq.empty()) {

            std::pair<int,int> p = pq.top();
            pq.pop();

            if (p.second == goal) {
                std::vector<int> path;
                int current = goal;
                while (current != -1) {
                    path.push_back(current);
                    current = parents[current];
                }
                std::reverse(path.begin(), path.end());
                
                std::cout << "Found node: " << p.second << " with cost: " << p.first << "\n";
                for (int node : path) {
                    std::cout << node << " ";
                }
                std::cout << std::endl;
                return;
            }
            if (!visited[p.second]) {
                for (int i = 0; i < adj[p.second].size(); i++) {
                    std::pair<int,int> child;
                    child.first = adj[p.second][i].second;
                    child.second = adj[p.second][i].first;
                    parents[child.second] = p.second;
                    pq.push({p.first + child.first, child.second});
			    }
            }
			visited[p.second] = true;
        }
        return;
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
        gp.ucs(init,goal);
        
    } else {
        std::cout << "No se puede abrir el archivo" << "\n"; 
    }
    
    return 0;
}
