#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <set>

//#include "Graph.h"

const string SUBREDDIT_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/subreddit_text_new/";
const string USER_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/subreddit_text_new/";
const string JSON_SUFFIX = ".json";
const string TXT_SUFFIX = ".txt";
using namespace std;

class GraphBuilder {

    public:
        struct SubReddit {
            string name;
            set<string> users;
            map<SubReddit*, int> adjacent; //key is the pointer to an adjacent subreddit, value is the strength of the connection
        };

        GraphBuilder();
        GraphBuilder(string source_directory); //Construct with the directory

        /*
         * Reads in from subreddit file usernames, adding those users to the current subreddit then calling populate subreddits on each user
         *
         */
        void populateSubReddits(string file_name);

        // More readable version of populateSubReddits and will replace that version after implemented
        // Maybe put in private since this will be called in readGraph
        void toBeImplementedPopulateSubreddit(string name); 

        // Read and construct the graph, which calls populateSubReddits to all subreddits
        void readGraph(string start);


        //Helper function that retrieves the pointer to a subreddit based on its name, creating a new SubReddit struct if that subreddit does not already exist
        SubReddit* retrieveSubreddit(string name);


        //helper function that adds edges between two subreddits (assume that sub1 and sub2 already exist in unique_subreddits)
        void connectSubreddits(SubReddit* sub1, SubReddit* sub2);

        //helper function that adds edges between all subreddits in a vector
        void connectSubreddits(vector<SubReddit*> subs);
        

        /*
         * Reads in from a user file subreddit names, initializing new subreddits if necessary
         * @param file_name the name of the inital file to be read in
         */
        //void PopulateSubreddits(string file_name);
 

        void BFSTraversal() const; //Write to a txt file all the nodes in the graph+

    private:
        // Contain the directory to the data source so we can easily change which tests, sources we use
        // Example: data-fetching/data, test/test1, test/test2
        string source;
        
        map<string, SubReddit*> unique_subreddits; //a map to keep track of subreddit object pointers (vertices)

        map<pair<SubReddit*, SubReddit*>, int> edges; //a set to keep track of the list of edges and their strengths

        set<string> checked_users; // A set to store users that have already been checked


        // Add weight to the connection between two subreddits
        // If a subreddit isn't exist yet, create new SubReddit* and add to unique_subreddits
        void addWeight(string subreddit1, string subreddit2);
        // List version of addWeight, which call addWeight to all pairs in the list
        void addWeightToList(vector<string> subreddit_list); 


        // Search the file in source/subreddit_text and return the list
        // Return empty vector if not found
        vector<string> getUserListFromSubRedditFile(string sureddit_name) const;
        
        // Search the file in source/user_text and return the list
        // Return empty vector if not found
        vector<string> getSubRedditListFromUserFile(string user_name) const;

        

};