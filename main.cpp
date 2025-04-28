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

void writeDictionary(Trie& trie) {
    std::string word;
    int frequency = 0;

    // TODO, need one of the search algorithms (doesnt really matter which one)
}



int main() {

    /*
    Before we make the GUI, we'll have some primitive input system, like this:
    
    1 - Find word prefixes
    2 - Add word
    3 - Delete word/word prefix
    4 - Change word sorting order
    0 - Exit
    
    */
    Trie trie;
    loadDictionary(trie);

    int userInput = 0;
    int preferredOrder = 1; 

    do {
        std::cout <<
        "1 - Find word prefixes\n2 - Add word\n3 - Delete word / word prefix\n4 - Change word sorting order\n0 - Exit\n";

        std::cin >> userInput;
        if (userInput == 1) {
            std::string key;
            std::cout << "Enter word: ";
            std::cin >> key;
            trie.increaseFrequency(key);
            std::vector<std::string> wordList;
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
            for (const auto& word : wordList) {
                std::cout << word << '\n';
            }
        }
        else if (userInput == 2) {
            std::string word;
            std::cout << "Enter word: ";
            std::cin >> word;
            trie.insertWord(word);
        } else if (userInput == 3) {
            std::string word;
            std::cout << "Enter word: ";
            std::cin >> word;
            trie.deleteWord(word);
        }
        else if (userInput == 4) {
            std::cout <<
            "1 - Most searched words first\n2 - Shortest words first\n3 - Sort alphabetically\n";
            std::cin >> preferredOrder;
        }

    } while (userInput != 0);

    trie.insertWord("Hi");
    trie.insertWord("My");
    trie.increaseFrequency("Hi");

}