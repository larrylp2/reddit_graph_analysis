#include "../GraphVisualization.h"
#include "../cs225/catch/catch.hpp"


TEST_CASE("testSimpleGraph", "[weight=1]")
{
    //Simple graph with just two nodes, one at (4,5) and another at (5,17)
	Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";

    std::map<Graph::SubReddit*, int> adj;
    adj.insert(std::pair<Graph::SubReddit*, int>(uiuc, 1));
    
    std::map<Graph::SubReddit*, int> adj2;
    adj2.insert(std::pair<Graph::SubReddit*, int>(cs, 1));

    cs->adjacent = adj;
    uiuc->adjacent = adj2;

    std::pair<int, int> position1(300, 70);
    std::pair<int ,int> position2(75, 268);

    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));

    GraphVisualization visual = GraphVisualization(20, 400, 350);

    cs225::PNG* drawing = visual.drawGraph(redditCoords);

    REQUIRE(drawing.height() == 350);
    REQUIRE(drawing.width() == 400); 
    REQUIRE(drawing.getPixel(300, 70).h == 11);
    REQUIRE(drawing.getPixel(75, 268).h == 11);
}