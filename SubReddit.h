#pragma once
#include <string>
#include <map>

using namespace std;

struct SubReddit {
    string name;
    map<SubReddit*, int> adjacent;
};