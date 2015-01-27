//code by: Laura Knutilla
#include "groups.h"

Groups::Groups() {
    this->count_flag = false;
}

void Groups::makeGroups(string &inFile, string&prefFile) {
    //makes a first round bunch of groups purely based on first preference
    makePrefGroups(inFile);
    //if groups are over 5
    //PASS 1: puts student in 2nd choice
    //ROUND 1: will move students with late surveys
    //ROUND 2: will move students to their second choice if the group is < 3
    //ROUND 3-4: puts students in second choice groups of increasing size
    //PASS 2: reapeats pass 1 but puts students in 3rd choice
    for (pass = 1; pass < 3 && count_flag; ++pass) {
        round = 1;
        //moves students who turned surveys in late to 2nd/3rd choice
        if (count_flag) {
            preferences.makePreferenceMap(prefFile);
            sortTeams();
        }
        checkCount();
        round = 2;
        //if groups are still over 5, will scan large groups
        //and move students in order (except preferred) to open 2nd/3rd choice
        if (count_flag) {
            sortTeams();
        }
        round = 3;
        //if groups are still over 5, will scan large groups
        //and move students in order (except preferred) to open 2nd/3rd choice
        if (count_flag) {
            sortTeams();
        }
        round = 4;
        //if groups are still over 5, will scan large groups
        //and move students in order (except preferred) to open 2nd/3rd choice
        if (count_flag) {
            sortTeams();
        }
    }
    placeNone();


}

void Groups::makePrefGroups(string & inFile) {
//places students in their first choice group
    string line;
    ifstream groupFile(inFile);
    if (groupFile.is_open()) {
        while (getline(groupFile,line)) {
            Student student;
            stringstream ss1;
            ss1 << line;
            ss1 >> student.umid >> student.survey >> student.first_choice >> student.second_choice >> student.third_choice;
            if (student.first_choice == "") {
                student.first_choice = "None";
                student.second_choice = "None";
                student.third_choice = "None";
            }
            ++teams[student.first_choice].count;
            teams[student.first_choice].members.push_back(student);
            //will alert count flag if any team is over 5
            if (teams[student.first_choice].count > 5) {
                count_flag = true;
            }
        }
    }
}

void Groups::starPreferred() {
//marks students who are preferred
    //initialize preferred map
    for (auto itr = teams.begin(); itr != teams.end(); ++itr ) {
        for (auto i = teams[itr->first].members.begin(); i != teams[itr->first].members.end(); ++i) {
            i->preferred = false;
        }
    }
    //mark preferred
    for (auto itr = teams.begin(); itr != teams.end(); ++itr ) {
        if (preferences.pref_map.find(itr->first) != preferences.pref_map.end()) {
            for (auto i = teams[itr->first].members.begin(); i != teams[itr->first].members.end(); ++i) {
                auto first = preferences.pref_map[itr->first].begin();
                auto last = preferences.pref_map[itr->first].end();
                if (find(first, last, i->umid) != last) {
                    i->preferred = true;
                }
            }   
        } 
    }

}

void Groups::sortTeams() {
//late survey students in groups > 5 are placed in second/third preference 
//if they didn't turn in their survey on time and are not preferred
//move and flag with star (*umid)
    starPreferred();
    for (auto itr = teams.begin(); itr != teams.end(); ++itr ) {
        string leader = itr->first;
        if (itr->second.count > 5 && itr->first != "None" 
            && itr->first != "NOT PLACED IN 2nd/3rd Choice") {
            if (round == 1 && pass == 1) moveLateSurveys(leader);
            if (round == 2) move2Second(leader);
            if (round == 3) move2Second(leader);
            if (round == 4) move2Second(leader);
        }
        if (round == 4 && itr->second.count < 2 && itr->first != "None" && pass == 2 
            && itr->first != "NOT PLACED IN 2nd/3rd Choice") {
            moveSmall(leader);
        }
    }
}

void Groups::moveLateSurveys(string & leader) {
    //printGroups();
    for (auto itr = teams[leader].members.begin(); itr != teams[leader].members.end(); ++itr) {
        if (!itr->survey && !itr->preferred && itr->umid != leader) {
            itr->umid = "*"+itr->umid;
            if (teams[itr->second_choice].count < 5) {
                //place in second choice
                --teams[leader].count;
                ++teams[itr->second_choice].count;
                teams[itr->second_choice].members.push_back(*itr);
                teams[leader].members.erase(itr);
                --itr;
            }
            else if (teams[itr->third_choice].count < 5) {
                //place in third choice
                --teams[leader].count;
                ++teams[itr->third_choice].count;
                teams[itr->third_choice].members.push_back(*itr);
                teams[leader].members.erase(itr);
                --itr;
            }
        }
    }
}


void Groups::move2Second(string & leader) {
    for (auto itr = teams[leader].members.begin(); itr != teams[leader].members.end() && teams[leader].count > 5; ++itr) {
        if (!itr->preferred && (itr->umid != leader)) {
            string choice;
            if (pass == 1) {
                choice = itr->second_choice;
            }
            else choice = itr->third_choice;

            if (teams[choice].count < (round+1)) {
                //place in second choice
                itr->umid = "*"+itr->umid;
                --teams[leader].count;
                ++teams[choice].count;
                teams[choice].members.push_back(*itr);
                teams[leader].members.erase(itr);
                --itr;
            }
            else if (round == 4 && pass == 2) {
                //move to none
                itr->umid = "*"+itr->umid;
                --teams[leader].count;
                ++teams["NOT PLACED IN 2nd/3rd Choice"].count;
                teams["NOT PLACED IN 2nd/3rd Choice"].members.push_back(*itr);
                teams[leader].members.erase(itr);
                --itr;
            }
        }
    }
}

void Groups::moveSmall(string & leader) {
    for (auto itr = teams[leader].members.begin(); itr != teams[leader].members.end(); ++itr) {
        itr->umid = "*"+itr->umid;
        if (teams[itr->second_choice].count < 5 && itr->second_choice != leader) {
            //place in second choice
            --teams[leader].count;
            ++teams[itr->second_choice].count;
            teams[itr->second_choice].members.push_back(*itr);
            teams[leader].members.erase(itr);
            --itr;
        }
        else if (teams[itr->third_choice].count < 5 && itr->third_choice != leader) {
            //place in third choice
            --teams[leader].count;
            ++teams[itr->third_choice].count;
            teams[itr->third_choice].members.push_back(*itr);
            teams[leader].members.erase(itr);
            --itr;
        }
        else {
            //move to none
            --teams[leader].count;
            ++teams["NOT PLACED IN 2nd/3rd Choice"].count;
            teams["NOT PLACED IN 2nd/3rd Choice"].members.push_back(*itr);
            teams[leader].members.erase(itr);
            --itr;
        }
    }
}

void Groups::placeNone() {
    auto itr = teams["None"].members.begin();
    int team_size = 3;
    while (itr != teams["None"].members.end() && team_size < 6) {
        for (auto itt = teams.begin(); itt != teams.end() && itr != teams["None"].members.end(); ++itt) {
            if (itt->second.count < team_size && itt->second.count > 0 && itt->first != "NOT PLACED IN 2nd/3rd Choice") {
                itr->umid = "placed"+itr->umid;
                ++itt->second.count;
                itt->second.members.push_back(*itr);
                ++itr;
            }
        }
        ++team_size;
    }
}

void Groups::checkCount(){
    count_flag = false;
    for (auto itr = teams.begin(); itr != teams.end(); ++itr ) {
        if (teams[itr->first].count > 5 || teams[itr->first].count < 3) count_flag = true;
    }

}

void Groups::printGroups() {
    unordered_map <int, int> group_stats;
    for (auto itr = teams.begin(); itr != teams.end(); ++itr ) {
        cout << "--PROPOSAL---\n";
        cout << itr->first << '\n';
        cout << "--GROUP-----\n";
        int count = 0;
        for (auto i = teams[itr->first].members.begin(); i != teams[itr->first].members.end(); ++i) {
            cout << i->umid << "\n";
            ++count;
        }
        cout << "COUNT: " << teams[itr->first].count << '\n';
        cout << '\n';
        ++group_stats[teams[itr->first].count];
    }
    cout << "GROUP STATS\n";
    cout << "Group size | Number of groups with Size\n";
    for (auto itt = group_stats.begin(); itt != group_stats.end(); ++itt) {
            cout << itt->first << "        " << itt->second << '\n';
    }
}

