#include <iostream>
#include <vector>
#include <utility>

class Graph {
    int vnum;
    std::vector<bool> visited;
    std::vector<int> path;
    std::vector<std::vector<std::pair<int, int> > > adj;
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
        std::cout << "Encontrado! \nCamino: ";
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
    *   0 A
    *   1 B
    *   2 C
    *   3 D
    *   4 E
    *   5 F
    *   6 G
    *   7 H
    */
    Graph gp(8);
    gp.addEdge(0,1,11);
    gp.addEdge(0,2,6);
    gp.addEdge(1,3,4);
    gp.addEdge(1,4,3);
    gp.addEdge(2,5,3);
    gp.addEdge(2,4,10);
    gp.addEdge(3,7,3);
    gp.addEdge(4,7,5);
    gp.addEdge(5,6,1);
    gp.addEdge(6,4,4);

    //gp.printSelf();
    gp.dfs(0,7,0);

    return 0;
}



