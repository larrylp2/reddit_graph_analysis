#include "Graph.h"

Graph::Graph() {
    //default constructor
}

Graph::Graph(string source_directory) {
    source = source_directory;
}
/* this would segfault
void Graph::readGraph(string root) {
    populateSubreddit(root);
    SubReddit* rootSub = unique_subreddits.find(root)->second;
    read_subs.insert(rootSub->name);
    std::cout << "Populated: " << read_subs.size() << std::endl;
    for(map<SubReddit*, int>::iterator it = rootSub->adjacent.begin(); it != rootSub->adjacent.end(); it++) {
        if(read_subs.find(it->first->name) != read_subs.end()) { //already read this subreddit 
            //do nothing
        } else {
            //recursively read this next subreddit
            readGraph(it->first->name);
        }
    }
}*/

void Graph::readGraphBFS(string root) {
    queue<string> subReddit;
    subReddit.push(root);
    int pop = 1;
    while(!subReddit.empty()) {
        //populate the subreddit in the front of the qeueu
        string sub = subReddit.front();
        pop++;
        subReddit.pop();
        populateSubreddit(sub);
        SubReddit* subPtr = retrieveSubreddit(sub);
        std::cout << "Populated: " << pop << std::endl;
        //now add the adjacent ones to the queue
        for(map<SubReddit*, int>::iterator it = subPtr->adjacent.begin(); it != subPtr->adjacent.end(); it++) {
            if(read_subs.find(it->first->name) != read_subs.end()) { //already read this subreddit 
                //do nothing
            } else {
                //recursively read this next subreddit
                subReddit.push(it->first->name);
                read_subs.insert(it->first->name);
            }
        }
    }
}

void Graph::BFSTraversal() const {
    queue<string> subReddit;
    subReddit.push("UIUC");
    set<string> seen_subs; // A set to store subs that have already been seen
    ofstream BFSOutput("BFSResults.txt");
    BFSOutput << "UIUC" << std::endl;

    while(!subReddit.empty()) {
        string sub = subReddit.front();
        subReddit.pop();
        SubReddit* subPtr = unique_subreddits.find(sub)->second;
        //now add the adjacent ones to the queue
        for(map<SubReddit*, int>::iterator it = subPtr->adjacent.begin(); it != subPtr->adjacent.end(); it++) {
            if(seen_subs.find(it->first->name) != seen_subs.end()) { //already read this subreddit 
                //do nothing
            } else {
                //recursively read this next subreddit
                BFSOutput << it->first->name << std::endl;
                seen_subs.insert(it->first->name);
            }
        }
    }
}

void Graph::populateSubreddit(std::string name) {
    // name is the name of the subreddit, example: UIUC

    vector<string> user_list = getUserListFromSubRedditFile(name);
    //std::cout << "User Size: " << user_list.size() << std::endl;
    for (int i = 0; i < (int)user_list.size(); i++) {
        string u = user_list[i];
        if (checked_users.find(u) != checked_users.end()) { 
            //if the user has already been checked and exists in the set of checked users, do nothing
        } else { //if the user has not yet been checked
            connectSubRedditList(getSubRedditListFromUserFile(u));
            checked_users.insert(u);
        }
    }
}

Graph::SubReddit* Graph::retrieveSubreddit(string subName) {
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

int Graph::getUsers() const {
    return checked_users.size();
}

int Graph::getSubs() const {
    return read_subs.size();
}

void Graph::printMaxConnection() const {
    std::cout << "Max Connection: " << max_connection << std::endl;
    std::cout << "Sub1: " << best1 << " Sub2: " << best2 << std::endl;
}

void Graph::connectSubreddits(SubReddit* sub1, SubReddit* sub2) {

    //check if the two are already connected (assume that if sub1 is adjacent to sub2, sub2 is adjacent to sub1)
    map<SubReddit*, int>::iterator iterator = sub1->adjacent.find(sub2);
    if(iterator != sub1->adjacent.end()) { //the connection already exists
        //increment the int
        iterator->second++;
        sub2->adjacent.find(sub1)->second++;

        if(iterator->second > max_connection) {
            max_connection = iterator->second;
            best1 = sub1->name;
            best2 = sub2->name;
        }
    } else { //otherwise make a new connection
        sub1->adjacent.insert(pair<SubReddit*, int>(sub2, 1));
        sub2->adjacent.insert(pair<SubReddit*, int>(sub1, 1));
    }
}

// List version of addWeight, which call addWeight to all pairs in the list
void Graph::connectSubRedditList(vector<string> subreddit_list) {
    vector<SubReddit*> subs;
    for(int i = 0; i < (int) subreddit_list.size(); i++) {
        subs.push_back(retrieveSubreddit(subreddit_list[i]));
    }

    for(int i = 0; i < (int) subs.size(); i++) {
        for(int j = i + 1; j < (int) subs.size(); j++) {
            connectSubreddits(subs[i], subs[j]); //simple algoritm to connect each subreddit with each other
        }
    }
}


// Search the file in source/subreddit_text and return the list
// Return empty vector if not found
vector<string> Graph::getUserListFromSubRedditFile(string subreddit) const {
    vector<string> users;
    
    string user;
    //std::cout << "File: " << source + SUBREDDIT_DATA_PATH + subreddit + TXT_SUFFIX << std::endl;
    ifstream sub_file(source + SUBREDDIT_DATA_PATH + subreddit + TXT_SUFFIX); //gets the relative path to the subreddit filename
    if(sub_file.is_open()) {
        //std::cout << "File Open" << std::endl;
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
vector<string> Graph::getSubRedditListFromUserFile(string username) const {
    vector<string> subs;
    
    string sub;
    ifstream user_file(source + USER_DATA_PATH + username + TXT_SUFFIX); //gets the relative path to the subreddit filename
    if(user_file.is_open()) {
        while(getline(user_file, sub)) {
            if(sub != "0") {
                subs.push_back(sub);
            }
        }
    }
    return subs;
}

double Graph::dijkstra(string subreddit1, string subreddit2) {
    //Comparision class
    class compareSubreddit {
        public:
            bool operator()( const pair<SubReddit*, double>& lhs, const pair<SubReddit*, double>& rhs ) const {
                if (lhs.second == -1) {
                    return false;
                }
                if (rhs.second == -1) {
                    return true;
                }
                if (lhs.second < rhs.second) {
                    return true;
                }
                return false;
            }
    };
    //Make vector
    vector<pair<SubReddit*, double>> subredditList = vector<pair<SubReddit*, double>>();
    for (pair<string, SubReddit*> s : unique_subreddits) {
        if (s.first == subreddit1) {
            subredditList.push_back(make_pair(s.second, 0));
        } else {
            subredditList.push_back(make_pair(s.second, -1));
        }
    }
    //Construct heap/priority queue



    
    return 0;
}