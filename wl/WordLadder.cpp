/*
 * File: WordLadder.cpp
 * --------------------
 * Name: Sam Wemyss, z5019350
 */

// TODO: Remove using, update vector<std::string>'s' to be auto

#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

std::vector<std::vector<std::string>> generateWordLadders(Lexicon dict, const std::string start, const std::string end);
std::vector<std::string> possibleNewWords(Lexicon dict, std::string word);
char nextLetterInAlphabet(const char letter);
bool test_possibleNewWords();
bool test_nextLetterInAlphabet();

int main() {
    // Used for testing
    // std::cout << test_nextLetterInAlphabet() << '\n';
    // std::cout << test_possibleNewWords() << '\n';

    Lexicon dict("EnglishWords.dat");
    auto start = std::string{};
    auto end = std::string{};

    std::cout << "Enter start word (RETURN to quit): ";
    getline(std::cin, start);

    if (start.empty()) {
        return 0;   // RETURN was hit without any other input
    }

    std::cout << "Enter destination word: ";
    std::cin >> end;

    std::transform(start.begin(), start.end(), start.begin(), ::tolower);
    std::transform(end.begin(), end.end(), end.begin(), ::tolower);
    auto const ladders = generateWordLadders(dict, start, end);

    if (ladders.empty()) {
        std::cout << "No ladder found.\n";
    } else {
        std::cout << "Found ladder: ";
        for (auto const &ladder: ladders) {
            for (auto const &word: ladder) {
                std::cout << word << ' ';
            }
            std::cout << '\n';
        }
    }
	return 0;
}

/*
 * BFS Search to generate all the valid word ladders between the start and end word'
 * [0]: Lexicon containing valid words
 * [1]: Starting std::string
 * [2]: Ending std::string
 * RET: Container of all the shortest word ladders from the starting word to the ending word
 */
std::vector<std::vector<std::string>> generateWordLadders(Lexicon dict, const std::string start, const std::string end) {
    auto q = std::queue<std::vector<std::string>>{};
    auto result = std::vector<std::vector<std::string>>{};
    auto visited = std::unordered_set<std::string>{};
    auto wordCache = std::unordered_map<std::string, std::vector<std::string>>{};
    // Length of current path
    auto currLength = 1U;
    // Stores the last word of all the paths at the current length, so that when the length increases we can add them to the visited set
    auto currLengthWords = std::vector<std::string>{};
    // We should never get a ladder greater than MAX INT for this implementation
    auto minLadderLength = std::numeric_limits<unsigned int>::max();

    q.push(std::vector<std::string>{start});

    while (! q.empty()) {
        auto curr = q.front();
        auto lastWord = curr.back();
        q.pop();
        visited.insert(lastWord);

        // If we have found all the shortest ladders, end
        if (curr.size() > minLadderLength) {
            break;
        }

        // If the length of the current path is greater than the previous path/s, add all the words in currLengthWords to visited set
        if (curr.size() > currLength) {
            std::copy(currLengthWords.begin(), currLengthWords.end(), std::inserter(visited, visited.end()));
            currLengthWords.clear();
            currLength = curr.size();
        }

        if (lastWord == end) {
            // Found a valid path, add to results
            result.push_back(curr);
            minLadderLength = curr.size();
        } else {
            // Using memoization to drastically improve performance
            if (wordCache.find(lastWord) == wordCache.end()) {
                auto newWords = possibleNewWords(dict, lastWord);
                wordCache.emplace(lastWord, newWords);
            }
            // Add all valid children paths to the queue, and to currLengthWords
            for (auto const &word: wordCache.at(lastWord)) {
                if (visited.find(word) == visited.end()) {
                   currLengthWords.push_back(word);
                   auto newPath = curr;
                   newPath.push_back(word);
                   q.push(newPath);
               }
           }
       }
    }
    return result;
}

// Generates a sorted list of possible new words from the dictionary that are one letter different from the starting word
std::vector<std::string> possibleNewWords(Lexicon dict, std::string word) {
    auto result = std::vector<std::string>{};
    for (auto i = 0U; i < word.length(); ++i) {
        auto currLetter = 'a';
        do {
            if (currLetter != word[i]) {
                auto newWord = word;
                newWord[i] = currLetter;
                if (dict.containsWord(newWord)) {
                    result.push_back(newWord);
                }
            }
            currLetter = nextLetterInAlphabet(currLetter);
        } while (currLetter != 'a');
    }
    std::sort(result.begin(), result.end());
    return result;
}

// Returns the next letter in the alphabet with wrap-around
char nextLetterInAlphabet(const char letter) {
    return letter == 'z' || letter == 'Z' ? letter - 25 : letter + 1;
}



////////////////
// UNIT TESTS //
////////////////
bool test_possibleNewWords() {
    Lexicon lex;
    lex.add("dog");
    lex.add("cat");
    lex.add("dogs");
    lex.add("dot");
    lex.add("do");
    lex.add("god");
    lex.add("birdy");
    lex.add("o");
    lex.add("dag");
    lex.add("rag");
    lex.add("bog");
    auto const result = possibleNewWords(lex, "dog");
    return result[0] == "bog" && result[1] == "dag" && result[2] == "dot";
}

bool test_nextLetterInAlphabet() {
    return
    nextLetterInAlphabet('a') == 'b' &&
    nextLetterInAlphabet('b') == 'c' &&
    nextLetterInAlphabet('c') == 'd' &&
    nextLetterInAlphabet('y') == 'z' &&
    nextLetterInAlphabet('z') == 'a' &&
    nextLetterInAlphabet('A') == 'B' &&
    nextLetterInAlphabet('Z') == 'A';
}
