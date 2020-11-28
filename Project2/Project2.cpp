//Project 2
//Author: Han
//ID: 
//Compile: g++

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>

using namespace std;

bool A_live = true;
bool B_live = true;
bool C_live = true;
int frequency = 10000;
int A_win_s1 = 0;
int A_win_s2 = 0;

//Check at least two alive
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
    int i = 0;
    if (A_alive) {
        i++;
    }
    if (B_alive) {
        i++;
    }
    if (C_alive) {
        i++;
    }
    if (i >= 2) {
        return true;
    }
    return false;
}

//Aaron shoots
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    //Only works while Arron is alive
    if (!A_live) {
        return;
    }
    //Aaron hit rate: 1/3
    int r = rand() % 3;
    if (r == 0) {
        if (C_alive) {
            C_alive = false;
            return;
        }
        B_alive = false;
    }
    return;
}

//Bob shoots
void Bob_shoots(bool& A_alive, bool& C_alive) {
    //Only works while Bob is alive
    if (!B_live) {
        return;
    }
    //Bob hit rate: 1/2
    int r = rand() % 2;
    if (r == 0) {
        if (C_alive) {
            C_alive = false;
            return;
        }
        A_alive = false;
    }
    return;
}

//Charlie shoots
void Charlie_shoots(bool& A_alive, bool& B_alive) {
    //Only works while Charlie is alive
    if (!C_live) {
        return;
    }
    if (B_alive) {
        B_alive = false;
        return;
    }
    A_alive = false;
    return;
}

//Aaron shoots2
//I can't use only 1 Class to achieve deliberately miss shoot, so it's same as shoots1
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    //Only works while Arron is alive
    if (!A_live) {
        return;
    }
    //Aaron hit rate: 1/3
    int r = rand() % 3;
    if (r == 0) {
        if (C_alive) {
            C_alive = false;
            return;
        }
        B_alive = false;
    }
    return;
}

//Press Enter to continue
void pressKey() {
    cout << "Press Enter to continue...";
    cin.ignore().get();
    return;
}

//Print Unit Testing 1
void test_at_least_two_alive() {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";

    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n"; 

    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n"; 

    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n"; 

    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n"; 

    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n"; 

    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n"; 

    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n"; 

    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed ...\n"; 
    return;
}

//Print Unit Testing 2 - Aaron shoots1
void test_Aaron_shoots1() {
    cout << "Unit Testing 2: Function - Aaron_shoots1(Bob_alive, Charlie_alive)\n";

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    cout << "\t\tAaron is shooting at Bob\n";
    return;
}

//Print Unit Testing 3 - Bob shoots
void test_Bob_shoots() {
    cout << "Unit Testing 3: Function - Bob_shoots(Aaron_alive, Charlie_alive)\n";

    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    cout << "\t\tBob is shooting at Aaron\n";
    return;
}

//Print Unit Testing 4 - Charlie shoots
void test_Charlie_shoots() {
    cout << "Unit Testing 4: Function - Charlie_shoots(Aaron_alive, Bob_alive)\n";

    cout << "\tCase 1: Aaron alive, Bob alive\n";
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 2: Aaron dead, Bob alive\n";
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 3: Aaron alive, Bob dead\n";
    cout << "\t\tCharlie is shooting at Aaron\n";
    return;
}

//Print Unit Testing 1 - Aaron shoots2
void test_Aaron_shoots2() {
    cout << "Unit Testing 5: Function - Aaron_shoots2(Bob_alive, Charlie_alive)\n";

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    cout << "\t\tAaron intentionally misses his first shot\n";
    cout << "\t\tBob and Charlie are alive\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    cout << "\t\tAaron is shooting at Bob\n";
    return;
}

//Simulation strategy 1
void test_strategy_1() {
    int A_win = 0;
    int B_win = 0;
    int C_win = 0;
    for (int i = 0; i < frequency; i++) {
        A_live = true;
        B_live = true;
        C_live = true;
        while (at_least_two_alive(A_live, B_live, C_live)) {
            Aaron_shoots1(B_live, C_live);
            Bob_shoots(A_live, C_live);
            Charlie_shoots(A_live, B_live);
        }
        if (A_live) {
            A_win++;
        }
        if (B_live) {
            B_win++;
        }
        if (C_live) {
            C_win++;
        }
    }
    //Caculate win rate
    double A_winRate = (double)A_win / 100;
    double B_winRate = (double)B_win / 100;
    double C_winRate = (double)C_win / 100;
    //Print result
    cout << "Aaron won " << A_win << "/" << "10000 duels or " << A_winRate << "%" << endl;
    cout << "Bob won " << B_win << "/" << "10000 duels or " << B_winRate << "%" << endl;
    cout << "Charlie won " << C_win << "/" << "10000 duels or " << C_winRate << "%" << endl;

    A_win_s1 = A_win;
    return;
}

//Simulation strategy 2
void test_strategy_2() {
    int A_win = 0;
    int B_win = 0;
    int C_win = 0;
    for (int i = 0; i < frequency; i++) {
        A_live = true;
        B_live = true;
        C_live = true;
        bool first = true;
        while (at_least_two_alive(A_live, B_live, C_live)) {
            //First time, Aaron deliberately shoot miss
            if (first) {
                Bob_shoots(A_live, C_live);
                Charlie_shoots(A_live, B_live);
            }
            else {
                Aaron_shoots1(B_live, C_live);
                Bob_shoots(A_live, C_live);
                Charlie_shoots(A_live, B_live);
            }
            first = false;
        }
        if (A_live) {
            A_win++;
        }
        if (B_live) {
            B_win++;
        }
        if (C_live) {
            C_win++;
        }
    }
    //Caculate win rate
    double A_winRate = (double)A_win / 100;
    double B_winRate = (double)B_win / 100;
    double C_winRate = (double)C_win / 100;
    //Print result
    cout << "Aaron won " << A_win << "/" << "10000 duels or " << A_winRate << "%" << endl;
    cout << "Bob won " << B_win << "/" << "10000 duels or " << B_winRate << "%" << endl;
    cout << "Charlie won " << C_win << "/" << "10000 duels or " << C_winRate << "%" << endl;

    A_win_s2 = A_win;
    return;
}


int main() {
    //Keep the output to two decimal places
    cout.setf(ios::fixed); 
    cout.setf(ios::showpoint); 
    cout.precision(2); 

    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;

    //Achieve random number
    srand(time(0));

    cout << "*** Welcome to	Han's Duel Simulator ***" << endl;
    test_at_least_two_alive();
    pressKey();
    test_Aaron_shoots1();
    pressKey();
    test_Bob_shoots();
    pressKey();
    test_Charlie_shoots();
    pressKey();
    test_Aaron_shoots2();
    pressKey();
    cout << "Ready to test strategy 1 (run 10000 times):\n";
    pressKey();
    test_strategy_1();
    cout << "\nReady to test strategy 2 (run 10000 times):\n";
    pressKey();
    test_strategy_2();
    cout << endl;
    if (A_win_s1 > A_win_s2) {
        cout << "Strategy 1 is better than strategy 2. ";	
    }
    else if (A_win_s1 < A_win_s2) {
        cout << "Strategy 2 is better than strategy 1. ";
    }
    else {
        cout << "Strategy 1 and strategy 2 are equal. ";
    }

    return 0;
}
