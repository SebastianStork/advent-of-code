#include <iostream>
#include <vector>

using namespace std;

void readInput(vector<string> &mappedArea, pair<int, int> &startingPosition)
{
    string line;
    for (size_t rowIndex = 0; getline(cin, line); rowIndex++) {
        for (size_t colIndex = 0; colIndex < line.size(); colIndex++) {
            if (line[colIndex] == '^') {
                startingPosition = {rowIndex, colIndex};
            }
        }
        mappedArea.push_back(line);
    }
}

bool takeStep(vector<string> &mappedArea,
              pair<int, int> &currentPosition,
              int &currentOrientation,
              int &distinctPositionCount)
{
    pair<int, int> nextPosition = currentPosition;

    switch (currentOrientation) {
    case 0:
        nextPosition.first--;
        break;
    case 1:
        nextPosition.second++;
        break;
    case 2:
        nextPosition.first++;
        break;
    case 3:
        nextPosition.second--;
        break;
    default:
        break;
    }

    if ((nextPosition.first >= mappedArea.size() || nextPosition.first < 0)
        || (nextPosition.second >= mappedArea.front().size() || nextPosition.second < 0)) {
        mappedArea[currentPosition.first][currentPosition.second] = '#';
        return false;
    }

    if (mappedArea[nextPosition.first][nextPosition.second] == '#') {
        currentOrientation = ++currentOrientation % 4;
        return takeStep(mappedArea, currentPosition, currentOrientation, distinctPositionCount);
    }

    distinctPositionCount += !(mappedArea[nextPosition.first][nextPosition.second] == 'X');

    mappedArea[currentPosition.first][currentPosition.second] = 'X';
    mappedArea[nextPosition.first][nextPosition.second] = '^';

    currentPosition = nextPosition;
    return true;
}

int main()
{
    vector<string> mappedArea;
    pair<int, int> currentPosition;
    readInput(mappedArea, currentPosition);

    int currentOrientation = 0;
    int distinctPositionCount = 1;
    while (takeStep(mappedArea, currentPosition, currentOrientation, distinctPositionCount))
        ;

    for (auto row : mappedArea) {
        cout << row << endl;
    }
    cout << endl;

    // Part one
    cout << "How many distinct positions will the guard visit before leaving the mapped area? "
         << distinctPositionCount << endl;
}
