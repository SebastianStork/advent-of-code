#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<int>> readInput()
{
    vector<vector<int>> list;
    string line;
    while (getline(cin, line)) {
        list.push_back({});
        stringstream stream(line);
        int value;
        while (stream >> value) {
            list.back().push_back(value);
        }
    }
    return list;
}

int getIndexOfUnsafeValue(const vector<int> &report)
{
    const int MAX_SAFE_DIFFERENCE = 3;

    int directionOfChange = (report.front() < report.back()) ? 1 : -1;
    for (size_t i = 0; i < report.size() - 1; i++) {
        int levelDifference = (report[i + 1] - report[i]) * directionOfChange;
        if (levelDifference <= 0 || levelDifference > MAX_SAFE_DIFFERENCE) {
            return i;
        }
    }

    return -1;
}

bool isSafeReport(const vector<int> &report, const bool applyDampener)
{
    int indexOfUnsafeValue = getIndexOfUnsafeValue(report);

    if (indexOfUnsafeValue == -1) {
        return true;
    }

    if (!applyDampener) {
        return false;
    }

    vector<int> tempReport = report;
    int unsafeValue = report[indexOfUnsafeValue];
    tempReport.erase(tempReport.begin() + indexOfUnsafeValue);
    if (getIndexOfUnsafeValue(tempReport) == -1) {
        return true;
    }

    tempReport.insert(tempReport.begin() + indexOfUnsafeValue, unsafeValue);
    tempReport.erase(tempReport.begin() + indexOfUnsafeValue + 1);
    return getIndexOfUnsafeValue(tempReport) == -1;
}

int calculateNumberOfSafeReports(const vector<vector<int>> &list, const bool applyDampener)
{
    int numberOfSafeReports = 0;
    for (const vector<int> &report : list) {
        numberOfSafeReports += isSafeReport(report, applyDampener);
    }
    return numberOfSafeReports;
}

int main()
{
    vector<vector<int>> list = readInput();

    // Part one
    cout << "Number of safe reports: " << calculateNumberOfSafeReports(list, false) << endl;

    // Part two
    cout << "Number of safe reports (when taking the dampener into account): "
         << calculateNumberOfSafeReports(list, true) << endl;
}
