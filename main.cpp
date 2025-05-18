#include <iostream>
#include <fstream>
#include <vector>
#include "Trie.h"

#define FREQUENCY_ORDER 1
#define SHORTEST_ORDER 2
#define LEXIOGRAPHICAL_ORDER 3

/*
Autocomplete System - Feature Specification

Functionality:
--------------
1. Word Suggestion with Prefix Matching:
   - Users can enter a prefix and choose the sorting order for suggestions.
   - The system traverses the trie/subtree from the prefix node to generate suggestions.
   - Sorting options:
     a. Frequently searched terms appear first. (Default)
     b. Shortest words first (BFS-based).
     c. Lexicographical order (DFS-based).

2. Dictionary Management:
   - Add a Word:
     · User inputs a new word to be added to the dictionary. (done)
   - Delete a Word:
     · User can input an exact word for deletion, OR (done)
     · Enter a prefix and select the desired word from a list of matches.

3. Dynamic Dataset Expansion:
   - Track word usage frequency. (done)
   - Automatically add user-typed words to the dictionary once they've been used 3 or more times. 

4. Robustness & User Experience:
   - Case Insensitivity:
     · System treats uppercase and lowercase inputs the same (e.g., "Car" == "car"). (done)
   - Exact Match Highlighting:
     · If the user's input matches a word exactly, that word is highlighted in the suggestions.
   - Error Handling:
     · Gracefully handle invalid characters or unsupported inputs.
     · Manage empty/null inputs without crashing.



*/

void loadDictionary(Trie &trie) {
    std::string word;
    int frequency = 0;
    std::ifstream dictionary("Dictionary.txt");
    if (dictionary.is_open()) {
        while (dictionary >> word >> frequency) {
            trie.insertWord(word, frequency);
        }
        dictionary.close();
    }
    else {
        std::cerr << "File not found.\n";
    }
}
void writeDictionary(Trie& trie)
{
    std::string word;
    int frequency = 0;
    std::vector<std::string> words = trie.frequencySearch("");
    std::ofstream output("Dictionary.txt");

    if (output.is_open())
    {
        for (const auto& word : words)
        {
            Trie::Node* node = trie.searchWord(word);
            int frequency = (node && node->isWord) ? node->frequency : 0;
            output << word << " " << frequency << "\n";
        }
        output.close();
        std::cout << "Dictionary updated successfully.\n";
    }
    else
    {
        std::cerr << "Cannot open Dictionary.txt for writing.\n";
    }
}



void setWordList(const int& preferredOrder, std::vector<std::string> &wordList, Trie &trie, const std::string &key) {
    switch (preferredOrder)
    {
    case FREQUENCY_ORDER:
        wordList = trie.frequencySearch(key);
        break;
    case SHORTEST_ORDER:
        wordList = trie.shortestSearch(key);
        break;
    case LEXIOGRAPHICAL_ORDER:
        wordList = trie.lexicographicalSearch(key);
        break;
    default:
        break;
    }
}



int main() {
    Trie trie;
    loadDictionary(trie);

    int userInput = 0;
    int preferredOrder = FREQUENCY_ORDER; 

    do {
        std::cout <<
        "1 - Find word prefixes\n2 - Add word\n3 - Delete word / word prefix\n4 - Change word sorting order\n0 - Exit\n";

        std::cin >> userInput;
        if (userInput == 1) {
            std::string key;
            std::cout << "Enter word: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //necessary for ignoring previous newline
            getline(std::cin, key);

            while (key.empty() || key.find(" ") != std::string::npos) {
                std::cout << "No empty characters!\n";
                getline(std::cin, key);
            }

            trie.increaseFrequency(key);
            std::vector<std::string> wordList;
            setWordList(preferredOrder, wordList, trie, key);

            for (const auto& word : wordList) {
                std::cout << word << '\n';
            }
        }
        else if (userInput == 2) {
            std::string word;
            std::cout << "Enter word: ";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //necessary for ignoring previous newline
            getline(std::cin, word);

            while (word.empty() || word.find(" ") != std::string::npos ) {
                std::cout << "No empty characters!\n";
                getline(std::cin, word);
            }

            trie.insertWord(word);
        }
        else if (userInput == 3) {
            std::string word;
            std::cout << "Enter word: ";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //necessary for ignoring previous newline
            getline(std::cin, word);

            while (word.empty() || word.find(" ") != std::string::npos) {
                std::cout << "No empty characters!\n";
                getline(std::cin, word);
            }


            std::vector<std::string> wordList;
            setWordList(preferredOrder, wordList, trie, word);

            std::cout << "Select word from the following (Enter number):\n ";
            for (int i = 0;i<wordList.size();i++) {
                std::cout << i+1 << ". " <<  wordList[i] << '\n';
            }

            int idx;
            std::cin >> idx;
            trie.deleteWord(wordList[idx-1]);
        }
        else if (userInput == 4) {
            std::cout <<
            "1 - Most searched words first\n2 - Shortest words first\n3 - Sort alphabetically\n";
            std::cin >> preferredOrder;
        }
        else if (userInput == 0) {
            writeDictionary(trie);
        }

    } while (userInput != 0);
}