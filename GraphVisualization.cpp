#include "GraphVisualization.h"
#include <math.h>

GraphVisualization::GraphVisualization() {
    //default constructor
}

GraphVisualization::~GraphVisualization() {
    //destructor
    for(map<char, cs225::PNG*>::iterator it = characters_.begin(); it != characters_.end(); it++) {
        delete it->second;
    }
    characters_ = map<char, cs225::PNG*>();
}

GraphVisualization::GraphVisualization(int width, int height, int max_connections) {
    radius_ = 100;
    width_ = width;
    height_ = height;
    max_connections_ = max_connections;
    loadCharacterPNG();
}

void GraphVisualization::convertCoordinates(map<Graph::SubReddit*, pair<int, int>>& redditCoords) {
    //do a pass through to find the largest and smallest x and y coordinates
    int smallestX = INT_MAX;
    int smallestY = INT_MAX;
    int largestX = INT_MIN;
    int largestY = INT_MIN;

    for(map<Graph::SubReddit*, pair<int, int>>::iterator it = redditCoords.begin(); it != redditCoords.end(); it++) {
        int x = it->second.first;
        int y = it->second.second;

        smallestX = (x < smallestX) ? x : smallestX;
        smallestY = (y < smallestX) ? y : smallestY;
        largestX = (x > largestX) ? x : largestX;
        largestY = (y > largestY) ? y : largestY;
    }

    //check if we need to make the coordinates positive by translating by the negative x and y
    int translateY = (smallestY < 0) ? -1 * smallestY : 0;
    int translateX = (smallestX < 0) ? -1 * smallestX : 0;


    largestX += translateX;
    largestY += translateY;

    for(map<Graph::SubReddit*, pair<int, int>>::iterator it = redditCoords.begin(); it != redditCoords.end(); it++) {
        int x = it->second.first + translateX; //translate to be non negative
        int y = it->second.second + translateY; //translate to be non negative

        //scale to be within height bounds
        y = height_ * 1.0 * y / largestY;
        x = width_ * 1.0 * y / largestX;

        //update positions
        it->second.first = x;
        it->second.second = y;
    }
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
                drawLine(image, coords, redditCoords.find(it->first)->second, calculateNodeHue(node), calculateNodeHue(it->first), .5, .5);

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

int GraphVisualization::calculateNodeHue(Graph::SubReddit* node) const {
    int scaled = 180 * 1.0 * node->adjacent.size() / max_connections_;
    int hue = 180 - scaled;
    if(node->name == "UIUC") {
        hue = 11;
    }
    return hue;
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

    //hue is dependent on the number of outgoing connections the subreddit has
    //goes from light blue to red as a node has more outgoing connections (180 - 0)
    //scale the connections to be between 0 and 180
    //we already know the max connection
    int hue = calculateNodeHue(node);

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
        drawLine(image, pair<int, int>(xUpper - offset, y + diffY), pair<int, int>(xUpper - offset, y - diffY), hue, hue, .5, .5);
        drawLine(image, pair<int, int>(x + diffX, yUpper - offset), pair<int, int>(x - diffX, yUpper - offset), hue, hue, .5, .5);

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

    writeLabel(image, node->name, location);
}

void GraphVisualization::drawLine(cs225::PNG* image, pair<int, int> coord1, pair<int, int> coord2, double coord1Hue, double coord2Hue, double saturation, double luminance) {
    //std::cout << "Drawing from (" << coord1.first << "," << coord1.second << ") to (" << coord2.first << "," << coord2.second << ")" << std::endl;
    //draws a line between two points
    int hueChange = coord1Hue - coord2Hue;
    bool check = coord1Hue == 135;
    float currentHue = coord1Hue;

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
        float hueChangeY = 1.0 * hueChange / yDiff; 
        int counter = 0;
        while(startY != endY) {
            image->getPixel(startX, startY).h = currentHue;
            image->getPixel(startX, startY).s = saturation;
            image->getPixel(startX, startY).l = luminance;
            int increment = (yDiff > 0) ? -1 : 1;
            startY += increment;
            counter++;
            currentHue += hueChangeY;
        }
    } else {
        if(abs(yDiff) > abs(xDiff)) { //go by Y if we are travelling through Y more
            float hueChangeY = 1.0 * hueChange / yDiff;
            //do from y
            float slope = xDiff * 1.0 / yDiff;
            float currentY = startY;
            float currentX = startX;
            int counter = 0;
            while(currentY <= endY) {
                image->getPixel(currentX, (int)currentY).h = currentHue;
                image->getPixel(currentX, (int)currentY).s = saturation;
                image->getPixel(currentX, (int)currentY).l = luminance;

                currentX += slope; //increment the current Y by the slope as we increase X by one
                currentY++;
                currentHue += hueChangeY;
                counter++;
            }

        } else { //go by X if we are travelling through X more
            float hueChangeX = 1.0 * hueChange / xDiff;
            //find the slope (rise over run with dy/dx)
            float slope = yDiff * 1.0 / xDiff;
            //std::cout << "Slope: " << slope << std::endl;
            float currentY = startY;
            float currentX = startX;
            //follow the slope filling in the nearest whole pixel until we reach the end point
            while(currentX <= endX) {
                image->getPixel(currentX, (int)currentY).h = currentHue;
                image->getPixel(currentX, (int)currentY).s = saturation;
                image->getPixel(currentX, (int)currentY).l = luminance;

                currentY += slope; //increment the current Y by the slope as we increase X by one
                currentX++;
                currentHue += hueChangeX;
            }
        }
    }


}

void GraphVisualization::loadCharacterPNG() {
    string neededChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
    string folder = "/InterFontCharacters/";
    string suffix = ".png";
    for(char c : neededChars) {
        string current;
        if(c >= 65 && c <= 90) { //capital character
            char cc = c + 32;
            current = string({cc}) + "cap";
        } else if (c == '-') {
            current = "customdash";
        } else if (c == '_') {
            current = "customunderscore";
        } else {
            current = string({c});
        }
        string file = folder + current + suffix;
        cout << "File: " << file << endl;
        cs225::PNG* newChar = new cs225::PNG(10, 16);
        newChar->readFromFile(file);
        characters_.insert(pair<char, cs225::PNG*>(c, newChar));
    }
}

void GraphVisualization::writeLabel(cs225::PNG* image, string label, pair<int, int> location) {
    int width = 0; //keep track of the estimated pixel width of the letters
    vector<cs225::PNG*> characters;
    for(char c : label) {
        cs225::PNG* png = characters_.find(c)->second;
        characters.push_back(png);
        width += png->width();
    }

    //check if the width is greater than the one allocated by the radius
    if(width > radius_ * 2) {
        //do later;

    } else {
        //make it centered
        int currentX = location.first - width / 2;
        for(cs225::PNG* png : characters) {
            int height = png->height();
            //make sure the height is centered as well
            int currentY = location.second - height / 2;
            for(int x = 0; x < 10; x++) {
                for(int y = 0; y < height; y++) {
                    if(png->getPixel(x, y).a != 0) {
                        image->getPixel(currentX, currentY).a = 1;
                    }
                }
                currentX++;
            }
        }
    }
}