#include "GraphVisualization.h"


GraphVisualization::GraphVisualization(int radius, int width, int height) {
    radius_ = radius;
    width_ = width;
    height_ = height;
}


cs225::PNG* GraphVisualization::drawGraph(Graph &graph) {
    map<Graph::SubReddit*, pair<int, int>> redditCoords = loadSimulation(graph);

    cs225::PNG* image = new cs225::PNG(width_, height_);

    //start drawing the graph from the first node in the dictionary iterator
    Graph::SubReddit* start = redditCoords.begin()->first;

    //visited subreddits
    set<Graph::SubReddit*> drawn;

    //use a queue (BFS)
    queue<Graph::SubReddit*> toDraw;

    toDraw.push(start);
    while(!toDraw.empty()) {
        //look at the first
        Graph::SubReddit* node = toDraw.front();
        toDraw.pop();

        if(drawn.find(node) != drawn.end()) { //node already exists in the drawn set of nodes
            //do nothing and move on to the next node
        } else {
            //get the coordinates of the current node
            pair<int, int> coords = redditCoords.find(node)->second;
            //draw all of the outgoing edges, adding each one to the queue
            for(map<Graph::SubReddit*, int>::iterator it = node->adjacent.begin(); it != node->adjacent.end(); it++) {
                drawLine(image, coords, redditCoords.find(it->first)->second);

                toDraw.push(it->first);
            }

            //draw the node itself
            drawNode(image, node, coords);

            //mark this node drawn
            drawn.insert(node);
        }
    }
    //only issue is that each edge is drawn twice
}



void GraphVisualization::drawNode(cs225::PNG* image, Graph::SubReddit* node, pair<int, int> location) {

}


void GraphVisualization::drawLine(cs225::PNG* image, pair<int, int> coord1, pair<int, int> coord2) {

}






