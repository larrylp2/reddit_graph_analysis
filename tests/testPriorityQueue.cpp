#include "../PriorityQueue.h"
#include "../cs225/catch/catch.hpp"

TEST_CASE("testPriorityQueue", "[weight=1][part=1]")
{
	PriorityQueue pq = PriorityQueue();

    Graph::SubReddit* p1 = new Graph::SubReddit();
    Graph::SubReddit* p2 = new Graph::SubReddit();
    Graph::SubReddit* p3 = new Graph::SubReddit();
    Graph::SubReddit* p4 = new Graph::SubReddit();
    Graph::SubReddit* p5 = new Graph::SubReddit();
    
    pq.push(p1, -1);
    pq.push(p2, 10);
    pq.push(p3, 1);
    pq.push(p4, 20);
    pq.push(p5, 7);

    vector<double> list;
    vector<double> expected;

    expected.push_back(1);
    expected.push_back(7);
    expected.push_back(10);
    expected.push_back(20);
    expected.push_back(-1);

    while (!pq.isEmpty()) {
        list.push_back(pq.peakMinValue());
        pq.popMin();
    }

    REQUIRE(list == expected);
}