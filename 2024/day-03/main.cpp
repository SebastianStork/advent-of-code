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

string getNextValidInstruction(string &line)
{
    while (true) {
        {
            size_t startPosition = line.find("mul(");
            if (startPosition == string::npos) {
                return "";
            }
            line.erase(0, startPosition);
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

int main()
{
    vector<string> lines = readInput();
    int finalResult = 0;

    for (string &line : lines) {
        while (true) {
            string instruction = getNextValidInstruction(line);
            if (instruction == "") {
                break;
            }
            finalResult += getInstructionResult(instruction);
        }
    }

    cout << "Sum of all the multiplication: " << finalResult << endl;
}
