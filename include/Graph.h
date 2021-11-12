#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

class Graph {
    public:
        struct Node {
            //Name of this subreddit
            string name; 
            //List of its adjacentNodes, map the name of the subreddit to a pair of Node* and long.
            //long is the weight of the connection (user count) and Node* points to the other subreddit node.
            map <string, pair<Node*, long> > adjacentNodes;
        };

        Graph();


    private:
        map<string, Node*> nodeList; //Store the list of all nodes, map the name to the pointer
};