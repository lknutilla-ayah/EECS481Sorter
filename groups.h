//code by: Laura Knutilla
#ifndef GROUPS
#define GROUPS

#include "preferences.h"

#include <unordered_map>
#include <string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;

struct Student {
    bool survey;
    bool preferred;
    string umid;
    string first_choice;
    string second_choice;
    string third_choice;
};

struct Group {
    int count;
    vector<Student>members;
};

class Groups {
public:
    bool count_flag;
    int round;
    int pass;
    unordered_map<string, Group> teams; 
    Preference preferences;

    Groups();
    void makeGroups(string &, string &);
    void makePrefGroups(string &);
    void starPreferred();
    void placeNone();
    void sortTeams();
    void moveLateSurveys(string &);
    void move2Second(string &);
    void moveSmall(string &);
    void checkCount();
    void printGroups();
};

#endif
