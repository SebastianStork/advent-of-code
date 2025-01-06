#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<pair<int, int>> readRules()
{
    vector<pair<int, int>> rules;
    string line;
    while (getline(cin, line)) {
        if (line == "") {
            break;
        }
        int number1 = stoi(line.substr(0, 2));
        int number2 = stoi(line.substr(3, 2));
        rules.push_back({number1, number2});
    }
    return rules;
}

vector<vector<int>> readManuals()
{
    vector<vector<int>> manuals;
    string line;
    while (getline(cin, line)) {
        stringstream inStream(line);
        vector<int> pages;
        string page;
        while (getline(inStream, page, ',')) {
            pages.push_back(stoi(page));
        }
        manuals.push_back(pages);
    }
    return manuals;
}

bool isCorrectPageOrdering(const int firstPage,
                           const int secondPage,
                           const vector<pair<int, int>> &rules)
{
    auto it = lower_bound(rules.begin(),
                          rules.end(),
                          secondPage,
                          [](const pair<int, int> &a, int b) { return a.first < b; });

    for (; it != rules.end() && it->first == secondPage; ++it) {
        if (it->second == firstPage) {
            return false;
        }
    }

    return true;
}

vector<int> getProperlyOrderedPages(vector<int> pages, const vector<pair<int, int>> &rules)
{
    sort(pages.begin(), pages.end(), [&rules](int a, int b) {
        return isCorrectPageOrdering(a, b, rules);
    });
    return pages;
}

int getMiddlePageNumber(const vector<int> &pages)
{
    size_t middleIndex = pages.size() / 2;
    return pages[middleIndex];
}

int main()
{
    vector<pair<int, int>> rules = readRules();
    vector<vector<int>> manuals = readManuals();
    sort(rules.begin(), rules.end());

    int sumOfCorrectMiddlePages = 0;
    int sumOfCorrectedMiddlePages = 0;

    for (const vector<int> &pages : manuals) {
        const vector<int> properlyOrderedPages = getProperlyOrderedPages(pages, rules);
        if (pages == properlyOrderedPages) {
            sumOfCorrectMiddlePages += getMiddlePageNumber(pages);
        } else {
            sumOfCorrectedMiddlePages += getMiddlePageNumber(properlyOrderedPages);
        }
    }

    // Part one
    cout << "Sum of the middle page numbers of all correctly ordered manuals: "
         << sumOfCorrectMiddlePages << endl;

    // Part two
    cout
        << "Sum of the middle page numbers of all incorrectly ordered manuals after ordering them: "
        << sumOfCorrectedMiddlePages << endl;
}
