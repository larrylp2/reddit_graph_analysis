#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Graph.h"
#include "GraphVisualization.h"

int main() {
    Graph g = Graph("data/data1/");
    g.readGraphBFS("UIUC");

    cout << "Creating Visualization class" << endl;
    GraphVisualization visual = GraphVisualization(25000, 25000, g.getMaxConnection(), "InterFontCharacters/");

    cout << "Constructing Simulator" << endl;
    PhysicSimulation sim = PhysicSimulation(.5, 1);

    cout << "Initiating Simulator" << endl;;
    sim.initiateGraph(g);

    cout << "Starting Simulation" << endl;
    map<Graph::SubReddit*, pair<float, float>> positions = sim.simulateFor(100000);

    cout << "Converting Coordinates" << endl;
    map<Graph::SubReddit*, pair<int, int>> convertedCoords = visual.convertCoordinates(positions);

    cout << "Drawing Graph" << endl;
    cs225::PNG* image = visual.drawGraph(convertedCoords);

    image->writeToFile("full_output.png");
    
    // std::cout << "Compile Worked" << std::endl;

    // std::string file_path = "data-fetching/data/";
    
    // Graph builder = Graph(file_path);

    // builder.readGraphBFS("UIUC");

    // std::cout << "Users: " << builder.getUsers() << std::endl;;

    // std::cout << "Subs: " << builder.getSubs() << std::endl;

    // builder.printMaxConnection();

    // builder.BFSToFile();

    // // std::cout << builder.dijkstra("UIUC", "AskReddit");

    // Don't do tests in main.cpp lol
    /*
    Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";
    
    std::map<Graph::SubReddit*, int> adj2;
    adj2.insert({cs, 1});

    Graph::SubReddit* one = new Graph::SubReddit();
    one->name = "long-Sub_Name12344";
    std::map<Graph::SubReddit*, int> adj3;
    adj3.insert({cs, 1});

    Graph::SubReddit* two = new Graph::SubReddit();
    two->name = "two";
    std::map<Graph::SubReddit*, int> adj4;
    adj4.insert({cs, 1});

    Graph::SubReddit* three = new Graph::SubReddit();
    three->name = "three";
    std::map<Graph::SubReddit*, int> adj5;
    adj5.insert({cs, 1});
    adj5.insert({two, 1});
    adj4.insert({three, 1});

    std::map<Graph::SubReddit*, int> adj;
    adj.insert({uiuc, 1});
    adj.insert({one, 1});
    adj.insert({two, 1});
    adj.insert({three, 1});

    cs->adjacent = adj;
    uiuc->adjacent = adj2;
    one->adjacent = adj3;
    two->adjacent = adj4;
    three->adjacent = adj5;


    std::pair<int, int> position1(3000, 700);
    std::pair<int ,int> position2(750, 2680);
    std::pair<int ,int> position3(400, 300);
    std::pair<int ,int> position4(3000, 3000);
    std::pair<int ,int> position5(2000, 200);


    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(one, position3));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(two, position4));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(three, position5));

    GraphVisualization visual = GraphVisualization(4000, 4000, 4, "InterFontCharacters/");

    cs225::PNG* drawing = visual.drawGraph(redditCoords);
    drawing->writeToFile("smallVisualizerTestOutput.png");

    Graph g = Graph("data/data2/");
    g.readGraphBFS("UIUC");
    g.BFSToFile();
    map <string, double> dijkstra = g.dijkstra("UIUC");
    // map <string, double> badDijkstra = g.badDijkstra("UIUC");
    vector<pair<string, double>> v = vector<pair<string, double>>();
    for (auto itr : dijkstra) {
        v.push_back(std::make_pair(itr.first, itr.second));
    }
    // vector<pair<string, double>> vbad = vector<pair<string, double>>();
    // for (auto itr : badDijkstra) {
    //     vbad.push_back(std::make_pair(itr.first, itr.second));
    // }
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
    // std::sort(vbad.begin(), vbad.end(), lessthan());

    ofstream Dijkstra("DijkstraResult.txt");
    for(auto itr : v) {
        Dijkstra << itr.first << " " << itr.second << '\n';
    }

    // ofstream BadDijkstra("BadDijkstraResult.txt");
    // for(auto itr : vbad) {
    //     BadDijkstra << itr.first << " " << itr.second << '\n';
    // }
    */

    /*
    map<Graph::SubReddit*, int> adjacent = g.getSubReddit("PokemonGoRaid")->adjacent;
    for(map<Graph::SubReddit*, int>::iterator it = adjacent.begin(); it != adjacent.end(); it++) {
        cout << "Sub: " << it->first->name << " Weight: " << it->second << endl; 
    }*/
    return 0;
}