#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void readInput(vector<int> &list1, vector<int> &list2)
{
    int value1, value2;
    while (cin >> value1 >> value2) {
        list1.push_back(value1);
        list2.push_back(value2);
    }
}

void sortLists(vector<int> &list1, vector<int> &list2)
{
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());
}

int calculateTotalDistance(const vector<int> &list1, const vector<int> &list2)
{
    int totalDistance = 0;
    for (size_t i = 0; i < list1.size(); i++) {
        totalDistance += abs(list1[i] - list2[i]);
    }
    return totalDistance;
}

int calculateSimilarityScore(const vector<int> &list1, const vector<int> &list2)
{
    int similarityScore = 0;
    size_t index2 = 0;
    for (size_t index1 = 0; index1 < list1.size(); index1++) {
        while ((index2 < list2.size()) && (list1[index1] > list2[index2])) {
            index2++;
        }
        while ((index2 < list2.size()) && (list1[index1] == list2[index2])) {
            similarityScore += list2[index2];
            index2++;
        }
    }
    return similarityScore;
}

int main()
{
    vector<int> list1, list2;
    readInput(list1, list2);

    sortLists(list1, list2);

    // Part one
    cout << "Total distance between the lists: " << calculateTotalDistance(list1, list2) << endl;

    // Part two
    cout << "Similarity Score: " << calculateSimilarityScore(list1, list2) << endl;
}
