#include "../include/Graph.h"


GraphBuilder::GraphBuilder() {
    //default constructor
}

GraphBuilder::GraphBuilder(string source_directory) {
    source = source_directory;
}

GraphBuilder::SubReddit* GraphBuilder::retrieveSubreddit(string subName) {
    //start by checking if the subreddit already exists in our map
    map<string, SubReddit*>::iterator iterator = unique_subreddits.find(subName);
    if(iterator != unique_subreddits.end()) {
        //subreddit already exists
        return iterator->second;
    } else {
        //subreddit does not exist
        SubReddit* newSub = new SubReddit();
        newSub->name = subName;
        unique_subreddits.insert(pair<string, SubReddit*>(subName, newSub));
        return newSub; //return a pointer to the newly created subreddit struct
    }
}

void GraphBuilder::connectSubreddits(SubReddit* sub1, SubReddit* sub2) {

    //check if the two are already connected (assume that if sub1 is adjacent to sub2, sub2 is adjacent to sub1)
    map<SubReddit*, int>::iterator iterator = sub1->adjacent.find(sub2);
    if(iterator != sub1->adjacent.end()) { //the connection already exists
        //increment the int
        iterator->second++;
        sub2->adjacent.find(sub1)->second++;
    } else { //otherwise make a new connection
        sub1->adjacent.insert(pair<SubReddit*, int>(sub2, 1));
        sub2->adjacent.insert(pair<SubReddit*, int>(sub1, 1));
    }
}

void GraphBuilder::connectSubreddits(vector<SubReddit*> subs) {
    for(int i = 0; i < subs.size(); i++) {
        for(int j = i + 1; j < subs.size(); j++) {
            connectSubreddits(subs[i], subs[j]); //simple algoritm to connect each subreddit with each other
        }
    }
}

void GraphBuilder::populateSubReddits(std::string file_name) {
    //our file_name for this includes the name of the subreddit in question
    string subReddit = file_name.substr(0, file_name.size() - 5); // the ".json" portion is size 5
    
    //the subreddit that our initial call was done from
    SubReddit* original = retrieveSubreddit(subReddit);

    ifstream sub_file(SUBREDDIT_DATA_PATH + file_name); //gets the relative path to the subreddit filename
    //read it line by line
    string user;
    if(sub_file.is_open()) {
        while(getline(sub_file, user)) {
            //first line of the .txt file is '0'
            if(user != "0") {
                //check to see if this user has already been checked
                if(checked_users.find(user) != checked_users.end()) {
                    //this user has already been handled, do nothing
                } else {
                    //this user has not yet been handled, start process after adding this user to the list of already checked users
                    checked_users.insert(user);
                    original->users.insert(user); //add this user to the set of users seen active on this subreddit

                    string user_file_name = user + TXT_SUFFIX;

                    ifstream user_file(USER_DATA_PATH + user_file_name);
                    string newSubReddit; //new subreddits that this user is active in
                    vector<SubReddit*> subs; //keep track of all subreddits that this user is active in that is not our initial subreddit

                    if(user_file.is_open()) {
                        while(getline(user_file, newSubReddit)) {
                            //first line of the .txt file is '0'
                            if(newSubReddit != "0") {
                                //only do stuff if this subReddit is not our starting subreddit
                                if(newSubReddit != subReddit) {
                                    
                                    //get a pointer to the subreddit this user is active in
                                    SubReddit* current = retrieveSubreddit(newSubReddit);

                                    //update the adjacent subreddits
                                    connectSubreddits(original, current);

                                    subs.push_back(current);

                                    //call populateSubReddits recursively on this new subreddit
                                    populateSubReddits(newSubReddit + TXT_SUFFIX);
                                }
                            }
                        }
                    }

                    //now connect all of the subreddits this user is active in to each other
                    connectSubreddits(subs);   
                }
            }
        }
    }
}


void GraphBuilder::toBeImplementedPopulateSubreddit(std::string name) {
    // name is the name of the subreddit, example: UIUC

    vector<string> user_list = getUserListFromSubRedditFile(name);
    for (string u : user_list) {
        if (checked_users.find(u) != checked_users.end()) { // If the user hasn't been checked
            addWeightToList(getSubRedditListFromUserFile(u));
        }
    }
}

void GraphBuilder::readGraph(string root) {
    // Create a new SubReddit of root and append to unique_subreddits
    // Then call toBeImplementedPopulateSubreddit() to all the name in the unique_subreddits
    // Be sure to not call it twice on one subreddit by making a map to keep track
    toBeImplementedPopulateSubreddit(root);
    SubReddit* rootSub = unique_subreddits.find(root)->second;
    read_subs.insert(rootSub);
    for(map<SubReddit*, int>::iterator it = rootSub->adjacent.begin(); it != rootSub->adjacent.end(); it++) {
        if(read_subs.find(it->first) != read_subs.end()) { //already read this subreddit 
            //do nothing
        } else {
            //recursively read this next subreddit
            readGraph(it->first->name);
        }
    }
}

// List version of addWeight, which call addWeight to all pairs in the list
void GraphBuilder::addWeightToList(vector<string> subreddit_list) {
    vector<SubReddit*> subs;
    for(int i = 0; i < subreddit_list.size(); i++) {
        subs.push_back(retrieveSubreddit(subreddit_list[i]));
    }

    for(int i = 0; i < subs.size(); i++) {
        for(int j = i + 1; j < subs.size(); j++) {
            connectSubreddits(subs[i], subs[j]); //simple algoritm to connect each subreddit with each other
        }
    }
}


// Search the file in source/subreddit_text and return the list
// Return empty vector if not found
vector<string> GraphBuilder::getUserListFromSubRedditFile(string subreddit) const {
    vector<string> users;
    
    string user;
    ifstream sub_file(SUBREDDIT_DATA_PATH + subreddit + TXT_SUFFIX); //gets the relative path to the subreddit filename
    if(sub_file.is_open()) {
        while(getline(sub_file, user)) {
            if(user != "0") {
                users.push_back(user);
            }
        }
    }
    return users;
}
        
// Search the file in source/user_text and return the list
// Return empty vector if not found
vector<string> GraphBuilder::getSubRedditListFromUserFile(string username) const {
    vector<string> subs;
    
    string sub;
    ifstream user_file(USER_DATA_PATH + username + TXT_SUFFIX); //gets the relative path to the subreddit filename
    if(user_file.is_open()) {
        while(getline(user_file, sub)) {
            if(sub != "0") {
                subs.push_back(sub);
            }
        }
    }
    return subs;
}
