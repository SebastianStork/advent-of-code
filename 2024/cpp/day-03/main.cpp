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

bool isNumber(const string &potentialNumber)
{
    for (const char c : potentialNumber) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

string getNextValidInstruction(string &line, bool *doMultiplication = nullptr)
{
    const bool considerConditionals = doMultiplication;

    while (true) {
        {
            size_t mulPosition = line.find("mul(");
            if (mulPosition == string::npos) {
                return "";
            }

            if (considerConditionals) {
                size_t doPosition = line.find("do()");
                size_t dontPosition = line.find("don't()");

                if ((doPosition < mulPosition) && (dontPosition < mulPosition)) {
                    *doMultiplication = doPosition > dontPosition;
                } else {
                    if (doPosition < mulPosition) {
                        *doMultiplication = true;
                    } else if (dontPosition < mulPosition) {
                        *doMultiplication = false;
                    }
                }
            }

            line.erase(0, mulPosition);
        }

        if (considerConditionals && !*doMultiplication) {
            line.erase(0, 4);
            continue;
        }

        size_t commaPosition = line.find(',');
        if (commaPosition == string::npos) {
            return "";
        }

        size_t closingBracketPosition = line.find(')');
        if (closingBracketPosition == string::npos) {
            return "";
        }

        int lengthOfNumber1 = commaPosition - 4;
        int lengthOfNumber2 = closingBracketPosition - commaPosition - 1;
        if ((lengthOfNumber1 < 1 || lengthOfNumber1 > 3)
            || (lengthOfNumber2 < 1 || lengthOfNumber2 > 3)) {
            line.erase(0, 4);
            continue;
        }

        if (!isNumber(line.substr(4, lengthOfNumber1))
            || !isNumber(line.substr(commaPosition + 1, lengthOfNumber2))) {
            line.erase(0, 4);
            continue;
        }

        string validInstruction = line.substr(0, closingBracketPosition + 1);
        line.erase(0, closingBracketPosition + 1);

        return validInstruction;
    }
}

int getInstructionResult(const string &instruction)
{
    size_t commaPosition = instruction.find(',');
    int number1 = stoi(instruction.substr(4, commaPosition - 4));
    int number2 = stoi(
        instruction.substr(commaPosition + 1, instruction.length() - commaPosition - 1));
    return number1 * number2;
}

int calculateSumIgnoringConditionals(vector<string> lines)
{
    int result = 0;

    for (string &line : lines) {
        while (true) {
            string instruction = getNextValidInstruction(line);
            if (instruction.empty()) {
                break;
            }

            result += getInstructionResult(instruction);
        }
    }

    return result;
}

int calculateSumConsideringConditionals(vector<string> lines)
{
    int result = 0;
    bool doMultiplication = true;

    for (string &line : lines) {
        while (true) {
            string instruction = getNextValidInstruction(line, &doMultiplication);
            if (instruction.empty()) {
                break;
            }

            result += getInstructionResult(instruction);
        }
    }

    return result;
}

int main()
{
    vector<string> lines = readInput();

    // Part one
    cout << "Sum of all the multiplications: " << calculateSumIgnoringConditionals(lines) << endl;

    // Part two
    cout << "Sum of all the multiplications (when taking the conditional statements into account): "
         << calculateSumConsideringConditionals(lines) << endl;
}
