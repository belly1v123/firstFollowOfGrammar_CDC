#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> firstSet, followSet;
set<char> nonTerminals;
set<char> terminals;
char startSymbol;

// Function to check if a symbol is non-terminal
bool isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

// Compute FIRST of a symbol
void computeFirst(char symbol) {
    if (!firstSet[symbol].empty()) return;

    // If symbol is a terminal
    if (!isNonTerminal(symbol)) {
        firstSet[symbol].insert(symbol);
        return;
    }

    for (string prod : grammar[symbol]) {
        for (int i = 0; i < prod.size(); i++) {
            char ch = prod[i];
            computeFirst(ch);
            // Add FIRST(ch) except epsilon
            for (char f : firstSet[ch]) {
                if (f != '#') firstSet[symbol].insert(f);
            }
            // If epsilon in FIRST(ch), continue to next symbol
            if (firstSet[ch].find('#') != firstSet[ch].end()) {
                if (i == prod.size() - 1) {
                    firstSet[symbol].insert('#');
                }
                continue;
            } else {
                break;
            }
        }
    }
}

// Compute FOLLOW of a non-terminal
void computeFollow(char symbol) {
    if (!followSet[symbol].empty() && symbol != startSymbol) return;

    if (symbol == startSymbol) {
        followSet[symbol].insert('$'); // $ marks end of input
    }

    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
        char lhs = it->first;
        vector<string> prods = it->second;
        for (string prod : prods) {
            for (int i = 0; i < prod.size(); i++) {
                if (prod[i] == symbol) {
                    // Case 1: symbol followed by something
                    if (i + 1 < prod.size()) {
                        char next = prod[i + 1];
                        // Add FIRST(next) except epsilon
                        for (char f : firstSet[next]) {
                            if (f != '#') followSet[symbol].insert(f);
                        }
                        // If epsilon in FIRST(next), add FOLLOW(lhs)
                        if (firstSet[next].find('#') != firstSet[next].end()) {
                            computeFollow(lhs);
                            for (char f : followSet[lhs]) {
                                followSet[symbol].insert(f);
                            }
                        }
                    }
                    // Case 2: symbol at end
                    else {
                        if (lhs != symbol) {
                            computeFollow(lhs);
                            for (char f : followSet[lhs]) {
                                followSet[symbol].insert(f);
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (use # for epsilon):\n";
    for (int i = 0; i < n; i++) {
        string prod;
        cin >> prod; // Example: E->E+T or T->id
        char lhs = prod[0];
        string rhs = prod.substr(3);

        grammar[lhs].push_back(rhs);
        nonTerminals.insert(lhs);

        for (char c : rhs) {
            if (!isNonTerminal(c) && c != '#') terminals.insert(c);
        }
        if (i == 0) startSymbol = lhs; // first production start symbol
    }

    // Compute FIRST sets
    for (char nt : nonTerminals) {
        computeFirst(nt);
    }

    // Compute FOLLOW sets
    for (char nt : nonTerminals) {
        computeFollow(nt);
    }

    cout << "\nFIRST sets:\n";
    for (char nt : nonTerminals) {
        cout << "FIRST(" << nt << ") = { ";
        for (char f : firstSet[nt]) cout << f << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (char nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (char f : followSet[nt]) cout << f << " ";
        cout << "}\n";
    }

    return 0;
}