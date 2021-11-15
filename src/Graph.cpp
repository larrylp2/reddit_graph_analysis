#include "../include/Graph.h"


GraphBuilder::GraphBuilder() {
    //default constructor
}

void GraphBuilder::populateSubReddits(std::string file_name) {
    //our file_name for this includes the name of the subreddit in question
    std::string subReddit = file_name.substr(0, file_name.size() - 5); // the ".json" portion is size 5
    
    //start by checking if the subreddit already exists in our map
    std::map<std::string, SubReddit*>::iterator iterator = unique_subreddits.find(subReddit);
    if(!(iterator != unique_subreddits.end())) {
        //subreddit does not exist
        SubReddit* newSub = new SubReddit();
        newSub->name = subReddit;
        unique_subreddits.insert(std::pair<std::string, SubReddit*>(subReddit, newSub));
    }

    //the subreddit that our initial call was done from
    SubReddit* original = unique_subreddits.find(subReddit)->second;

    std::ifstream sub_file(SUBREDDIT_DATA_PATH + file_name);
    //read it line by line
    std::string user;
    if(sub_file.is_open()) {
        while(getline(sub_file, user)) {
            unique_subreddits.find(subReddit)->second->users.push_back(user); //add all of the users to the vector
            //then load in the subreddits used the current user
            //add connections between this current subreddit and each subreddit read in by the current user
            //load in the user file
            std::string user_file_name = user + JSON_SUFFIX;

            //TODO: need to add a check if the user file is valid IMPORTANT!!!!!!
            std::ifstream user_file(USER_DATA_PATH + user_file_name);
            std::string newSubReddit;
            if(user_file.is_open()) {
                while(getline(user_file, newSubReddit)) {
                    //only do stuff if this subReddit is not our starting subreddit
                    if(newSubReddit != subReddit) {
                        //first add the newSubReddit to the list the unique subreddits if it does not already exist
                        std::map<std::string, SubReddit*>::iterator user_iterator = unique_subreddits.find(newSubReddit);
                        if(!(user_iterator != unique_subreddits.end())) {
                            //it does not exist, add it to the list of unique SubReddits
                            SubReddit* addSub = new SubReddit();
                            addSub->name = newSubReddit;
                            unique_subreddits.insert(std::pair<std::string, SubReddit*>(newSubReddit, addSub));
                        }

                        //now update the adjacency lists for both subreddits, the 'subReddit' that we loaded in users from
                        //and the 'newSubReddit' that we read from a user

                        //get the pointers to the subreddits
                        SubReddit* current = unique_subreddits.find(newSubReddit)->second;

                        //update the adjacency lists
                        current->adjacentSubReddits.push_back(original);
                        original->adjacentSubReddits.push_back(current);
                    }
                }
            }
        }
    }
}

GraphBuilder::SubReddit* GraphBuilder::getSubReddit(std::string subReddit) {
    std::map<std::string, SubReddit*>::iterator user_iterator = unique_subreddits.find(subReddit);
    
    //use ternary operator
    //if the subreddit was found, the retValue is the pointer, otherwise it is the NULL
    SubReddit* retValue = (user_iterator != unique_subreddits.end()) ? user_iterator->second : NULL;
    return retValue;
}


//bottom is no longer needed
/*
void GraphBuilder::PopulateSubreddits(std::string file_name) {
    std::ifstream file(USER_DATA_PATH + file_name);

    //read it line by line
    std::string subReddit;
    if(file.is_open()) {
        while(getline(file, subReddit)) {
            //check if the subreddit already exists in our map tracking unique subreddits
            std::map<std::string, SubReddit*>::iterator iterator = unique_subreddits.find(subReddit);

            if(iterator != unique_subreddits.end()) {
                //if it already exists, add the user this file is associated with as one of the users of this SubReddit
                iterator->second->users.push_back(file_name.substr(0, file_name.size() - 5)); //make a substring that is 5 smaller to remove the .json and isolate the username
            } else {
                //if it does not exist, add it to the running list of subreddits
                SubReddit* newSub = new SubReddit();
                newSub->name = subReddit;
                unique_subreddits.insert(std::pair<std::string, SubReddit*>(subReddit, newSub));
            }

        }
    } 
} */