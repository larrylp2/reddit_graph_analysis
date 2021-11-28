#include "../include/Graph.h"


GraphBuilder::GraphBuilder() {
    //default constructor
}

GraphBuilder::GraphBuilder(string source_directory) {
    source = source_directory;
}

void GraphBuilder::readGraph(string root) {
    // Create a new SubReddit of root and append to unique_subreddits
    // Then call populate() to all the name in the unique_subreddits
    // Be sure to not call it twice on one subreddit by making a map to keep track
    populateSubreddit(root);
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

void GraphBuilder::populateSubreddit(std::string name) {
    // name is the name of the subreddit, example: UIUC

    vector<string> user_list = getUserListFromSubRedditFile(name);
    for (string u : user_list) {
        if (checked_users.find(u) != checked_users.end()) { // If the user hasn't been checked
            connectSubRedditList(getSubRedditListFromUserFile(u));
        }
    }
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

// List version of addWeight, which call addWeight to all pairs in the list
void GraphBuilder::connectSubRedditList(vector<string> subreddit_list) {
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
