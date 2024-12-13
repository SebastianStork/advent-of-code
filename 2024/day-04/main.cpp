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

bool wordIsXmas(const string &word)
{
    return word == "XMAS" || word == "SAMX";
}

bool wordIsMas(const string &word)
{
    return word == "MAS" || word == "SAM";
}

int xmasCountAt(const vector<string> &matrix, const size_t rowIndex, const size_t colIndex)
{
    const size_t numberOfRows = matrix.size();
    const size_t numberOfCols = matrix[0].size();

    int xmasCount = 0;

    // Horizontal check
    if (colIndex + 3 < numberOfCols) {
        string horizontalWord = matrix[rowIndex].substr(colIndex, 4);
        xmasCount += wordIsXmas(horizontalWord);
    }

    // Vertical check
    if (rowIndex + 3 < numberOfRows) {
        string verticalWord;
        for (size_t i = 0; i <= 3; i++) {
            verticalWord += matrix[rowIndex + i][colIndex];
        }
        xmasCount += wordIsXmas(verticalWord);
    }

    // Down-diagonal check
    if (rowIndex + 3 < numberOfRows && colIndex + 3 < numberOfCols) {
        string downDiagonalWord;
        for (size_t i = 0; i <= 3; i++) {
            downDiagonalWord += matrix[rowIndex + i][colIndex + i];
        }
        xmasCount += wordIsXmas(downDiagonalWord);
    }

    // Up-diagonal check
    if (rowIndex + 3 < numberOfRows && colIndex + 3 < numberOfCols) {
        string upDiagonalWord;
        for (size_t i = 0; i <= 3; i++) {
            upDiagonalWord += matrix[rowIndex + (3 - i)][colIndex + i];
        }
        xmasCount += wordIsXmas(upDiagonalWord);
    }

    return xmasCount;
}

bool crossMasExistsAt(const vector<string> &matrix, const size_t rowIndex, const size_t colIndex)
{
    const size_t numberOfRows = matrix.size();
    const size_t numberOfCols = matrix[0].size();

    if (rowIndex + 2 >= numberOfRows || colIndex + 2 >= numberOfCols) {
        return false;
    }

    string downDiagonalWord;
    for (size_t i = 0; i <= 2; i++) {
        downDiagonalWord += matrix[rowIndex + i][colIndex + i];
    }
    if (!wordIsMas(downDiagonalWord)) {
        return false;
    }

    string upDiagonalWord;
    for (size_t i = 0; i <= 2; i++) {
        upDiagonalWord += matrix[rowIndex + (2 - i)][colIndex + i];
    }
    if (!wordIsMas(upDiagonalWord)) {
        return false;
    }

    return true;
}

int main()
{
    const vector<string> matrix = readInput();
    const size_t numberOfRows = matrix.size();
    const size_t numberOfCols = matrix[0].size();

    int numberOfXmasOccurrences = 0;
    int numberOfCrossMasOccurrences = 0;

    for (size_t rowIndex = 0; rowIndex < numberOfRows; rowIndex++) {
        for (size_t colIndex = 0; colIndex < numberOfCols; colIndex++) {
            numberOfXmasOccurrences += xmasCountAt(matrix, rowIndex, colIndex);
            numberOfCrossMasOccurrences += crossMasExistsAt(matrix, rowIndex, colIndex);
        }
    }

    // Part one
    cout << "Number of XMAS occurrences: " << numberOfXmasOccurrences << endl;

    // Part two
    cout << "Number of X-MAS occurrences: " << numberOfCrossMasOccurrences << endl;
}
