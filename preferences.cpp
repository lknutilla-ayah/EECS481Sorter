//code by Laura Knutilla
#include "preferences.h"


//MAKE PREFERENCES MAP
void Preference::makePreferenceMap(string & preferences) {
    ifstream prefFile(preferences); 
    string line;
    if (prefFile.is_open()) {
        while (getline(prefFile,line)) {
            string stud;
            string lead;
            stringstream ss2;
            ss2 << line;
            ss2 >> lead;
            while (ss2) {
                ss2 >> stud;
                pref_map[lead].push_back(stud);
            }
        }
    }
    //DEBUGGING TOOL
    //prints preferences file
    // for (auto itr = pref_map.begin(); itr != pref_map.end(); ++itr) {
    //     cout << itr->first << ": ";
    //     for (auto itt = pref_map[itr->first].begin(); itt != pref_map[itr->first].end(); ++itt) {
    //         cout << *itt << " ";
    //     }
    //     cout << '\n';
    // }
}
    
