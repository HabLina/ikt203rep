/*
 * Knuth-Morris-Pratt:
 * Time complexity - O(N+M)
 * Space complexity - O(n)
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 * DoubleSpace: function to remove extra spaces from the text and pattern
 */
void DoubleSpace(string& _s, string& _p) {
    // remove extra spaces in the text
    string new_text;
    bool space = false;
    for (char c : _s) {
        if (!(c == ' ' && space)) {
            new_text += c;
            space = (c == ' ');
        }
    }
    _s = new_text;

    // remove extra spaces in the pattern
    string new_pat;
    space = false;
    for (char c : _p) {
        if (!(c == ' ' && space)) {
            new_pat += c;
            space = (c == ' ');
        }
    }
    _p = new_pat;
}

/*
 * ComputePrefixTable: compute the prefix table for efficient pattern matching.
 * Time complexity - O(M)
 */
vector<int> ComputePrefixTable(const string& _pattern) {
    int M = (int)_pattern.length(); // length of the pattern
    vector<int> prefix_table(M, 0);

    int len = 0, i = 1;

    while (i < M) {
        if (_pattern[i] == _pattern[len]) {
            len++;
            prefix_table[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = prefix_table[len - 1];
            } else {
                prefix_table[i] = 0;
                i++;
            }
        }
    }
    return prefix_table;
}

/*
 * KMPSearch: recursive function for searching the pattern in the text
 */

void KMPSearch(const string& text, const string& pattern, int i, int j, const vector<int>& prefix_table) {
    if (i == text.length()) {
        if (j != 0) {
            cout << "Pattern is not found in the string" << endl;
        }
        return;  // reached the end of the text
    }

    // looping through the string/pattern to find the matches
    if (tolower(pattern[j]) == tolower(text[i])) { // converting to lowercase for case-insensitive search
        i++;
        j++;
    } else {
        if (j != 0) {
            j = prefix_table[j - 1];
        } else {
            i++;
        }
    }

    // pattern found
    if (j == pattern.length()) {
        cout << "Pattern found at index: " << i - j << endl;
        j = prefix_table[j - 1];
    }

    KMPSearch(text, pattern, i, j, prefix_table); // recursive concept
}

/*
 * KMP: main function for performing KMP
 */
void KMP(const string& _string, const string& _pattern) {
    int N = _string.length();
    int M = _pattern.length();

    if (M == 0 || N == 0) {
        cout << "Invalid input: the string or pattern is empty" << endl;
        return;
    }

    vector<int> prefix_table = ComputePrefixTable(_pattern);

    KMPSearch(_string, _pattern, 0, 0, prefix_table);
}

int main() {

    string text;
    string pattern;

    // UI for user input
    cout << "Enter the string: " << endl;
    getline(cin, text);

    cout << "Enter the pattern: " << endl;
    getline(cin, pattern);

    // preprocess text and pattern by removing extra spaces
    DoubleSpace(text, pattern);
    // performs the pattern search with KMP
    KMP(text, pattern);

    return 0;
}
