#include "../GraphVisualization.h"
#include "../cs225/catch/catch.hpp"


TEST_CASE("Draw Nodes Simple Graph", "[weight=1]")
{
    //Simple graph with just two nodes, one at (4,5) and another at (5,17)
	Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";

    std::pair<int, int> position1(300, 70);
    std::pair<int ,int> position2(75, 268);

    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));

    GraphVisualization visual = GraphVisualization(20, 400, 350, 2);

    cs225::PNG* drawing = visual.drawGraph(redditCoords);

    REQUIRE(drawing->height() == 350);
    REQUIRE(drawing->width() == 400); 
    REQUIRE(drawing->getPixel(300, 70).h == 11); //UIUC node automatically orange
    REQUIRE(drawing->getPixel(75, 268).h != 0);
}

TEST_CASE("Draw Edges Simple Graph", "[weight=1]")
{
    //Simple graph with just two nodes, one at (4,5) and another at (5,17)
	Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";

    std::pair<int, int> position1(300, 70);
    std::pair<int ,int> position2(75, 268);

    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));

    GraphVisualization visual = GraphVisualization(20, 400, 350, 2);

    cs225::PNG* drawing = visual.drawGraph(redditCoords);

    REQUIRE(drawing->height() == 350);
    REQUIRE(drawing->width() == 400); 
    //test that the midpoint is colored instead of tracing entire edge

}

TEST_CASE("Draw Nodes Larger Graph", "[weight=1]")
{
    Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";

    Graph::SubReddit* one = new Graph::SubReddit();
    one->name = "one";

    Graph::SubReddit* two = new Graph::SubReddit();
    two->name = "two";

    Graph::SubReddit* three = new Graph::SubReddit();
    three->name = "three";

    std::pair<int, int> position1(300, 70);
    std::pair<int ,int> position2(75, 268);
    std::pair<int ,int> position3(40, 30);
    std::pair<int ,int> position4(300, 300);
    std::pair<int ,int> position5(200, 20);

    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(one, position3));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(two, position4));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(three, position5));

    GraphVisualization visual = GraphVisualization(20, 400, 400, 4);

    cs225::PNG* drawing = visual.drawGraph(redditCoords);

    REQUIRE(drawing->height() == 400);
    REQUIRE(drawing->width() == 400); 
    REQUIRE(drawing->getPixel(300, 70).h == 11); //UIUC node automatically orange
    REQUIRE(drawing->getPixel(75, 268).h != 0); 
    REQUIRE(drawing->getPixel(40, 30).h != 0); 
    REQUIRE(drawing->getPixel(300, 300).h != 0); 
    REQUIRE(drawing->getPixel(200, 20).h != 0); 

}

TEST_CASE("Draw Edges Larger Graph", "[weight=1]")
{
    Graph::SubReddit* uiuc = new Graph::SubReddit();
    uiuc->name = "UIUC";

    Graph::SubReddit* cs = new Graph::SubReddit();
    cs->name = "CS";
    
    std::map<Graph::SubReddit*, int> adj2;
    adj2.insert({cs, 1});

    Graph::SubReddit* one = new Graph::SubReddit();
    one->name = "one";
    std::map<Graph::SubReddit*, int> adj3;
    adj3.insert({cs, 1});

    Graph::SubReddit* two = new Graph::SubReddit();
    two->name = "two";
    std::map<Graph::SubReddit*, int> adj4;
    adj4.insert({cs, 1});

    Graph::SubReddit* three = new Graph::SubReddit();
    three->name = "three";
    std::map<Graph::SubReddit*, int> adj5;
    adj5.insert({cs, 1});
    adj5.insert({two, 1});
    adj4.insert({three, 1});

    std::map<Graph::SubReddit*, int> adj;
    adj.insert({uiuc, 1});
    adj.insert({one, 1});
    adj.insert({two, 1});
    adj.insert({three, 1});

    cs->adjacent = adj;
    uiuc->adjacent = adj2;
    one->adjacent = adj3;
    two->adjacent = adj4;
    three->adjacent = adj5;


    std::pair<int, int> position1(300, 70);
    std::pair<int ,int> position2(75, 268);
    std::pair<int ,int> position3(40, 30);
    std::pair<int ,int> position4(300, 300);
    std::pair<int ,int> position5(200, 20);


    map<Graph::SubReddit*, pair<int, int>> redditCoords;
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(uiuc, position1));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(cs, position2));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(one, position3));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(two, position4));
    redditCoords.insert(pair<Graph::SubReddit*, pair<int, int>>(three, position5));

    GraphVisualization visual = GraphVisualization(20, 400, 400, 4);

    cs225::PNG* drawing = visual.drawGraph(redditCoords);

    //test the midpoints points of each edge

}

