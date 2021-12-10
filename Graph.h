#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <set>
#include <queue>

#include "FileReader.h"

using namespace std;

class Graph {
    public:

        struct SubReddit {
            string name;
            map<SubReddit*, int> adjacent;
        };
        Graph(string source_directory); //Construct with the directory

        ~Graph(); //destructor

        // Read and construct the graph, which calls populateSubReddits to all subreddits
        void readGraphBFS(string start);

        vector<string> BFSTraversal(string start) const; //Converts the graph into a vector of nodes through a BFS traversal starting from a certain node

        void BFSToFile() const;

        //Helper function that retrieves the pointer to a subreddit based on its name, creating a new SubReddit struct if that subreddit does not already exist
        SubReddit* retrieveSubreddit(string name);

        //Helper function that only retrives the pointer based on the name, returning NULL if the sub does not exist
        SubReddit* getSubReddit(string name) const;

        int getUsers() const;

        int getSubs() const;

        void printMaxConnection() const;

        int getMaxConnection() const;

        map<string, Graph::SubReddit*> getSubReddits() const;

        //Helper function that retrieves the number of shared users between two subreddits
        int commonUsers(string sub1, string sub2) const;

        //Return the shortest path weight from subreddit1 to subreddit2
        map<string, double> dijkstra(string start);
        map<string, double> badDijkstra(string start);
    private:    
        //class that reads subreddit and user text files
        FileReader reader;

        int max_connection = 0;

        string best1 = "";
        string best2 = "";
        
        map<string, SubReddit*> unique_subreddits; //a map to keep track of subreddit object pointers (vertices)

        //map<pair<SubReddit*, SubReddit*>, int> edges; //a set to keep track of the list of edges and their strengths

        set<string> checked_users; // A set to store users that have already been checked

        set<string> read_subs; // A set to store subs that have already been stored

        // More readable version of populateSubReddits and will replace that version after implemented
        // Maybe put in private since this will be called in readGraph
        void populateSubreddit(string name); 

        // List version of connectSubreddits, which calls connectSubreddits to all pairs in the list
        void connectSubRedditList(set<string> subreddit_list); 

        //helper function that adds edges between two subreddits (assume that sub1 and sub2 already exist in unique_subreddits)
        void connectSubreddits(SubReddit* sub1, SubReddit* sub2);

        // private helper method that clears allocated heap memory
        void clear();

        

};