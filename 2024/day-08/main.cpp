#include <iostream>
#include <map>
#include <set>
#include <utility>
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

pair<int, int> getDirectionVector(const pair<int, int> &antenna1, const pair<int, int> &antenna2)
{
    return {antenna2.first - antenna1.first, antenna2.second - antenna1.second};
}

bool isInBounds(const pair<int, int> &location, const vector<string> &map)
{
    return (location.first >= 0 && cmp_less(location.first, map.size()))
           && (location.second >= 0 && cmp_less(location.second, map[0].size()));
}

vector<pair<int, int>> getAntinodes(const pair<int, int> &antenna1,
                                    const pair<int, int> &antenna2,
                                    const vector<string> &antennaMap)
{
    if (antenna1 == antenna2) {
        return {};
    }

    const pair<int, int> directionVector = getDirectionVector(antenna1, antenna2);

    const pair<int, int> antinode1 = {antenna1.first - directionVector.first,
                                      antenna1.second - directionVector.second};
    const pair<int, int> antinode2 = {antenna2.first + directionVector.first,
                                      antenna2.second + directionVector.second};

    vector<pair<int, int>> antinodes;
    if (isInBounds(antinode1, antennaMap)) {
        antinodes.push_back(antinode1);
    }
    if (isInBounds(antinode2, antennaMap)) {
        antinodes.push_back(antinode2);
    }
    return antinodes;
}

vector<pair<int, int>> getResonantHarmonicsAntinodes(const pair<int, int> &antenna1,
                                                     const pair<int, int> &antenna2,
                                                     const vector<string> &antennaMap)
{
    if (antenna1 == antenna2) {
        return {};
    }

    const pair<int, int> directionVector = getDirectionVector(antenna1, antenna2);
    vector<pair<int, int>> antinodes;

    pair<int, int> antinode1 = antenna1;
    do {
        antinodes.push_back(antinode1);
        antinode1.first -= directionVector.first;
        antinode1.second -= directionVector.second;
    } while (isInBounds(antinode1, antennaMap));

    pair<int, int> antinode2 = antenna2;
    do {
        antinodes.push_back(antinode2);
        antinode2.first += directionVector.first;
        antinode2.second += directionVector.second;
    } while (isInBounds(antinode2, antennaMap));

    return antinodes;
}

int main()
{
    vector<string> antennaMap;
    map<char, set<pair<int, int>>> antennas;
    readInput(antennaMap, antennas);

    set<pair<int, int>> uniqueAntinodes;
    set<pair<int, int>> uniqueResonantHarmonicsAntinodes;
    set<pair<pair<int, int>, pair<int, int>>> consideredAntennaCombinations;

    for (const auto &antennasWithSameFrequency : antennas) {
        for (const auto &antenna1 : antennasWithSameFrequency.second) {
            for (const auto &antenna2 : antennasWithSameFrequency.second) {
                const auto orderedPair = make_pair(min(antenna1, antenna2), max(antenna1, antenna2));
                if (consideredAntennaCombinations.contains(orderedPair)) {
                    continue;
                }
                consideredAntennaCombinations.insert(orderedPair);

                const vector<pair<int, int>> foundAntinodes = getAntinodes(antenna1,
                                                                           antenna2,
                                                                           antennaMap);
                for (pair<int, int> antinode : foundAntinodes) {
                    uniqueAntinodes.insert(antinode);
                }
                const vector<pair<int, int>> foundResonantHarmonicsAntinodes
                    = getResonantHarmonicsAntinodes(antenna1, antenna2, antennaMap);
                for (pair<int, int> antinode : foundResonantHarmonicsAntinodes) {
                    uniqueResonantHarmonicsAntinodes.insert(antinode);
                }
            }
        }
    }

    // Part one
    cout << "Number of unique antinodes: " << uniqueAntinodes.size() << endl;

    // Part two
    cout << "Number of unique antinodes when taking resonant harmonics into account: "
         << uniqueResonantHarmonicsAntinodes.size() << endl;
}
