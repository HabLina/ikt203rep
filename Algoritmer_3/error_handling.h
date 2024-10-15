#ifndef POLYNOMIAL_EQUATION_ERROR_HANDLING_H
#define POLYNOMIAL_EQUATION_ERROR_HANDLING_H

#include <set>

using namespace std;

bool hasExponentGreaterThan4(const string& equation) {
    size_t pos = equation.find('^');
    if (pos != string::npos) {
        // Found '^' in the equation.
        try {
            int exponent = stoi(equation.substr(pos + 1));
            if (exponent > 4) {
                return true;
            }
        } catch (const invalid_argument& e) {
            // Ignore and continue if conversion to integer fails.
        }
    }
    return false;
}
bool IsValidVariable(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool HasMultipleDistinctVariables(const string& infix) {
    set<char> variables;

    for (char c : infix) {
        if (IsValidVariable(c)) {
            variables.insert(c);
            if (variables.size() > 1) {
                return true;
            }
        }
    }

    return false;
}

bool ContainsTrigonometricFunction(const string& infix) {
    const string trigFunctions[] = {"sin", "cos", "tan", "log", "exp"};

    for (const string& func : trigFunctions) {
        if (infix.find(func) != string::npos) {
            return true;
        }
    }

    return false;
}

#endif //POLYNOMIAL_EQUATION_ERROR_HANDLING_H
