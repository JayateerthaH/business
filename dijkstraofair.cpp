#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max()

class AirQualityMonitoring {
public:
    int numStations; // Number of monitoring stations
    vector<vector<pair<int, int>>> graph; // Adjacency list (station, weight)
    map<string, int> stationToIndex; // Maps station name to index
    map<int, string> indexToStation; // Maps index to station name

    AirQualityMonitoring() : numStations(0) {}

    void addStation(const string& name) {
        if (stationToIndex.find(name) == stationToIndex.end()) {
            stationToIndex[name] = numStations;
            indexToStation[numStations] = name;
            graph.push_back({});
            numStations++;
        }
    }

    void addConnection(const string& stationA, const string& stationB, int weight) {
        addStation(stationA);
        addStation(stationB);
        int indexA = stationToIndex[stationA];
        int indexB = stationToIndex[stationB];
        graph[indexA].push_back({indexB, weight});
        graph[indexB].push_back({indexA, weight}); // Assuming undirected graph
    }

    vector<int> dijkstra(const string& startStation) {
        if (stationToIndex.find(startStation) == stationToIndex.end()) {
            cout << "Error: Station not found.\n";
            return {};
        }

        int startIndex = stationToIndex[startStation];
        vector<int> dist(numStations, INF);
        vector<bool> visited(numStations, false);
        dist[startIndex] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, startIndex});

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (visited[currentNode]) continue;
            visited[currentNode] = true;

            for (const auto& neighbor : graph[currentNode]) {
                int neighborNode = neighbor.first;
                int edgeWeight = neighbor.second;

                if (currentDist + edgeWeight < dist[neighborNode]) {
                    dist[neighborNode] = currentDist + edgeWeight;
                    pq.push({dist[neighborNode], neighborNode});
                }
            }
        }

        return dist;
    }

    void printShortestPaths(const string& startStation) {
        vector<int> distances = dijkstra(startStation);
        if (distances.empty()) return;

        cout << "Shortest paths from " << startStation << ":\n";
        for (int i = 0; i < numStations; i++) {
            cout << "To " << indexToStation[i] << ": ";
            if (distances[i] == INF) {
                cout << "Unreachable\n";
            } else {
                cout << distances[i] << "\n";
            }
        }
    }
};

int main() {
    AirQualityMonitoring aqMonitor;

    // Example graph representing stations and connections
    aqMonitor.addConnection("Station1", "Station2", 10);
    aqMonitor.addConnection("Station1", "Station3", 15);
    aqMonitor.addConnection("Station2", "Station4", 12);
    aqMonitor.addConnection("Station3", "Station4", 10);
    aqMonitor.addConnection("Station4", "Station5", 5);

    // Printing shortest paths from a specific station
    string startStation;
    cout << "Enter the starting station: ";
    cin >> startStation;
    aqMonitor.printShortestPaths(startStation);

    return 0;
}
