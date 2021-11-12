#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

//file to test out reading in the text data
//tried to read in json data, did not work
//also used to test out compiling the data using clang++

int main() {
    std::cout << "start" << std::endl;

    //std::string file_path = "khanhn2-mohanty7--larrylp2/data-fetching/data/subreddit/UIUC.json";
    std::string file_path = "data-fetching/data/user_text/24thpanda.txt";
    std::ifstream file(file_path);

    //read it line by line
    std::string user;
    if(file.is_open()) {
        std::cout << "open" << std::endl;
        while(getline(file, user)) {
            std::cout << user << std::endl;

        }
    } 

    return 0;
}