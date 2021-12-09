#pragma once

#include "Graph.h"
#include "cs225/PNG.h"
//#include "GraphSimulation"
using namespace std;

class GraphVisualization {
    public:
        GraphVisualization();

        GraphVisualization(int radius, int width, int height, int max_connections);

        void convertCoordinates(map<Graph::SubReddit*, pair<int, int>>& redditCoords);
        
        cs225::PNG* drawGraph(map<Graph::SubReddit*, pair<int, int>> redditCoords);

    private:

        void drawNode(cs225::PNG* image, Graph::SubReddit* node, pair<int, int> location);

        void drawLine(cs225::PNG* image, pair<int, int> coord1, pair<int, int> coord2, double hue, double saturation, double luminance);

        int radius_;
        int width_;
        int height_;
        int max_connections_;


};