#include "PhysicSimulation.h"
#include <cmath>
#include <fstream>

PhysicSimulation::PhysicSimulation() {
    //do something
}

PhysicSimulation::PhysicSimulation(int coefficient, int length) {
    time = 0;
    springCoefficient = coefficient;
    springNaturalLength = length;
}

void PhysicSimulation::initiateGraph(Graph& g) {

    //retrieve the total number of subreddits
    //int totalSubreddits = g.getSubs();

    // if (g == NULL) {
    //     return;
    // }

    //retrieve the collection of subreddits
    map<string, Graph::SubReddit*> subreddits = g.getSubReddits();
    //setting the common position
    float x = 0;
    float y = 0;
    //for each subreddit, we insert the value with 
    for(map<string, Graph::SubReddit*>::iterator it = subreddits.begin(); it != subreddits.end(); it++) {
        //check to make sure each entry is not null
        x++;
        if (x >= sqrt(g.getSubs())) {
            y++;
            x = 0;
        }
        if (it -> second != NULL) {
            positions.insert(pair<Graph::SubReddit*, pair<float, float>>(it -> second, make_pair(x,y)));
        }
    }
    
}

map<Graph::SubReddit*, pair<float, float>> PhysicSimulation::simulateFor(int seconds) {
    map<Graph::SubReddit*, pair<float, float>> new_positions;

    ofstream newCoords("coordOutputSeconds.txt");

    //loop through the amount of seconds
    for (int i = 0; i < seconds; i++) {
        newCoords << "At Second: " << i + 1 << endl;
        for (map<Graph::SubReddit*, pair<float, float>>::iterator it = positions.begin(); it != positions.end(); it++) {
            
            //finding individual coordinates for current node
            float cX = it -> second.first;
            float cY = it -> second.second;

            //create our force vector
            std::pair<float, float> force_vector(0, 0);

            //create a subreddit pointer for traversing adjacent nodes
            Graph::SubReddit* subPtr = it -> first;

            //loop through adjacent nodes map
            for (map<Graph::SubReddit*, int>::iterator n = subPtr -> adjacent.begin(); n != subPtr -> adjacent.end(); n++) {
                //need to find the position vector for the adjacent node
                Graph::SubReddit* ptr = n -> first;

                map<Graph::SubReddit*, pair<float, float>>::iterator iter = positions.find(ptr);
                
                //finding individual coordinates for adjacent node
                float aX = iter -> second.first;
                float aY = iter -> second.second;

                //squaring the coordinate differences
                float squared_x = pow(aX - cX, 2);
                float squared_y = pow(aY - cY, 2);

                //calculate the distance
                float distance = sqrt(squared_x + squared_y);
                
                //calculate the unit vector
                std::pair<float, float> unit_vector;
                if (distance == 0) {
                    srand(rand());
                    int angle = rand();
                    unit_vector = make_pair(cos(angle),sin(angle));
                } else {
                    unit_vector = make_pair((aX - cX) / distance, (aY - cY)/distance);
                }
                //compute spring force vector formula

                float spring_force_value_x = -(distance - springNaturalLength) * springCoefficient * unit_vector.first;
                float spring_force_value_y = -(distance - springNaturalLength) * springCoefficient * unit_vector.second;

                //update the force vector
                force_vector.first += spring_force_value_x*n->second;
                force_vector.second += spring_force_value_y*n->second;
            }

            //insert all the data into our newly created map
            new_positions[it -> first].first = force_vector.first + cX;
            new_positions[it -> first].second = force_vector.second + cY;
            newCoords << "X: " << new_positions[it->first].first << " Y: " << new_positions[it->first].second << endl;
        }
        positions = new_positions;
    }

    return positions;
}
