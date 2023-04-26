#include <iostream>
#include <vector>
#include <utility>
#include <queue>
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

    gp.addHeuristic(0,10);
    gp.addHeuristic(1,7);
    gp.addHeuristic(2,10);
    gp.addHeuristic(3,3);
    gp.addHeuristic(4,1);
    gp.addHeuristic(5,2);
    gp.addHeuristic(6,2);
    gp.addHeuristic(7,0);

    //gp.printSelf();
    //gp.dfs(0,7,0);
    //gp.ucs(0,7);
    gp.greedySearch(0,7);

    return 0;
}



