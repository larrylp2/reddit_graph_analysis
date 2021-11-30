#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Graph.h"


int main() {
    std::cout << "Compile Worked" << std::endl;

    std::string file_path = "data-fetching/data/";
    
    Graph builder = Graph(file_path);

    builder.readGraphBFS("UIUC");

    std::cout << "Users: " << builder.getUsers() << std::endl;;

    std::cout << "Subs: " << builder.getSubs() << std::endl;

    builder.printMaxConnection();

    builder.BFSTraversal();

    std::cout << builder.dijkstra("UIUC", "AskReddit");
    return 0;
}