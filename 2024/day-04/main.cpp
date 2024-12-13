#include <iostream>
#include <vector>

using namespace std;

vector<string> readInput()
{
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    return lines;
}

int main()
{
    int numberOfOccurences = 0;
    const vector<string> matrix = readInput();

    // Horizontal
    for (size_t rowIndex = 0; rowIndex < matrix.size(); rowIndex++) {
        for (size_t colIndex = 0; colIndex < matrix[0].size() - 3; colIndex++) {
            const string nextWord = matrix[rowIndex].substr(colIndex, 4);
            if (nextWord == "XMAS" || nextWord == "SAMX") {
                numberOfOccurences++;
            }
        }
    }

    // Vertical
    for (size_t colIndex = 0; colIndex < matrix[0].size(); colIndex++) {
        for (size_t rowIndex = 0; rowIndex < matrix.size() - 3; rowIndex++) {
            string nextWord;
            for (size_t i = 0; i <= 3; i++) {
                nextWord += matrix[rowIndex + i][colIndex];
            }
            if (nextWord == "XMAS" || nextWord == "SAMX") {
                numberOfOccurences++;
            }
        }
    }

    // Diagonal
    for (size_t rowIndex = 0; rowIndex < matrix.size() - 3; rowIndex++) {
        for (size_t colIndex = 0; colIndex < matrix[0].size() - 3; colIndex++) {
            string nextWord1, nextWord2;
            for (size_t i = 0, j = 3; i <= 3; i++, j--) {
                nextWord1 += matrix[rowIndex + i][colIndex + i];
                nextWord2 += matrix[rowIndex + j][colIndex + i];
            }
            if (nextWord1 == "XMAS" || nextWord1 == "SAMX") {
                numberOfOccurences++;
            }
            if (nextWord2 == "XMAS" || nextWord2 == "SAMX") {
                numberOfOccurences++;
            }
        }
    }

    cout << "Number of XMAS occurences: " << numberOfOccurences << endl;
}
