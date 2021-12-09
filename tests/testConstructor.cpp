#include "../cs225/catch/catch.hpp"
#include "../Graph.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

TEST_CASE("Constructor Simple Graph", "[weight=1]") {
    std::string file_path = "data/testConstructor/";

    Graph g = Graph(file_path);
    g.readGraphBFS("one");
    
    REQUIRE(g.commonUsers("two", "one") == g.commonUsers("one", "two") == 2);
    REQUIRE(g.commonUsers("three", "one") == g.commonUsers("one", "three") == 1);
    REQUIRE(g.commonUsers("four", "one") == g.commonUsers("one", "four") == 1);
    REQUIRE(g.commonUsers("five", "one") == g.commonUsers("one", "five") == 1);
    REQUIRE(g.commonUsers("three", "two") == g.commonUsers("two", "three") == 1);
    REQUIRE(g.commonUsers("four", "two") == g.commonUsers("two", "four") == 1);
    REQUIRE(g.commonUsers("five", "two") == g.commonUsers("two", "five") == 1);
    REQUIRE(g.commonUsers("four", "three") == g.commonUsers("three", "four") == 1);
    REQUIRE(g.commonUsers("five", "three") == g.commonUsers("three", "five") == 0);
    REQUIRE(g.commonUsers("five", "four") == g.commonUsers("four", "five") == 0);
}

TEST_CASE("Constructor Larger Graph", "[weight=1]") {
    std::string file_path = "data/testDijkstra1/";

    Graph g = Graph(file_path);
    g.readGraphBFS("A");
    
    Graph::SubReddit* sA = g.retrieveSubreddit("A");
    Graph::SubReddit* sB = g.retrieveSubreddit("B");
    Graph::SubReddit* sC = g.retrieveSubreddit("C");
    Graph::SubReddit* sD = g.retrieveSubreddit("D");
    Graph::SubReddit* sE = g.retrieveSubreddit("E");
    REQUIRE(g.commonUsers("B", "A") == g.commonUsers("A", "B") == 3);
    REQUIRE(g.commonUsers("C", "A") == g.commonUsers("A", "C") == 2);
    REQUIRE(g.commonUsers("D", "B") == g.commonUsers("B", "D") == 1);
    REQUIRE(g.commonUsers("E", "B") == g.commonUsers("B", "E") == 2);
    REQUIRE(g.commonUsers("A", "E") == g.commonUsers("E", "A") == 1);
    REQUIRE(g.commonUsers("C", "E") == g.commonUsers("E", "C") == 5);
}
