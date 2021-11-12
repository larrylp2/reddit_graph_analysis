#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>

//#include "Graph.h"

const std::string SUBREDDIT_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/subreddit_text/";
const std::string USER_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/subreddit_text/";
const std::string JSON_SUFFIX = ".json";


class GraphBuilder {

    public:
        struct SubReddit {
            std::string name;
            std::vector<std::string> users;
            std::vector<SubReddit*> adjacentSubReddits;
        };

        GraphBuilder();

        /*
         * Reads in from subreddit file usernames, adding those users to the current subreddit then calling populate subreddits on each user
         *
         */
        void populateSubReddits(std::string file_name);

        /*
         * Reads in from a user file subreddit names, initializing new subreddits if necessary
         * @param file_name the name of the inital file to be read in
         */
        //void PopulateSubreddits(std::string file_name);

        /*
         * Gets the SubReddit pointer for a subreddit name from the map of unique subreddits
         * @param subReddit the name of the subreddit to find
         * @return the pointer to the input subReddit if found, NULL if not found
         */
        SubReddit* getSubReddit(std::string subReddit);

    private:
        //create a map with pointers to subreddit nodes as values and subreddit names as keys
        std::map<std::string, SubReddit*> unique_subreddits;

};