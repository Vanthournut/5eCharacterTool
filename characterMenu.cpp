#include "src/character.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

int main() {

    string name;
    cout << "Enter Character Name: ";
    cin >> name;

    vector<char> standardArray{15,14,13,12,10,8};
    char stats[6]{0};
    const char* statString[6] = {"STR", "DEX", "CON", "INT", "WIS", "CHA"};
    int selection;
    int numAssigned = 0;
    string errorMessage = "";

    while(numAssigned != 6) {
        cout << "0 STR: " << int(stats[0]) << endl;
        cout << "1 DEX: " << int(stats[1]) << endl;
        cout << "2 CON: " << int(stats[2]) << endl;
        cout << "3 INT: " << int(stats[3]) << endl;
        cout << "4 WIS: " << int(stats[4]) << endl;
        cout << "5 CHA: " << int(stats[5]) << endl << endl;

        cout << errorMessage << "Enter the index of the stat you would like to assign '" //
            << int(standardArray[numAssigned]) << "' to or enter -1 to go back to the last assignment." << endl;

        cin >> selection;
        if (cin.fail() || selection < -1 || selection > 6)
        {
            errorMessage = "Invalid input. ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (selection == -1)
        {
            cin.clear();
            errorMessage = "";
            if(numAssigned != 0) {
                numAssigned--;
                stats[numAssigned] = 0;
            }
        }
        else if (stats[selection] != char(0))
        {
            errorMessage = "Stat already assigned. ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else {
            cin.clear();
            errorMessage = "";
            stats[selection] = standardArray[numAssigned++];
        }
    }

    Character c(name, stats);

    ConsoleSelecter selecter;
    try{
        HighElf e(selecter);
        c.addRace(&e);
    } catch(...) {
        cout << "Failed to create HighElf Class" << endl;
    }

    cout << endl << endl;

    cout << c.toString() << endl;
    return 0;
}