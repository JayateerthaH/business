#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <sstream>

using namespace std;

#define INF INT_MAX / 2

class DijkstraWithHeap {
public:
    int totalNodes; // Total number of nodes in the graph
    vector<int> distances, predecessors, visited; // Distance, predecessor, and visited status arrays
    int sourceIndex, currentNode; // Source index and current node
    vector<vector<int>> adjacencyMatrix; // Cost matrix
    map<string, int> nameToIndex; // Map node names to indices
    map<int, string> indexToName; // Map indices to node names

    // Method to input the graph data manually
    void loadGraph() {
        int numEdges;
        cout << "Enter number of edges: ";
        cin >> numEdges;

        for (int i = 0; i < numEdges; ++i) {
            string nodeStart, nodeEnd;
            int edgeWeight;

            cout << "Enter edge " << i + 1 << " (start_node, end_node, weight): ";
            cin >> nodeStart >> nodeEnd >> edgeWeight;

            // Add the nodes if they are not already present
            if (nameToIndex.find(nodeStart) == nameToIndex.end()) {
                nameToIndex[nodeStart] = totalNodes;
                indexToName[totalNodes] = nodeStart;
                totalNodes++;
                adjacencyMatrix.resize(totalNodes);
                for (int j = 0; j < totalNodes; ++j) {
                    adjacencyMatrix[j].resize(totalNodes, INF);
                }
            }
            if (nameToIndex.find(nodeEnd) == nameToIndex.end()) {
                nameToIndex[nodeEnd] = totalNodes;
                indexToName[totalNodes] = nodeEnd;
                totalNodes++;
                adjacencyMatrix.resize(totalNodes);
                for (int j = 0; j < totalNodes; ++j) {
                    adjacencyMatrix[j].resize(totalNodes, INF);
                }
            }

            adjacencyMatrix[nameToIndex[nodeStart]][nameToIndex[nodeEnd]] = edgeWeight;
            adjacencyMatrix[nameToIndex[nodeEnd]][nameToIndex[nodeStart]] = edgeWeight;
        }
    }

    void initialize() {
        visited.resize(totalNodes, 0);

        cout << "Enter source node: ";
        string sourceName;
        cin >> sourceName;

        if (nameToIndex.find(sourceName) == nameToIndex.end()) {
            cout << "Error: Source node not found." << endl;
            return;
        }

        sourceIndex = nameToIndex[sourceName];
        visited[sourceIndex] = 1;

        predecessors.resize(totalNodes);
        distances.resize(totalNodes, INF);
        distances[sourceIndex] = 0;

        for (int i = 0; i < totalNodes; i++) {
            predecessors[i] = sourceIndex;
        }

        currentNode = sourceIndex;
    }

    void calculateShortestPaths() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        minHeap.push({0, sourceIndex});

        while (!minHeap.empty()) {
            int distanceToCurrent = minHeap.top().first;
            int current = minHeap.top().second;
            minHeap.pop();

            if (visited[current]) continue;
            visited[current] = 1;

            for (int neighbor = 0; neighbor < totalNodes; neighbor++) {
                if (!visited[neighbor] && adjacencyMatrix[current][neighbor] != INF &&
                    distanceToCurrent + adjacencyMatrix[current][neighbor] < distances[neighbor]) {

                    distances[neighbor] = distanceToCurrent + adjacencyMatrix[current][neighbor];
                    predecessors[neighbor] = current;
                    minHeap.push({distances[neighbor], neighbor});
                }
            }
        }
    }

    void printShortestPath(int destinationIndex) {
        vector<int> path;
        for (int current = destinationIndex; current != sourceIndex; current = predecessors[current]) {
            path.push_back(current);
        }
        path.push_back(sourceIndex);

        for (int i = path.size() - 1; i > 0; i--) {
            cout << indexToName[path[i]] << " -> ";
        }
        cout << indexToName[path[0]] << "\tTotal cost: " << distances[destinationIndex] << endl;
    }

    void showAllReachableNodes() {
        cout << "Reachable Nodes from " << indexToName[sourceIndex] << ":\n";
        for (int i = 0; i < totalNodes; i++) {
            if (distances[i] != INF) {
                cout << indexToName[i] << " (Distance: " << distances[i] << ")\n";
            }
        }
    }
};

int main() {
    DijkstraWithHeap algorithm;

    algorithm.loadGraph(); // Load graph interactively

    algorithm.initialize();
    algorithm.calculateShortestPaths();

    algorithm.showAllReachableNodes();

    cout << "\nShortest Paths:\n";
    for (int i = 0; i < algorithm.totalNodes; i++) {
        if (i != algorithm.sourceIndex) {
            cout << "To " << algorithm.indexToName[i] << ": ";
            algorithm.printShortestPath(i);
        }
    }

    return 0;
}
