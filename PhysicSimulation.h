#include "Graph.h"

class PhysicSimulation {
    public:
        PhysicSimulation();
        PhysicSimulation(float coefficient, float length); //Constructor that initialize coefficient and length, time = 0

        void initiateGraph(Graph &g); // Initiate with a graph, initialize all positions to (0,0) or random

        // Run simulation from current positions and return new position after simulated for some seconds
        // Can be run sequentially: For example:
        // simulateFor(5);
        // simulateFor(5); //Simulate for another 5 seconds
        // 
        // This way we can output an animation if we want:
        // gif;
        // for (int i = 0; i < 120; i++) {
        //      gif.addFrame(drawGraph(simulateFor(1)));
        // }
        // return gif;
        map<Graph::SubReddit*, pair<float, float>> simulateFor(int seconds);
        // Outline of simulateFor(int seconds):
        // 
        // loop for (seconds):
        // For each Graph::Subreddit* A in positions:
        //      forceVector = (0,0);
        //      For each adjacent node N:
        //          int distance = distance between A and N;
        //          compute spring force vector between A and N based on distance, natural length and coefficient and direction
        //          then add to forceVector
        //      translate A positions by forceVector
        
    private:
        float springCoefficient;
        float springNaturalLength;
        int time;
        map<Graph::SubReddit*, pair<float, float>> positions;
};
