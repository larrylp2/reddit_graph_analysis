#include "GraphVisualization.h"
#include <math.h>


GraphVisualization::GraphVisualization(int radius, int width, int height) {
    radius_ = radius;
    width_ = width;
    height_ = height;
}


cs225::PNG* GraphVisualization::drawGraph(map<Graph::SubReddit*, pair<int, int>> redditCoords) {
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
                drawLine(image, coords, redditCoords.find(it->first)->second, 0, 0, 0);

                toDraw.push(it->first);
            }
            //mark this node drawn
            drawn.insert(node);
        }
    }

    //now draw all of the nodes
    for(map<Graph::SubReddit*, pair<int, int>>::iterator it = redditCoords.begin(); it != redditCoords.end(); it++) {
        //draw the node itself
        drawNode(image, it->first, it->second);
    }


    //only issue is that each edge is drawn twice
    return image;
}



void GraphVisualization::drawNode(cs225::PNG* image, Graph::SubReddit* node, pair<int, int> location) {

    //TODO: Coloring the node


    //draws a circle based on the existing radius at the given location
    //creates the equation of a circle
    // (x - startingX)^2 + (y - startingY)^2 = radius_^2
    // positive portion and negative portions
    // y = (radius^2 - (x - startingX)^2)^.5 - startingY
    // y = (radius^2 - (x - startingX)^2)^.5 + startingY
    // y-1 = (4^4 - y-1
    // x and y are interchangable

    //calculate the upper and lower y values as we go from the left most x coordinate on the circle (start - radius) to the right most x coordinate
    //at the same time, calculates the upper and lower y values as we go from top most y coordinate to the bottom most y coordinate
    //(found that only calculating the upper and lower y values yields a unfinished sphere for smaller radius sizes)
    //round to nearest int when coloring png
    //assume that the left most x coordinate is nonnegative and within bounds?
    int x = location.first;
    int y = location.second;

    int xUpper = x + radius_;
    int yUpper = y + radius_;
    int offset = 0; //offset from xUpper and yUpper we are checking
    while(offset <= radius_ * 2) {
        //need to add way to write the name
        //diff
        float diffY = sqrt(1.0 * (radius_ * radius_) - (xUpper - offset - x) * (xUpper - offset - x));
        float diffX = sqrt(1.0 * (radius_ * radius_) - (yUpper - offset - y) * (yUpper - offset - y));
        //std::cout << "current x: " << currentX << " diff " << diff << std::endl;


        //draw lines between these two coordinates to fill the circle in addition to drawing the outline

        drawLine(image, pair<int, int>(xUpper - offset, y + diffY), pair<int, int>(xUpper - offset, y - diffY), 11, .5, .5);
        drawLine(image, pair<int, int>(x + diffX, yUpper - offset), pair<int, int>(x - diffX, yUpper - offset), 11, .5, .5);

        image->getPixel(xUpper - offset, y + diffY).l = 0; //upper y drawn by rounding the float result
        image->getPixel(xUpper - offset, y - diffY).l = 0; //lower y drawn by rounding the float result

        image->getPixel(x + diffX, yUpper - offset).l = 0; //upper x drawn by rounding the float result
        image->getPixel(x - diffX, yUpper - offset).l = 0; //lower x drawn by rounding the float result

        offset++;
        //float currentYUpper = y + diff;
        //std::cout << "Y Upper: " << currentYUpper << std::endl;
        //float currentYLower = y - diff;
        //std::cout << "Y Lower: " << currentYLower << std::endl;

        //assume that resultant y values are also within bounds of the png
        //image->getPixel(currentX, currentYUpper).l = 0; //set luminance to 0, appears black, round the Y to the correct Y
        //image->getPixel(currentX, currentYLower).l = 0; //set luminance to 0, appears black, round the Y to the correct Y
    }
}


void GraphVisualization::drawLine(cs225::PNG* image, pair<int, int> coord1, pair<int, int> coord2, double hue, double saturation, double luminance) {
    std::cout << "Drawing from (" << coord1.first << "," << coord1.second << ") to (" << coord2.first << "," << coord2.second << ")" << std::endl;
    //draws a line between two points
    int startX = coord1.first;
    int startY = coord1.second;
    int endX = coord2.first;
    int endY = coord2.second;

    //finds the x we need to travel 
    int xDiff = startX - endX;

    //finds the y we need to travel
    int yDiff = startY - endY;

    // we are drawing a vertical line
    if(xDiff == 0) {
        while(startY != endY) {
            image->getPixel(startX, startY).h = hue;
            image->getPixel(startX, startY).s = saturation;
            image->getPixel(startX, startY).l = luminance;
            int increment = (yDiff > 0) ? -1 : 1;
            startY += increment;
        }
    } else {

        //find the slope (rise over run with dy/dx)
        float slope = yDiff * 1.0 / xDiff;
        std::cout << "Slope: " << slope << std::endl;
        float currentY = startY;
        float currentX = startX;
        //follow the slope filling in the nearest whole pixel until we reach the end point
        while(currentX <= endX) {
            image->getPixel(currentX, (int)currentY).h = hue;
            image->getPixel(currentX, (int)currentY).s = saturation;
            image->getPixel(currentX, (int)currentY).l = luminance;

            currentY += slope; //increment the current Y by the slope as we increase X by one
            currentX++;
        }
    }


}






