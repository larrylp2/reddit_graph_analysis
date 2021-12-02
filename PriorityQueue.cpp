#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {
    // Default constructor
    size = 0;
    nodeList = map<Graph::SubReddit*, HeapNode*>();
    root = NULL;
}

PriorityQueue::PriorityQueue(Graph::SubReddit* first, vector<Graph::SubReddit*> rest) {
    // Default constructor
}

PriorityQueue::~PriorityQueue() {
    // Destructor
}

Graph::SubReddit* PriorityQueue::peakMin() const {
    return root->subreddit;
}

void PriorityQueue::popMin() {

}

void PriorityQueue::push(Graph::SubReddit* subreddit, double weight) {

}

void PriorityQueue::changeWeight(Graph::SubReddit* sub, double newWeight) {

}
bool PriorityQueue::isEmpty() const {

}
void PriorityQueue::heapifyUp(HeapNode* node) {
    if (node == root) {
        return;
    }
    HeapNode* p = node->parent;
    if (lesser(node, p)) {
        if (p->leftChild == node) {

        } else {
            
        }
        heapifyUp(p);
    }
}
void PriorityQueue::heapifyDown(HeapNode* node) {

}

bool PriorityQueue::hasAChild(HeapNode* node) const{

}

bool PriorityQueue::lesser(HeapNode* left, HeapNode* right) const{
    double wl = left->weight;
    double wr = right->weight;
    if (wl == -1) {
        return false;
    }
    if (wr == -1) {
        return true;
    }
    return (wl < wr);
}

PriorityQueue::HeapNode* PriorityQueue::rightMostNode() const {
    
}

void PriorityQueue::swap(HeapNode* child, HeapNode* parent) {
    
}