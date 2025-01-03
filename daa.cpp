#include <bits/stdc++.h>
using namespace std;

// Define a structure for edges
struct Edge {
    int to, weight;
};

// Define a structure for graph nodes
struct Node {
    int id, distance;
    bool operator>(const Node &other) const {
        return distance > other.distance;
    }
};

// Graph class
class Graph {
    int numNodes;
    vector<vector<Edge>> adjList;

public:
    Graph(int nodes) : numNodes(nodes), adjList(nodes) {}

    void addEdge(int from, int to, int weight) {
        adjList[from].push_back({to, weight});
        adjList[to].push_back({from, weight}); // Undirected graph
    }

    vector<int> dijkstra(int start) {
        vector<int> dist(numNodes, INT_MAX);
        priority_queue<Node, vector<Node>, greater<Node>> pq;

        dist[start] = 0;
        pq.push({start, 0});

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            for (const Edge &edge : adjList[current.id]) {
                int newDist = current.distance + edge.weight;
                if (newDist < dist[edge.to]) {
                    dist[edge.to] = newDist;
                    pq.push({edge.to, newDist});
                }
            }
        }

        return dist;
    }

    int findNearest(int start, const vector<int> &targets) {
        vector<int> dist = dijkstra(start);
        int nearest = -1, minDist = INT_MAX;

        for (int target : targets) {
            if (dist[target] < minDist) {
                minDist = dist[target];
                nearest = target;
            }
        }

        return nearest;
    }

    void minimumSpanningTree() {
        vector<bool> inMST(numNodes, false);
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        vector<Edge> edges;

        inMST[0] = true;
        for (const Edge &edge : adjList[0]) {
            pq.push(edge);
        }

        while (!pq.empty()) {
            Edge current = pq.top();
            pq.pop();

            if (!inMST[current.to]) {
                inMST[current.to] = true;
                edges.push_back(current);

                for (const Edge &edge : adjList[current.to]) {
                    if (!inMST[edge.to]) {
                        pq.push(edge);
                    }
                }
            }
        }

        cout << "Minimum Spanning Tree Edges:\n";
        for (const Edge &edge : edges) {
            cout << edge.to << " - " << edge.weight << endl;
        }
    }
};

int main() {
    int numLocations = 6;
    Graph cityGraph(numLocations);

    cityGraph.addEdge(0, 1, 4);
    cityGraph.addEdge(0, 2, 2);
    cityGraph.addEdge(1, 2, 1);
    cityGraph.addEdge(1, 3, 5);
    cityGraph.addEdge(2, 3, 8);
    cityGraph.addEdge(3, 4, 6);
    cityGraph.addEdge(4, 5, 3);

    vector<int> petrolPumps = {2, 5};
    vector<int> busStands = {1, 4};

    int start = 0;
    vector<int> distances = cityGraph.dijkstra(start);

    cout << "Shortest distances from location " << start << ":\n";
    for (int i = 0; i < distances.size(); i++) {
        cout << "To " << i << ": " << distances[i] << endl;
    }

    int nearestPetrolPump = cityGraph.findNearest(start, petrolPumps);
    int nearestBusStand = cityGraph.findNearest(start, busStands);

    cout << "Nearest Petrol Pump: " << nearestPetrolPump << endl;
    cout << "Nearest Bus Stand: " << nearestBusStand << endl;

    cityGraph.minimumSpanningTree();

    return 0;
}
