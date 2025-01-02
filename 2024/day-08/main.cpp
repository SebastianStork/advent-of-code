#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

void readInput(vector<string> &antennaMap, map<char, set<pair<int, int>>> &antennas)
{
    string line;
    for (size_t row = 0; getline(cin, line); row++) {
        for (size_t col = 0; col < line.size(); col++) {
            char frequency = line[col];
            if (frequency != '.') {
                if (antennas.count(frequency)) {
                    antennas.at(frequency).insert({row, col});
                } else {
                    antennas.insert({frequency, {{row, col}}});
                }
            }
        }
        antennaMap.push_back(line);
    }
}

bool isInBounds(pair<int, int> location, const vector<string> &map)
{
    return (location.first >= 0 && location.first < map.size())
           && (location.second >= 0 && location.second < map[0].size());
}

vector<pair<int, int>> getAntinodes(pair<int, int> antenna1,
                                    pair<int, int> antenna2,
                                    const vector<string> &antennaMap)
{
    if (antenna1 == antenna2) {
        return {};
    }

    pair<int, int> directionVector = {antenna2.first - antenna1.first,
                                      antenna2.second - antenna1.second};

    pair<int, int> antinode1 = {antenna2.first + directionVector.first,
                                antenna2.second + directionVector.second};
    pair<int, int> antinode2 = {antenna1.first - directionVector.first,
                                antenna1.second - directionVector.second};

    vector<pair<int, int>> antinodes;
    if (isInBounds(antinode1, antennaMap)) {
        antinodes.push_back(antinode1);
    }
    if (isInBounds(antinode2, antennaMap)) {
        antinodes.push_back(antinode2);
    }
    return antinodes;
}

int main()
{
    vector<string> antennaMap;
    map<char, set<pair<int, int>>> antennas;
    readInput(antennaMap, antennas);

    set<pair<int, int>> uniqueAntinodes;

    for (auto antennasWithSameFrequency : antennas) {
        for (auto antenna1 : antennasWithSameFrequency.second) {
            for (auto antenna2 : antennasWithSameFrequency.second) {
                vector<pair<int, int>> foundAntinodes = getAntinodes(antenna1, antenna2, antennaMap);
                for (pair<int, int> antinode : foundAntinodes) {
                    uniqueAntinodes.insert(antinode);
                }
            }
        }
    }

    // Part one
    cout << "Number of unique antinodes: " << uniqueAntinodes.size() << endl;
}
