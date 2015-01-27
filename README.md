EECS 481 Student Group Sorter
**by Laura Knutilla

<ul>To Run:</ul>
    <li>1) Download file. Contains:
        Makefile
        main.h/.cpp
        groups.h/.cpp
        preferences.h/.cpp</li>
    <li>2) Add your text files (see Inputs section for format):
        a)List of students and preferences
        b)List of leaders and preferences</li>
    <li>3)run "make" from folder</li>
    <li>4)run ./teams [students_file] [preferences_file]</li>

Inputs:

    Student list Format:

    STUDENT_UMID SURVEY_SUBMIT[0,1] FIRST_CHOICE_UMID SECOND_CHOICE_UMID THIRD_CHOICE_UMID  
    Example:

    mojojo 0 blossom butterc bubbles 

    Student mojojo turned in their survey late and would prefer to be in blossom's group, then butterc's, then bubbles's

    Preference file Format:

    PROPOSAL_LEADER_UMID list of preferred student ids
    Example:

    blossom utonium mskeane 

    Student proposal leader, blossom, would like students, utonium and mskeane on their team

    !!!!NOTE: if a student doesn't turn in a preference survey, a "None" group will be created for these students and they will be sorted. Leave their preferences blank in the txt file. 

Sorting Algorithm:
    The algorithm works by generally sorting the students into groups of their first preference then 
    running two passes over the groups to shrink groups > 5 and grow groups < 3

    Note: A student will not be moved if they have been preferred by the leader  or they are the proposal leader as specified in the preferences file.

    FIRST PASS: puts students in 2nd choice
        if groups are over 5
            ROUND 1: will move students with late surveys
            ROUND 2: will move students to their second choice if the group is < 3
            ROUND 3-4: puts students in second choice groups of increasing size
    SECOND PASS: repeats Pass 1, but puts students in 3rd choice and does not move students with late surveys

    If a student cannot be placed and a group still must be shrunk, the program places them in a "Not placed" group and they will need to be manually sorted later.

    Students who do not turn in a survey are placed in a "None" group. After the groups are sorted, the students in "None" will be randomly placed in groups with sizes < 2. Their umid's are marked with "placed+umid" after they have been sorted. They will still appear in the "None" group.

    
