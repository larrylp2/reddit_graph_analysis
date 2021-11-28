#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "include/Graph.h"


int main() {
    //undefined symbol error
    GraphBuilder builder = GraphBuilder();

    std::string file_path = "data-fetching/data/subreddit_test/UIUC.txt";

    // builder.populateSubReddits(file_path);

    // GraphBuilder::SubReddit* sub = builder.getSubReddit("UIUC");

    //iterate through the subreddit's adjacent nodes
    std::cout << "Adjacent SubReddits" << std::endl;

    // int size = sub->adjacentSubReddits.size();
    // for(int i = 0; i < size; i++) {
    //     std::cout << sub->adjacentSubReddits[i]->name << std::endl;
    // }

    return 0;
}