#include <iostream>
#include <vector>
#include <utility>
#include <queue>
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
    //gp.dfs(0,7,0);
    gp.ucs(0,7);

    return 0;
}



