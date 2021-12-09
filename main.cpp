#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Graph.h"
#include "GraphVisualization.h"

int main() {
    
    // std::cout << "Compile Worked" << std::endl;

    // std::string file_path = "data-fetching/data/";
    
    // Graph builder = Graph(file_path);

    // builder.readGraphBFS("UIUC");

    // std::cout << "Users: " << builder.getUsers() << std::endl;;

    // std::cout << "Subs: " << builder.getSubs() << std::endl;

    // builder.printMaxConnection();

    // builder.BFSToFile();

    // // std::cout << builder.dijkstra("UIUC", "AskReddit");
    
   
    // //tests out the visualization
    // Graph::SubReddit* uiuc = new Graph::SubReddit();
    // uiuc->name = "UIUC";

    // Graph::SubReddit* cs = new Graph::SubReddit();
    // cs->name = "CS";
    
    // std::map<Graph::SubReddit*, int> adj2;
    // adj2.insert({cs, 1});

    // Graph::SubReddit* one = new Graph::SubReddit();
    // one->name = "one";
    // std::map<Graph::SubReddit*, int> adj3;
    // adj3.insert({cs, 1});

    // Graph::SubReddit* two = new Graph::SubReddit();
    // two->name = "two";
    // std::map<Graph::SubReddit*, int> adj4;
    // adj4.insert({cs, 1});

    // Graph::SubReddit* three = new Graph::SubReddit();
    // three->name = "three";
    // std::map<Graph::SubReddit*, int> adj5;
    // adj5.insert({cs, 1});
    // adj5.insert({two, 1});
    // adj4.insert({three, 1});

    // std::map<Graph::SubReddit*, int> adj;
    // adj.insert({uiuc, 1});
    // adj.insert({one, 1});
    // adj.insert({two, 1});
    // adj.insert({three, 1});

    // cs->adjacent = adj;
    // uiuc->adjacent = adj2;
    // one->adjacent = adj3;
    // two->adjacent = adj4;
    // three->adjacent = adj5;


    // std::pair<int, int> position1(300, 70);
    // std::pair<int ,int> position2(75, 268);
    // std::pair<int ,int> position3(40, 30);
    // std::pair<int ,int> position4(300, 300);
    // std::pair<int ,int> position5(200, 20);


    // map<Graph::SubReddit*, pair<int, int>> redditCoords;
    // redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    // redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));
    // redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(one, position3));
    // redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(two, position4));
    // redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(three, position5));

    // GraphVisualization visual = GraphVisualization(20, 400, 400, 4);

    // cs225::PNG* drawing = visual.drawGraph(redditCoords);

    // drawing->writeToFile("smallVisualizerTestOutput.png");


    // Don't do tests in main.cpp lol

    Graph g = Graph("data/data2/");
    g.readGraphBFS("UIUC");
    // g.BFSToFile();
    map <string, double> dijkstra = g.dijkstra("UIUC");
    vector<pair<string, double>> v = vector<pair<string, double>>();
    for (auto itr : dijkstra) {
        v.push_back(std::make_pair(itr.first, itr.second));
    }

    struct comparator {
        inline bool operator() (const pair<string, double>& p1, const pair<string, double>& p2) {
            return (p1.second < p2.second);
        }
    };

    std::sort(v.begin(), v.end(), comparator());
    for (auto itr : v) {
        cout << itr.first << " " << itr.second << '\n';
    }
    
    ofstream Dijkstra("DijkstraResult.txt");
    for(auto itr : v) {
        Dijkstra << itr.first << " " << itr.second << '\n';
    }
    return 0;
}