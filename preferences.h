//code by Laura Knutilla
#ifndef PREFERENCES
#define PREFERENCES

#include <unordered_map>
#include <string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Preference {
public:
    unordered_map <string, vector<string>> pref_map;

    void makePreferenceMap(string &);

};

#endif
