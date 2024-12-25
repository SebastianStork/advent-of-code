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

long computeEquationResult(const vector<int> &numbers, const size_t operatorMask)
{
    long testResult = numbers[0];

    for (size_t numberIndex = 1; numberIndex < numbers.size(); numberIndex++) {
        if (operatorMask & (1 << (numberIndex - 1))) {
            testResult += numbers[numberIndex];
        } else {
            testResult *= numbers[numberIndex];
        }
    }

    return testResult;
}

bool isValidEquation(const Equation &equation)
{
    const int operatorCount = equation.numbers.size() - 1;
    const size_t operatorMaskLimit = pow(2, operatorCount) - 1;

    for (size_t operatorMask = 0; operatorMask <= operatorMaskLimit; operatorMask++) {
        if (computeEquationResult(equation.numbers, operatorMask) == equation.result) {
            return true;
        }
    }

    return false;
}

int main()
{
    vector<Equation> equations;
    readInput(equations);

    long totalCalibrationResult = 0;
    for (const Equation &equation : equations) {
        totalCalibrationResult += equation.result * isValidEquation(equation);
    }

    // Part one
    cout << "Total Calibration Result: " << totalCalibrationResult << endl;
}
