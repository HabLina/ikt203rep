#include <iostream>
#include "string"
#include "error_handling.h"
#include "functions.h"

using namespace std;

string InputPolynomial() {
    string equation;

    while (true) {
        try {
            cout << "Enter a polynomial equation in infix notation: " << endl;
            getline(cin, equation);

            if (hasExponentGreaterThan4(equation)) {
                throw invalid_argument("The expression has an exponent greater than 4.");
            }

            if (HasMultipleDistinctVariables(equation)) {
                throw invalid_argument("Invalid input. Please enter an equation with only one variable");
            }

            if (ContainsTrigonometricFunction(equation)) {
                throw invalid_argument("Invalid input. Please enter an equation without trigonometric functions.");
            }

            break;
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << " Please enter a new equation." << endl;
        }
    }

    return equation;
}

int main() {
    string infix_1, infix_2;
    string postfix_1, postfix_2, result_postfix;
/*
 * User-friendly Interface (UI)
 */
    // polynomial equation - infix notation
    infix_1 = InputPolynomial();
    infix_2 = InputPolynomial();
    cout << "Infix expression (1): " << infix_1 << endl;
    cout << "Infix expression (2): " << infix_2 << endl;

    SplitAndSort(infix_1, infix_2);

    string sorted_1 = SortingPolynomial(infix_1);
    string sorted_2 = SortingPolynomial(infix_2);
    cout << "Infix expression (1): " << sorted_1 << endl;
    cout << "Infix expression (2): " << sorted_2 << endl;

    // converting infix to postfix
    postfix_1 = ConvertInfixToPostfix(sorted_1);
    postfix_2 = ConvertInfixToPostfix(sorted_2);

    cout << "Postfix expression (1): " << postfix_1 << endl;
    cout << "Postfix expression (2): " << postfix_2 << endl;

    result_postfix = AddPolynomials(postfix_1, postfix_2);
    cout << "Postfix result: " << result_postfix << endl;
    result_postfix = ConvertInfixToPostfix(result_postfix);
    cout << "Postfix result: " << result_postfix << endl;

    return 0;
}