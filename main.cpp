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

    // Don't do tests in main.cpp lol

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
    /*
    map<Graph::SubReddit*, int> adjacent = g.getSubReddit("PokemonGoRaid")->adjacent;
    for(map<Graph::SubReddit*, int>::iterator it = adjacent.begin(); it != adjacent.end(); it++) {
        cout << "Sub: " << it->first->name << " Weight: " << it->second << endl; 
    }*/
    return 0;
}