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
        Graph();

        Graph(string source_directory); //Construct with the directory

        ~Graph(); //destructor

        // Read and construct the graph, which calls populateSubReddits to all subreddits
        void readGraphBFS(string start);

        vector<string> BFSTraversal(string start) const; //Converts the graph into a vector of nodes through a BFS traversal starting from a certain node

        //Helper function that retrieves the pointer to a subreddit based on its name, creating a new SubReddit struct if that subreddit does not already exist
        SubReddit* retrieveSubreddit(string name);

        //Helper function that only retrives the pointer based on the name, returning NULL if the sub does not exist
        SubReddit* getSubReddit(string name) const;

        int getUsers() const;

        int getSubs() const;

        map<string, Graph::SubReddit*> getSubReddits() const;

        //Helper function that retrieves the number of shared users between two subreddits
        int commonUsers(string sub1, string sub2) const;

        //Return the shortest path weight from subreddit1 to subreddit2
        map<string, double> dijkstra(string start);
    private:    
        //class that reads subreddit and user text files
        FileReader reader;
        
        map<string, SubReddit*> unique_subreddits; //a map to keep track of subreddit object pointers (vertices)

        set<string> checked_users; // A set to store users that have already been checked

        set<string> read_subs; // A set to store subs that have already been stored

        void populateSubreddit(string name); 

        // List version of connectSubreddits, which calls connectSubreddits to all pairs in the list
        void connectSubRedditList(set<string> subreddit_list); 

        //helper function that adds edges between two subreddits (assume that sub1 and sub2 already exist in unique_subreddits)
        void connectSubreddits(SubReddit* sub1, SubReddit* sub2);

        // private helper method that clears allocated heap memory
        void clear();  

};