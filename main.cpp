#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Graph.h"
#include "GraphVisualization.h"

int main() {
    Graph g1 = Graph("data/data1/");
    g1.readGraphBFS("UIUC");

    cout << "Creating Visualization class" << endl;
    GraphVisualization visual = GraphVisualization(25000, 25000, g1.getMaxConnection(), "InterFontCharacters/");

    cout << "Constructing Simulator" << endl;
    PhysicSimulation sim = PhysicSimulation();

    cout << "Initiating Simulator" << endl;;
    sim.initiateGraph(g1);

    cout << "Starting Simulation" << endl;
    map<Graph::SubReddit*, pair<float, float>> positions = sim.simulateFor(2000);

    cout << "Converting Coordinates" << endl;
    map<Graph::SubReddit*, pair<int, int>> convertedCoords = visual.convertCoordinates(positions);

    cout << "Drawing Graph" << endl;
    cs225::PNG* image = visual.drawGraph(convertedCoords);

    image->writeToFile("full_output.png");


    Graph g2 = Graph("data/data2/");
    g2.readGraphBFS("UIUC");
    g2.BFSToFile();
    map <string, double> dijkstra = g2.dijkstra("UIUC");
    // map <string, double> badDijkstra = g.badDijkstra("UIUC");
    vector<pair<string, double>> v = vector<pair<string, double>>();
    for (auto itr : dijkstra) {
        v.push_back(std::make_pair(itr.first, itr.second));
    }
    
    struct lessthan {
        inline bool operator() (const pair<string, double>& p1, const pair<string, double>& p2) {
            if (p1.second == -1) {
                return false;
            }
            if (p2.second == -1) {
                return true;
            }
            return (p1.second < p2.second);
        }
    };

    std::sort(v.begin(), v.end(), lessthan());

    ofstream Dijkstra("DijkstraResult.txt");
    for(auto itr : v) {
        Dijkstra << itr.first << " " << itr.second << '\n';
    }
    
    return 0;
}