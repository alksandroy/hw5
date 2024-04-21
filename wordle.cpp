#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#endif

#include "dict-eng.h"
#include "wordle.h"
using namespace std;

// Add prototypes of helper functions here
void generateSatisfiedWords(string current,
                            set<string>& answers,
                            const string& in,
                            string floating,
                            size_t freedom);

// Definition of primary wordle function

std::set<std::string> wordle(const std::string& in,
                             const std::string& floating,
                             const std::set<std::string>& dict) {
    set<string> endlishWords, answers;
    size_t freedom = 0;
    for (char c : in)
        if (c == '-')
            freedom++;
    generateSatisfiedWords("", endlishWords, in, floating, freedom);
    for (string word : endlishWords) {
        if (dict.find(word) != dict.end()) {
            // cerr << word << endl;
            answers.insert(word);
        }
    }
    return answers;
}

void generateSatisfiedWords(string current,
                            set<string>& answers,
                            const string& in,
                            string floating,
                            size_t freedom) {
    // cerr << in << " " << current << (bool)(current.size() == in.size()) <<
    // endl;
    if (current.size() == in.size()) {
        if (floating == "")
            answers.insert(current);
        return;
    }

    if (freedom < floating.size())
        return;

    if (in[current.size()] != '-') {
        current.push_back(in[current.size()]);
        generateSatisfiedWords(current, answers, in, floating, freedom);
    } else {
        for (char c = 'a'; c <= 'z'; c++) {
            current.push_back(c);
            string newFloating = floating;

            for (size_t j = 0; j < floating.size(); j++)
                if (floating[j] == c) {
                    newFloating.erase(j, 1);
                    break;
                }
            generateSatisfiedWords(current, answers, in, newFloating, freedom - 1);
            current.pop_back();
        }
    }
}

// Define any helper functions here
