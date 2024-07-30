#include "src/character.hpp"
#include "src/characterClass.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <stack>
#include <sstream>
#include "src/sourceBook.hpp"

using namespace std;

int main() {
    system("clear");

    string name;
    cout << "Enter Character Name: ";
    cin >> name;

    vector<char> standardArray{15,14,13,12,10,8};
    char stats[6]{0};
    const char* statString[6] = {"STR", "DEX", "CON", "INT", "WIS", "CHA"};
    int selection;
    int numAssigned = 0;
    string errorMessage = "";
    stack<int> inputStack;


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
                stats[inputStack.top()] = 0;
                inputStack.pop();
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
            inputStack.push(selection);
        }
    }

    Character c(name, stats);

    ConsoleSelecter selecter;

    HighElf e(selecter);
    if (&e == nullptr)
    {
        cout << "High Elf Object does not exist\n";
        return -1;
    }
    
    // stringstream raceTestStream;
    // e.save(raceTestStream);
    // string sourceStringPlaceholder;
    // getline(raceTestStream, sourceStringPlaceholder);
    // Race* loadedRace = SRD_SOURCE.loadRace(raceTestStream);

    // cout << loadedRace->getName();

    // delete loadedRace;

    c.addRace(&e);

    // return 0;



    Barbarian barb = Barbarian(c, selecter, true);
    system("clear");

    c.update(selecter, UpdateType::Refresh);


    cout << c.toString() << endl;

    stringstream testStream;

    c.save(testStream);

    Character* c2 = Character::load(testStream);
    c2->update(selecter, UpdateType::Refresh);
    cout << endl << c2->toString() << endl;

    if(c == *c2) {
        cout << "This is the same character.\n";
    }

    delete c2;

    cout << "end\n";

    // AcidSplash acidSplash;
    // stringstream spellTestStream;
    // acidSplash.save(spellTestStream);
    // getline(spellTestStream, sourceStringPlaceholder);
    // Spell* loadedSpell = SRD_SOURCE.loadSpell(spellTestStream);

    // cout << loadedSpell->getName();

    // delete loadedSpell;

    return 0;
}