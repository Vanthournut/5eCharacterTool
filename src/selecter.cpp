#include "selecter.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

vector<int> ConsoleSelecter::select(vector<SelecterItem*> list, int count) {
    int selection = -2;
    vector<int> selectionVector;
    int index;
    string message = "";

    do
    {
        system("clear");
        index = 0;

        for(SelecterItem* item : list) {
            cout << index << ": " << item->getName() << endl << item->getDescription() << endl << endl;
            index++;
        }
        cout << message << "Type the index of the desired item, or type '-1' to cancel: ";
        cin >> selection;

        if (cin.fail() || selection < -1 || selection >= (int) list.size())
        {
            message = "Invalid input. ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (find(selectionVector.begin(), selectionVector.end(), selection) != selectionVector.end())
        {
            message = "Item already selected. ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (selection == -1)
        {
            return vector<int>();
        }

        selectionVector.push_back(selection);
        cout << endl << endl;

        message = "";
        

    } while (selectionVector.size() < count);
    
    
    return selectionVector;
}
vector<pair<int, int>> ConsoleSelecter::swap(vector<SelecterItem*> currentList, vector<SelecterItem*> swapList, int maxSelections) {
    return vector<pair<int,int>>();
}

// const static Selecter* defaultSelecter = new ConsoleSelecter();