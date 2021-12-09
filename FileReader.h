#pragma once
#include <vector>
#include <fstream>

using namespace std;
//class that reads in subreddit and user files

//const string SUBREDDIT_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/subreddit_text_new/";
//const string USER_DATA_PATH = "khanhn2-mohanty7--larrylp2/data-fetching/data/user_text_new/";
const string SUBREDDIT_DATA_PATH = "subreddit_text/";
const string USER_DATA_PATH = "user_text/";
const string JSON_SUFFIX = ".json";
const string TXT_SUFFIX = ".txt";

class FileReader {
    public:
        FileReader();
        FileReader(string file_path);

        // Search the file in source/subreddit_text and return the list
        // Return empty vector if not found
        vector<string> getUserListFromSubRedditFile(string subreddit_name) const;
        
        // Search the file in source/user_text and return the list
        // Return empty vector if not found
        vector<string> getSubRedditListFromUserFile(string user_name) const;

    private:
        // Contain the directory to the data source so we can easily change which tests, sources we use
        // Example: data-fetching/data, test/test1, test/test2
        string source;
};