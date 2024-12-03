#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void sort(vector<int> &list)
{
    for (size_t i = 0; i < list.size() - 1; i++) {
        for (size_t j = i + 1; j < list.size(); j++) {
            if (list[i] > list[j]) {
                int temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

int main()
{
    vector<int> list1, list2;

    {
        ifstream inputFile("input");
        string line;
        while (getline(inputFile, line)) {
            list1.push_back(stoi(line.substr(0, 5)));
            list2.push_back(stoi(line.substr(8, 5)));
        }
    }

    sort(list1);
    sort(list2);

    int totalDistance = 0;

    for (size_t i = 0; i < list1.size(); i++) {
        int distance = list1[i] - list2[i];
        totalDistance += (distance >= 0) ? distance : -distance;
    }

    cout << "Total distance between the lists: " << totalDistance << endl;
}
