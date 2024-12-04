#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    vector<vector<int>> list;

    {
        ifstream inputFile("input");
        string line;
        for (size_t i = 0; getline(inputFile, line); i++) {
            list.push_back({});
            stringstream stream(line);
            int value;
            while (stream >> value) {
                list[i].push_back(value);
            }
            cout << endl;
        }
    }

    // Part one
    int numberOfSafeReports = 0;
    for (vector<int> report : list) {
        bool safe = true;
        bool increasing = report[0] < report[1];
        int previousLevel = report[0];
        for (size_t i = 1; i < report.size(); i++) {
            int currentLevel = report[i];
            if (increasing) {
                if (previousLevel >= currentLevel || currentLevel - previousLevel > 3) {
                    safe = false;
                    break;
                }
            } else {
                if (previousLevel <= currentLevel || previousLevel - currentLevel > 3) {
                    safe = false;
                    break;
                }
            }
            previousLevel = currentLevel;
        }
        numberOfSafeReports += safe;
    }
    cout << "Number of safe reports: " << numberOfSafeReports << endl;
}
