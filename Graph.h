#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <set>
#include <queue>

//#include "Graph.h"

using namespace std;

//const string SUBREDDIT_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/subreddit_text_new/";
//const string USER_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/user_text_new/";
const string SUBREDDIT_DATA_PATH = "subreddit_text_new/";
const string USER_DATA_PATH = "user_text_new/";
const string JSON_SUFFIX = ".json";
const string TXT_SUFFIX = ".txt";

class GraphBuilder {

    public:
        struct SubReddit {
            string name;
            map<SubReddit*, int> adjacent; //key is the pointer to an adjacent subreddit, value is the strength of the connection
        };

        GraphBuilder();
        GraphBuilder(string source_directory); //Construct with the directory

        // Read and construct the graph, which calls populateSubReddits to all subreddits
        void readGraph(string start);

        void readGraphBFS(string start);

        void BFSTraversal() const; //Write to a txt file all the nodes in the graph+

        //Helper function that retrieves the pointer to a subreddit based on its name, creating a new SubReddit struct if that subreddit does not already exist
        SubReddit* retrieveSubreddit(string name);

    private:
        // Contain the directory to the data source so we can easily change which tests, sources we use
        // Example: data-fetching/data, test/test1, test/test2
        string source;
        
        map<string, SubReddit*> unique_subreddits; //a map to keep track of subreddit object pointers (vertices)

        //map<pair<SubReddit*, SubReddit*>, int> edges; //a set to keep track of the list of edges and their strengths

        set<string> checked_users; // A set to store users that have already been checked

        set<string> read_subs; // A set to store subs that have already been stored

        // More readable version of populateSubReddits and will replace that version after implemented
        // Maybe put in private since this will be called in readGraph
        void populateSubreddit(string name); 

        // List version of connectSubreddits, which calls connectSubreddits to all pairs in the list
        void connectSubRedditList(vector<string> subreddit_list); 

        //helper function that adds edges between two subreddits (assume that sub1 and sub2 already exist in unique_subreddits)
        void connectSubreddits(SubReddit* sub1, SubReddit* sub2);

        // Search the file in source/subreddit_text and return the list
        // Return empty vector if not found
        vector<string> getUserListFromSubRedditFile(string sureddit_name) const;
        
        // Search the file in source/user_text and return the list
        // Return empty vector if not found
        vector<string> getSubRedditListFromUserFile(string user_name) const;

        

};