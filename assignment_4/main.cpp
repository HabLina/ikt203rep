#include <iostream>
#include <string>

using namespace std;

int changeDatatype(const string& input){
    int newInput;

    for(char c : input) {
        if (isdigit(c)){
            newInput = stof(input);
            return newInput;
        }else{
            break;
        }
    }

    return 1;
}

int main() {
    string input;

    std::cout << "Write in your input: " << std::endl;
    getline(cin, input);
    changeDatatype(input);

    if (changeDatatype(input) == 1) {

    } else {

    }

    return 0;
}
