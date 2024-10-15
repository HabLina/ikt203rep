#ifndef POLYNOMIAL_EQUATION_FUNCTIONS_H
#define POLYNOMIAL_EQUATION_FUNCTIONS_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

/*
 * Stack: struct Node + class Stack
 */
struct Node {
    char data;
    Node* next;
    Node(char c) : data(c), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    bool isEmpty() {
        return top == nullptr;
    }
    char topStack() {
        if (isEmpty()) {
            cerr << "Error: Stack is empty" << endl;
            exit(1);
        }
        return top->data;
    }
    void push(Node c) {
        Node* new_node = new Node(c);
        new_node->next = top;
        top = new_node;
    }
    char pop() {
        if (isEmpty()) {
            cerr << "Error: Stack is empty" << endl;
            exit(1);
        }
        char data = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return data;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};
/*
 * Term
 */
struct Term {
    int coefficient{};
    string variable;
    int exponent{};
    string operators;
};

/*
 * Precedence: function to return precedence of operators (priority)
 */
int Precedence(char c) {
    // plus and minus
    if(c == '+' || c == '-') {
        return 1;
    }
        // division and multiplication
    else if(c == '/' || c == '*') {
        return 2;
    }
        // power
    else if(c == '^') {
        return 3;
    }
    else {
        return -1;
    }
}

/*
 * Operator: function to check if a character is an operator
 */
bool Operator(char c) {
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return true;
    }
    else {
        return false;
    }
}

/*
 * Convert: function to Convert infix- to postfix-expression
 */
string ConvertInfixToPostfix(const string& infix) {
    Stack stack;
    string postfix;

    for(char c : infix) {
        // if the character is an operand, we add it to the result output
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
           || (c >= '0' && c <= '9')) {
            postfix += c;
        }
            // if the character is an '(', we push it to the stack
        else if(c == '(') {
            stack.push('(');
        }
            // if the character is an ')', we pop and add the output string from the stack
            // until an '(' encounters
        else if(c == ')') {
            while(stack.topStack() != '(') {
                postfix += stack.topStack();
                stack.pop();
            }
            stack.pop();
        }
            // if the character is an operator
        else if(Operator(c)){
            while(!stack.isEmpty() && Precedence(c) <= Precedence(stack.topStack())) {
                postfix += stack.topStack();
                stack.pop();
            }
            stack.push(c);
        }
    }
    // pop the remaining characters from the stack
    while(!stack.isEmpty()) {
        postfix += stack.topStack();
        stack.pop();
    }

    return postfix;
}

/*
 * TokenizePolynomial: function to tokenize a polynomial equation
 */
std::vector<std::string> TokenizePolynomial(const std::string& equation) {
    std::vector<std::string> tokens;
    std::string token;
    bool inTerm = false;

    for (char c : equation) {
        if (c == ' ' || c == '\t') {
            continue;
        } else if (c == '+' || c == '-') {
            if (!inTerm) {
                token += c;
            } else {
                tokens.push_back(token);
                token = c;
            }
            inTerm = false;
        } else {
            token += c;
            inTerm = true;
        }
    }
    if (inTerm) {
        tokens.push_back(token);
    }

    return tokens;
}

/*
 * SplitTerm: function to split a term into coefficient, variable, and exponent
 */
void SplitTerm(const std::string& term, Term& result) {
    result.coefficient = 0;
    result.variable = "";
    result.exponent = 0;
    result.operators = "";

    // Handle cases where the term contains 'x' and '^'
    size_t xPos = term.find('x');
    size_t caretPos = term.find('^');
    size_t operatorPos = term.find_first_of("+-");

    if (xPos != std::string::npos) {
        // Check if 'x' is at the beginning or not
        if (xPos == 0) {
            result.coefficient = 1; // Term starts with 'x', e.g., "x^2" or "x"
        } else {
            std::string coefficientPart = term.substr(0, xPos);
            if (coefficientPart.empty()) {
                result.coefficient = 1; // Term is like "7x"
            } else {
                result.coefficient = std::stoi(coefficientPart); // Extract coefficient
            }
        }

        // Check if '^' is present
        std::string caretPart = term.substr(xPos + 1, caretPos - xPos - 1);
        if (caretPos != std::string::npos) {
            result.variable = "x";
            result.exponent = std::stoi(caretPart); // Extract exponent
            result.operators = term.substr(xPos + 1, caretPos - xPos);
        } else {
            // No '^' symbol, so assume the exponent is 1
            result.exponent = 1;
        }
    } else {
        result.coefficient = std::stoi(term); // Term is just a constant
    }
    // making sure that every joint with exponent more than zero has its 'x'
    if (result.variable.empty() && result.exponent != 0.0) {
        result.variable = "x";
    }
}

void SplitTerm(const std::string& term, double& coefficient, std::string& variable, int& exponent) {
    coefficient = 0.0;
    variable = "";
    exponent = 0;

    // Handle cases where the term contains 'x' and '^'
    size_t xPos = term.find('x');
    size_t caretPos = term.find('^');

    if (xPos != std::string::npos) {
        // Check if 'x' is at the beginning or not
        if (xPos == 0) {
            coefficient = 1.0; // Term starts with 'x', e.g., "x^2" or "x"
        } else {
            std::string coefficientPart = term.substr(0, xPos);
            if (coefficientPart.empty()) {
                coefficient = 1.0; // Term is like "7x"
            } else {
                coefficient = std::stod(coefficientPart); // Extract coefficient
            }
        }

        // Check if '^' is present
        if (caretPos != std::string::npos) {
            variable = "x";
            exponent = std::stoi(term.substr(caretPos + 1)); // Extract exponent
        } else {
            // No '^' symbol, so assume the exponent is 1
            exponent = 1;
        }
    } else {
        coefficient = std::stod(term); // Term is just a constant
    }
    // making sure that every joint with exponent more than zero has its 'x'
    if (variable.empty() && exponent != 0.0) {
        variable = "x";
    }
}

Term AddTerm(Term& term1, Term& term2) {
    if (term1.variable != term2.variable || term1.exponent != term2.exponent) {
        std::cerr << "Error: Cannot add terms with different variables or exponents." << std::endl;
        exit(1);
    }

    Term result;
    result.coefficient = term1.coefficient + term2.coefficient;
    result.variable = term1.variable;
    result.exponent = term1.exponent;
    return result;
}

bool CompareJoints(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
    return a.first > b.first;
}

string SortingPolynomial(const std::string& polynomial) {
    // Tokenize the poly string into joints
    std::vector<std::string> tokens = TokenizePolynomial(polynomial);

    // Sort the joints based on their positions
    std::vector<std::pair<int, std::string>> joints;

    for (const std::string& token : tokens) {
        double coefficient;
        std::string variable;
        int exponent;

        SplitTerm(token, coefficient, variable, exponent);

        // Combine the parts into a joint and store the position and joint
        int position = exponent; // Use the exponent as the position
        joints.emplace_back(position, token);
    }

    std::sort(joints.begin(), joints.end(), CompareJoints);

    // Reconstruct the sorted polynomial string
    std::string sortedPolynomial;

    for (size_t i = 0; i < joints.size(); ++i) {
        const std::string& joint = joints[i].second;

        // Check the sign of the joint
        char sign = '+';
        if (i > 0) {
            if (polynomial[joints[i - 1].first + joint.size()] == '-') {
                sign = '-';
                sortedPolynomial += sign + joint;
                continue;
            }else if(joints[i].first == 0 && joint.find('+')){
                sortedPolynomial += sign + joint;
                continue;
            }
        }

        // Append the sign and joint to the sorted polynomial
        sortedPolynomial += joint;
    }

    return sortedPolynomial;
}

void SplitAndSort(const string& equation1, const string& equation2) {
    double coefficient;
    string variable;
    int exponent;

    std::vector<std::string> terms1 = TokenizePolynomial(equation1);
    std::vector<std::string> terms2 = TokenizePolynomial(equation2);

    std::cout << "Tokens 1:" << std::endl;
    for (const std::string& term : terms1) {
        SplitTerm(term, coefficient, variable, exponent);
        std::cout << "Term: " << term << ", Coefficient " << coefficient
                  << ", Variable: " << variable << ", Exponent: " << exponent << std::endl;
    }
    std::cout << "Tokens 2:" << std::endl;
    for (const std::string& term : terms2) {
        SplitTerm(term, coefficient, variable, exponent);
        std::cout << "Term: " << term << ", Coefficient " << coefficient
                  << ", Variable: " << variable << ", Exponent: " << exponent << std::endl;
    }
}

string AddPolynomials(const string& polynomial1, const string& polynomial2) {
    std::vector<Term> terms1;
    std::vector<Term> terms2;
    std::vector<string> operators1;
    std::vector<string> operators2;

    // Tokenize and split the first polynomial
    size_t nextPos1 = 0;
    while (nextPos1 < polynomial1.size()) {
        size_t operatorIndex = polynomial1.find_first_of("+-", nextPos1);
        if (operatorIndex != std::string::npos) {
            std::string op = polynomial1.substr(operatorIndex, 1);
            operators1.push_back(op);
        }

        size_t endPos = (operatorIndex != std::string::npos) ? operatorIndex : polynomial1.size();
        std::string term = polynomial1.substr(nextPos1, endPos - nextPos1);

        Term parsedTerm;
        SplitTerm(term, parsedTerm);
        terms1.push_back(parsedTerm);

        nextPos1 = endPos + 1;
    }

    // Tokenize and split the second polynomial
    size_t nextPos2 = 0;
    while (nextPos2 < polynomial2.size()) {
        size_t operatorIndex = polynomial2.find_first_of("+-", nextPos2);
        if (operatorIndex != std::string::npos) {
            std::string op = polynomial2.substr(operatorIndex, 1);
            operators2.push_back(op);
        }

        size_t endPos = (operatorIndex != std::string::npos) ? operatorIndex : polynomial2.size();
        std::string term = polynomial2.substr(nextPos2, endPos - nextPos2);

        Term parsedTerm;
        SplitTerm(term, parsedTerm);
        terms2.push_back(parsedTerm);

        nextPos2 = endPos + 1;
    }

    // Combine coefficients and operators into a single vector
    std::vector<std::string> combinedTermsAndOperators1;
    std::vector<std::string> combinedTermsAndOperators2;
    size_t i = 0;
    size_t j = 0;

    // Combine terms and operators until one of the vectors is exhausted
    while (i < terms1.size()) {
        combinedTermsAndOperators1.push_back(operators1[i] + std::to_string(terms1[i].coefficient) + terms1[i].variable + "^" + std::to_string(terms1[i].exponent));
        ++i;
    }

    while (j < terms2.size()){
        combinedTermsAndOperators2.push_back(operators2[j] + std::to_string(terms2[j].coefficient) + terms2[j].variable + "^" + std::to_string(terms2[j].exponent));
        ++j;
    }

    std::vector<std::string> combinedResultTerms;

    size_t k = 0;
    size_t l = 0;

// Combine terms and operators until one of the vectors is exhausted
    while (k < combinedTermsAndOperators1.size() || l < combinedTermsAndOperators2.size()) {
        // Add the current element from combinedTermsAndOperators1
        if (k < combinedTermsAndOperators1.size()) {
            combinedResultTerms.push_back(combinedTermsAndOperators1[k]);
            k++;
        }

        // Add the current element from combinedTermsAndOperators2
        if (l < combinedTermsAndOperators2.size()) {
            combinedResultTerms.push_back(combinedTermsAndOperators2[l]);
            l++;
        }
    }

    /*// Construct the result string
    std::string result;
    for (const Term& term : resultTerms) {
        if (!result.empty()) {
            result += (term.coefficient >= 0.0) ? " + " : " - ";
        }
        result += std::to_string(std::abs(term.coefficient));
        if (!term.variable.empty()) {
            result += term.variable;
            if (term.exponent > 1) {
                result += "^" + std::to_string(term.exponent);
            }
        }
    }*/

    std::string result;

    return result;
}

#endif //POLYNOMIAL_EQUATION_FUNCTIONS_H
