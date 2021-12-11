#pragma once

#include "cs225/PNG.h"
#include "PhysicSimulation.h"
#include "Graph.h"
using namespace std;

class GraphVisualization {
    public:
        GraphVisualization();

        ~GraphVisualization();

        GraphVisualization(int width, int height, int max_connections, string path);

        map<Graph::SubReddit*, pair<int, int>> convertCoordinates(map<Graph::SubReddit*, pair<float, float>>& redditCoords);
        
        cs225::PNG* drawGraph(map<Graph::SubReddit*, pair<int, int>> redditCoords);

        void loadGraph(Graph g);
        
        void createVisualization();

    private:

        void loadCharacterPNG(string path);

        int calculateNodeHue(Graph::SubReddit* node) const;

        void drawNode(cs225::PNG* image, Graph::SubReddit* node, pair<int, int> location);

        void drawLine(cs225::PNG* image, pair<int, int> coord1, pair<int, int> coord2, double coord1Hue, double coord2Hue, double saturation, double luminance);

        void writeLabel(cs225::PNG* image, string label, pair<int, int> location);

        cs225::PNG resize(const cs225::PNG* image, float ratio);

        int radius_;
        int width_;
        int height_;
        int max_connections_;
        map<char, cs225::PNG*> characters_;

        Graph graph_;
};