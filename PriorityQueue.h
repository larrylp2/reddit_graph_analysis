#pragma once

#include <vector>
#include "Graph.h"

using namespace std;

class PriorityQueue {
    public:
        struct HeapNode {
            Graph::SubReddit* subreddit;
            double weight;
            HeapNode* parent;
            HeapNode* leftChild;
            HeapNode* rightChild;
        };
        PriorityQueue();
        PriorityQueue(Graph::SubReddit* root, vector<Graph::SubReddit*> rest);
        ~PriorityQueue();

    private:
        map<Graph::SubReddit*, HeapNode*> nodeList;

};