#include <iostream>
#include <set>
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

bool isOutOfBounds(const vector<string> &mappedArea, const pair<int, int> &position)
{
    return (position.first < 0 || position.first >= mappedArea.size())
           || (position.second < 0 || position.second >= mappedArea[0].size());
}

bool isObstacle(const vector<string> &mappedArea, const pair<int, int> &position)
{
    char cell = mappedArea[position.first][position.second];
    return cell == '#' || cell == 'O';
}

enum Direction { UP = 0, RIGHT, DOWN, LEFT };

bool takeStep(vector<string> &mappedArea,
              pair<int, int> &currentPosition,
              Direction &currentDirection,
              set<pair<int, int>> *distinctPositions = nullptr)
{
    const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    pair<int, int> nextPosition = {currentPosition.first + directions[currentDirection].first,
                                   currentPosition.second + directions[currentDirection].second};

    if (isOutOfBounds(mappedArea, nextPosition)) {
        return false;
    }

    if (isObstacle(mappedArea, nextPosition)) {
        currentDirection = static_cast<Direction>((currentDirection + 1) % 4);
        return true;
    }

    if (distinctPositions && mappedArea[nextPosition.first][nextPosition.second] != 'X') {
        distinctPositions->insert({nextPosition.first, nextPosition.second});
    }

    mappedArea[currentPosition.first][currentPosition.second] = 'X';
    mappedArea[nextPosition.first][nextPosition.second] = '^';
    currentPosition = nextPosition;
    return true;
}

bool isLoopCausingObstruction(const pair<int, int> &obstructionPosition,
                              vector<string> mappedArea,
                              pair<int, int> currentPosition,
                              Direction currentDirection)
{
    if (obstructionPosition == currentPosition) {
        return false;
    }

    mappedArea[obstructionPosition.first][obstructionPosition.second] = 'O';

    set<tuple<int, int, Direction>> states;
    states.insert({currentPosition.first, currentPosition.second, currentDirection});

    while (takeStep(mappedArea, currentPosition, currentDirection)) {
        tuple<int, int, Direction> currentState = {currentPosition.first,
                                                   currentPosition.second,
                                                   currentDirection};

        if (states.count(currentState)) {
            return true;
        }

        states.insert(currentState);
    }

    return false;
}

int main()
{
    vector<string> mappedArea;
    pair<int, int> startingPosition;
    Direction startingDirection = UP;
    readInput(mappedArea, startingPosition);

    pair<int, int> currentPosition = startingPosition;
    Direction currentDirection = startingDirection;
    set<pair<int, int>> distinctPositions = {currentPosition};
    while (takeStep(mappedArea, currentPosition, currentDirection, &distinctPositions))
        ;
    int numberOfDistinctPositions = distinctPositions.size();

    int numberOfLoopCausingObstructions = 0;
    for (const pair<int, int> &obstructionPosition : distinctPositions) {
        numberOfLoopCausingObstructions += isLoopCausingObstruction(obstructionPosition,
                                                                    mappedArea,
                                                                    startingPosition,
                                                                    startingDirection);
    }

    // Part one
    cout << "Number of distinct positions visited before leaving: " << numberOfDistinctPositions
         << endl;

    // Part two
    cout << "Number of potential obstructions to create a loop: " << numberOfLoopCausingObstructions
         << endl;
}
