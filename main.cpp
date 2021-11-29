#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Graph.h"


int main() {
    std::cout << "Compile Worked" << std::endl;
    GraphBuilder builder = GraphBuilder();

    std::string file_path = "data-fetching/data/";

    builder.readGraph("UIUC");

    return 0;
}