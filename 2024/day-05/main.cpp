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
        rules.push_back(make_pair(number1, number2));
    }
    return rules;
}

vector<vector<int>> readManuals()
{
    vector<vector<int>> manuals;
    string line;
    while (getline(cin, line)) {
        manuals.push_back({});
        stringstream inStream(line);
        string page;
        while (getline(inStream, page, ',')) {
            manuals.back().push_back(stoi(page));
        }
    }
    return manuals;
}

vector<pair<int, int>> getSortedLessThanRules(vector<pair<int, int>> rules)
{
    sort(rules.begin(), rules.end(), [](auto a, auto b) { return a.first < b.first; });
    return rules;
}

vector<pair<int, int>> getSortedGreaterThanRules(vector<pair<int, int>> rules)
{
    for (pair<int, int> &rule : rules) {
        swap(rule.first, rule.second);
    }
    sort(rules.begin(), rules.end(), [](auto a, auto b) { return a.first < b.first; });
    return rules;
}

enum class Comparison { lessThan, greaterThan };

bool pageIsFollowingRules(const vector<int> &pages,
                          const size_t indexOfPageToCheck,
                          const vector<pair<int, int>> &rules,
                          const Comparison ruleType)
{
    size_t indexOfFirstRule = lower_bound(rules.begin(),
                                          rules.end(),
                                          pages[indexOfPageToCheck],
                                          [](pair<int, int> a, int b) { return a.first < b; })
                              - rules.begin();

    if (indexOfFirstRule == rules.size()) {
        return true;
    }

    size_t pagesStart, pagesEnd;
    if (ruleType == Comparison::lessThan) {
        pagesStart = 0;
        pagesEnd = indexOfPageToCheck;
    } else {
        pagesStart = indexOfPageToCheck;
        pagesEnd = pages.size();
    }

    for (size_t pageIndex = pagesStart; pageIndex < pagesEnd; pageIndex++) {
        for (size_t ruleIndex = indexOfFirstRule;
             ruleIndex < rules.size() && rules[ruleIndex].first == pages[indexOfPageToCheck];
             ruleIndex++) {
            if (pages[pageIndex] == rules[ruleIndex].second) {
                return false;
            }
        }
    }

    return true;
}

int getMiddlePageNumber(vector<int> pages)
{
    size_t middleIndex = pages.size() / 2;
    return pages[middleIndex];
}

int main()
{
    vector<pair<int, int>> unsortedRules = readRules();
    vector<vector<int>> manuals = readManuals();

    vector<pair<int, int>> lessThanRules = getSortedLessThanRules(unsortedRules);
    vector<pair<int, int>> greaterThanRules = getSortedGreaterThanRules(unsortedRules);

    int middlePageNumberSum = 0;

    for (const vector<int> &pages : manuals) {
        bool correctlyOrdered = true;
        for (size_t i = 0; i < pages.size(); i++) {
            if (!pageIsFollowingRules(pages, i, lessThanRules, Comparison::lessThan)
                || !pageIsFollowingRules(pages, i, greaterThanRules, Comparison::greaterThan)) {
                correctlyOrdered = false;
                break;
            }
        }
        if (correctlyOrdered) {
            middlePageNumberSum += getMiddlePageNumber(pages);
        }
    }

    // Part one
    cout << "Sum of the middle page numbers of all correctly ordered manuals: "
         << middlePageNumberSum << endl;
}
