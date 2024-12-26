#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Equation
{
    long result;
    vector<int> numbers;
};

void readInput(vector<Equation> &equations)
{
    string line;
    while (getline(cin, line)) {
        stringstream stream(line);
        Equation equation;

        string result;
        getline(stream, result, ':');
        equation.result = stol(result);

        int number;
        while (stream >> number) {
            equation.numbers.push_back(number);
        }

        equations.push_back(equation);
    }
}

long computeEquationResult(const vector<int> &numbers,
                           size_t operatorMask,
                           const size_t operatorSpace)
{
    long currentResult = numbers[0];

    for (size_t operatorIndex = 0; operatorIndex < numbers.size() - 1; operatorIndex++) {
        size_t numberIndex = operatorIndex + 1;

        int currentOperator = (operatorMask / static_cast<int>(pow(operatorSpace, operatorIndex)))
                              % operatorSpace;

        switch (currentOperator) {
        case 0:
            currentResult += numbers[numberIndex];
            break;
        case 1:
            currentResult *= numbers[numberIndex];
            break;
        case 2:
            currentResult = stol(to_string(currentResult) + to_string(numbers[numberIndex]));
        default:
            break;
        }
    }

    return currentResult;
}

bool isValidEquation(const Equation &equation, const size_t operatorSpace)
{
    const size_t operatorCount = equation.numbers.size() - 1;
    const size_t maxOperatorMask = pow(operatorSpace, operatorCount) - 1;

    for (size_t operatorMask = 0; operatorMask <= maxOperatorMask; operatorMask++) {
        if (computeEquationResult(equation.numbers, operatorMask, operatorSpace)
            == equation.result) {
            return true;
        }
    }

    return false;
}

int main()
{
    vector<Equation> equations;
    readInput(equations);

    long totalResult = 0;
    long totalResultWithConcatenation = 0;
    for (const Equation &equation : equations) {
        if (isValidEquation(equation, 2)) {
            totalResult += equation.result;
            totalResultWithConcatenation += equation.result;
        } else if (isValidEquation(equation, 3)) {
            totalResultWithConcatenation += equation.result;
        }
    }

    // Part one
    cout << "Total calibration result: " << totalResult << endl;

    // Part one
    cout << "Total calibration result with concatenation: " << totalResultWithConcatenation << endl;
}
