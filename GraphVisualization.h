#pragma once

#include "Graph.h"
#include "cs225/PNG.h"
//#include "GraphSimulation"
using namespace std;

class GraphVisualization {
    public:
        GraphVisualization();

        ~GraphVisualization();

        GraphVisualization(int width, int height, int max_connections);

        void convertCoordinates(map<Graph::SubReddit*, pair<int, int>>& redditCoords);
        
        cs225::PNG* drawGraph(map<Graph::SubReddit*, pair<int, int>> redditCoords);

    private:
        void loadCharacterPNG();

        int calculateNodeHue(Graph::SubReddit* node) const;

        void drawNode(cs225::PNG* image, Graph::SubReddit* node, pair<int, int> location);

        void drawLine(cs225::PNG* image, pair<int, int> coord1, pair<int, int> coord2, double coord1Hue, double coord2Hue, double saturation, double luminance);

        void writeLabel(cs225::PNG* image, string label, pair<int, int> location);

        int radius_;
        int width_;
        int height_;
        int max_connections_;
        map<char, cs225::PNG*> characters_;

};