#pragma once

#include "Graph.h"
#include "cs225/PNG.h"
//#include "GraphSimulation"
using namespace std;

class GraphVisualization {
    public:
        GraphVisualization(int radius, int width, int height);
        
        cs225::PNG* drawGraph(Graph &graph);

    private:

        void drawNode(cs225::PNG* image, Graph::SubReddit* node, pair<int, int> location);

        void drawLine(cs225::PNG* image, pair<int, int> coord1, pair<int, int> coord2);

        map<Graph::SubReddit*, pair<int, int>> loadSimulation(Graph& graph);


        int radius_;
        int width_;
        int height_;


};