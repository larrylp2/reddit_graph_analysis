#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>

//#include "Graph.h"

const string SUBREDDIT_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/subreddit_text/";
const string USER_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/subreddit_text/";
const string JSON_SUFFIX = ".json";
using namespace std;

class GraphBuilder {

    public:
        struct SubReddit {
            string name;
            vector<string> users;
            vector<SubReddit*> adjacentSubReddits;
            map<string, pair<SubReddit*, int>> a;
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



        /*
         * Reads in from a user file subreddit names, initializing new subreddits if necessary
         * @param file_name the name of the inital file to be read in
         */
        //void PopulateSubreddits(string file_name);

        /*
         * Gets the SubReddit pointer for a subreddit name from the map of unique subreddits
         * @param subReddit the name of the subreddit to find
         * @return the pointer to the input subReddit if found, NULL if not found
         */
        SubReddit* getSubReddit(string subReddit) const;

        void BFSTraversal() const; //Write to a txt file all the nodes in the graph+

    private:
        // Contain the directory to the data source so we can easily change which tests, sources we use
        // Example: data-fetching/data, test/test1, test/test2
        string source;
        
        map<string, SubReddit*> unique_subreddits;

        map<string, bool> checked_users; // A map store checked user to ensure no user is checked twice


        // Add weight to the connection between two subreddits
        // If a subreddit isn't exist yet, create new SubReddit* and add to unique_subreddits
        void addWeight(string subreddit1, string subreddit2);
        // List version of addWeight, which call addWeight to all pairs in the list
        void addWeightToList(vector<string> subreddit_list); 


        // Search the file in source/subreddit_text and return the list
        // Return empty vector if not found
        vector<string> getUserListFromSubredditFile(string sureddit_name) const;
        
        // Search the file in source/user_text and return the list
        // Return empty vector if not found
        vector<string> getSubRedditListFromUserFile(string user_name) const;

        

};