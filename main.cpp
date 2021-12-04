#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Graph.h"
#include "GraphVisualization.h"
#include "PriorityQueue.h"

int main() {
    std::cout << "Compile Worked" << std::endl;

    std::string file_path = "data-fetching/data/";
    
    Graph builder = Graph(file_path);

    builder.readGraphBFS("UIUC");

    std::cout << "Users: " << builder.getUsers() << std::endl;;

    std::cout << "Subs: " << builder.getSubs() << std::endl;

    builder.printMaxConnection();

    builder.BFSTraversal();

    std::cout << builder.dijkstra("UIUC", "AskReddit");

    Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    // PriorityQueue pq = PriorityQueue();

    //tests out the visualization
    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";
    std::map<Graph::SubReddit*, int> adj;
    adj.insert(std::pair<Graph::SubReddit*, int>(uiuc, 1));
    
    std::map<Graph::SubReddit*, int> adj2;
    adj2.insert(std::pair<Graph::SubReddit*, int>(cs, 1));

    cs->adjacent = adj;
    uiuc->adjacent = adj2;

    std::pair<int, int> position1(300, 70);
    std::pair<int ,int> position2(75, 268);

    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));

    GraphVisualization visual = GraphVisualization(20, 400, 400);

    cs225::PNG* drawing = visual.drawGraph(redditCoords);

    drawing->writeToFile("smallVisualizerTestOutput.png");

    return 0;
}