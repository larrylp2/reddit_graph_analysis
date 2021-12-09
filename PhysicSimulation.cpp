#include "PhysicSimulation.h"
#include <cmath>

PhysicSimulation::PhysicSimulation() {
    //do something
}

PhysicSimulation::PhysicSimulation(int coefficient, int length) {
    time = 0;
    springCoefficient = coefficient;
    springNaturalLength = length;
}

void PhysicSimulation::initiateGraph(Graph g) {

    //retrieve the total number of subreddits
    //int totalSubreddits = g.getSubs();
    if (g == NULL) {
        return;
    }
    //retrieve the collection of subreddits
    map<string, Graph::SubReddit*> subreddits = g.getSubReddits();
    //setting the common position
    std::pair<int, int> starting_point(0, 0);
    //for each subreddit, we insert the value with 
    for(map<string, Graph::SubReddit*>::iterator it = subreddits.begin(); it != subreddits.end(); it++) {
        //check to make sure each entry is not null
        if (it -> second != NULL) {
            positions.insert(pair<Graph::SubReddit*, pair<int, int>>(it -> second, starting_point));
        }
    }
    
}

map<Graph::SubReddit*, pair<int, int>> simulateFor(int seconds) {
    for (int i = 0; i < seconds; i++) {
        for (map<Graph::SubReddit*, pair<int, int>>::iterator it = positions.begin(); it != positions.end(); it++) {
            std::pair<int, int> force_vector(0, 0);
            //find distance between current node and adjacent node
            int x_distance = pow((it -> second.x - it -> adjacent -> second.x), 2);
            int y_distance = pow((it -> second.y - it -> adjacent -> second.y), 2);

            int total_distance = sqrt(x_distance + y_distance);
        }
    }
}
