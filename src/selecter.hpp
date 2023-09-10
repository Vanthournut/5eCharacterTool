#include <vector>
#include <string>

using namespace std;

class SelecterItem {
    public:
    virtual string getName() = 0;
    virtual string getDescription() = 0;
};

class Selecter {
    public:
    virtual vector<int> select(vector<SelecterItem*> list, int count = 1) = 0;
    virtual vector<pair<int, int>> swap(vector<SelecterItem*> currentList, vector<SelecterItem*> swapList, int maxSelections = 1) = 0;
};

class ConsoleSelecter : public Selecter {
    public:
    vector<int> select(vector<SelecterItem*> list, int count = 1) override;
    vector<pair<int, int>> swap(vector<SelecterItem*> currentList, vector<SelecterItem*> swapList, int maxSelections = 1) override;
};