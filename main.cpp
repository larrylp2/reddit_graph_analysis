#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Graph.h"


int main() {
    std::cout << "Compile Worked" << std::endl;

    std::string file_path = "data-fetching/data/";
    
    GraphBuilder builder = GraphBuilder(file_path);

    builder.readGraphBFS("UIUC");

    std::map<GraphBuilder::SubReddit*, int> adjacent = builder.retrieveSubreddit("UIUC")->adjacent;
    for(std::map<GraphBuilder::SubReddit*, int>::iterator it = adjacent.begin(); it != adjacent.end(); it++) {
        std::cout << "Subreddit: " << it->first->name << " Weight: " << it->second << std::endl;
    } //Segmentation fault: 11, currently having a stack overflow

    return 0;
}