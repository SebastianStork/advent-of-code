#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void readInput(vector<vector<int>> &list)
{
    string line;
    while (getline(cin, line)) {
        list.push_back({});
        stringstream stream(line);
        int value;
        while (stream >> value) {
            list.back().push_back(value);
        }
    }
}

int calculateNumberOfSafeReports(const vector<vector<int>> &list)
{
    int numberOfSafeReports = 0;
    for (vector<int> report : list) {
        bool safe = true;

        int directionOfChange = (report[0] < report[1]) ? 1 : -1;
        for (size_t i = 0; i < report.size() - 1; i++) {
            int levelDifference = (report[i + 1] - report[i]) * directionOfChange;

            if (levelDifference <= 0 || levelDifference > 3) {
                safe = false;
                break;
            }
        }
        numberOfSafeReports += safe;
    }
    return numberOfSafeReports;
}

int main()
{
    vector<vector<int>> list;
    readInput(list);

    // Part one
    cout << "Number of safe reports: " << calculateNumberOfSafeReports(list) << endl;
}
