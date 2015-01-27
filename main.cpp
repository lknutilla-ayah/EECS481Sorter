//Group sorted for EECS 481
//code by: Laura Knutilla
#include "main.h"


int main(int argc, char const *argv[])
{
    //File that contains student names and preferences
    string students = argv[1];
    //File that contains leader preferences
    string preferences = argv[2];
    Groups groups;
    
    groups.makeGroups(students, preferences);
    groups.printGroups();

    return 0;
}
