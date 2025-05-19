#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <cctype> //to add isalpha fn
#include "Trie.h"

#define FREQUENCY_ORDER 1
#define SHORTEST_ORDER 2
#define LEXIOGRAPHICAL_ORDER 3

#define RESET   "\033[0m"
#define CYAN     "\033[1;36m" // codes to color text in the terminal, used for highlighting


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
     - User inputs a new word to be added to the dictionary. (done)
   - Delete a Word:
     - User can input an exact word for deletion, OR (done)
     - Enter a prefix and select the desired word from a list of matches.

3. Dynamic Dataset Expansion:
   - Track word usage frequency. (done)
   - Automatically add user-typed words to the dictionary once they've been used 3 or more times.

4. Robustness &صيغة النص User Experience:
   - Case Insensitivity:
     - System treats uppercase and lowercase inputs the same (e.g., "Car" == "car"). (done)
   - Exact Match Highlighting:
     - If the user's input matches a word exactly, that word is highlighted in the suggestions.
   - Error Handling:
     - Gracefully handle invalid characters or unsupported inputs.
     - Manage empty/null inputs without crashing.
*/


void writeDictionary(Trie& trie)
{
    std::ofstream output("Dictionary.txt");
    try {
        if (!output.is_open()) {
            throw std::runtime_error("Cannot open Dictionary.txt for writing.");
        }

        std::vector<std::string> words = trie.frequencySearch("");
        for (const auto& word : words) {
            Trie::Node* node = trie.searchWord(word);
            int frequency = node->isWord ? node->frequency : 0;
            output << word << " " << frequency << "\n";
        }

        if (output.fail()) {
            throw std::runtime_error("Error writing to Dictionary.txt.");
        }

        output.close();
        std::cout << "Dictionary updated successfully.\n";
    }
    catch (const std::exception& e) {
        output.close();
        std::cerr << "Error writing dictionary: " << e.what() << "\n";
    }
}

void loadDictionary(Trie& trie)
{
    std::ifstream dictionary("Dictionary.txt");
    try {
        if (!dictionary.is_open()) {
            throw std::runtime_error("File not found or cannot be opened.");
        }

        std::string word;
        int frequency;
        while (dictionary >> word >> frequency) {
            if (dictionary.fail()) {
                throw std::runtime_error("Error reading Dictionary.txt.");
            }
            if (frequency < 0) {
                std::cerr << "Warning: Negative frequency for word '" << word << "' skipped.\n";
                continue;
            }
            try {
                trie.insertWord(word, frequency);
            }
            catch (const std::exception& e) {
                std::cerr << "Error loading word '" << word << "': " << e.what() << "\n";
                continue;
            }
        }
        dictionary.close();
    }
    catch (const std::exception& e) {
        dictionary.close();
        std::cerr << "Error loading dictionary: " << e.what() << "\n";
    }
}


int main() {
    Trie trie;
    loadDictionary(trie);
    int userInput = 0;
    int preferredOrder = SHORTEST_ORDER;

    do {
        std::cout << "1 - Find word prefixes\n2 - Add word\n3 - Delete word/prefix\n4 - Change sorting order\n0 - Exit\n";

        bool validInput = false;
        while (!validInput) {
            std::cout << "Enter choice: ";
            try {
                std::cin >> userInput;
                if (std::cin.fail()) {
                    throw std::invalid_argument("Input must be an integer!");
                }
                if (userInput < 0 || userInput > 4) {
                    throw std::invalid_argument("Input must be between 0 and 4!");
                }
                validInput = true;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        try {
            if (userInput == 1) {
                std::string key;
                std::cout << "Enter word or prefix: ";
                std::cin >> key;

                // Validate input
                if (key.empty()) {
                    throw std::invalid_argument("Input cannot be empty.");
                }
                for (char c : key) {
                    if (!std::isalpha(c)) {
                        throw std::invalid_argument("Input must contain only alphabetic characters.");
                    }
                }

                // Check if prefix exists first
                Trie::Node* node = trie.searchWord(key);
                if (node == nullptr) {
                    std::cout << "No suggestions found.\n";
                    continue; // Return to do while loop
                }

                std::vector<std::string> wordList;

                switch (preferredOrder) {
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
                    throw std::runtime_error("Invalid sorting order.");
                }

                if (wordList.empty()) {
                    std::cout << "No suggestions found.\n";
                }
                else {
                    trie.increaseFrequency(key);
                    writeDictionary(trie);
                    // Highlight exact match
                    for (const auto& word : wordList) {
                        if (word == key) {
                            std::cout << CYAN << word << RESET << "\n";
                        }
                        else {
                            std::cout << word << '\n';
                        }
                    }
                }

            }
            else if (userInput == 2) {
                std::string word;
                std::cout << "Enter word to add: ";
                std::cin >> word;


                if (word.empty()) {
                    throw std::invalid_argument("Can't add an empty word.");
                }

                for (char c : word) {
                    if (!std::isalpha(c)) {
                        throw std::invalid_argument("Word must contain only alphabetic characters.");
                    }
                }

                trie.insertWord(word);
                writeDictionary(trie);
                std::cout << "Word added successfully.\n";

            }
            else if (userInput == 3) {
                std::string word;
                std::cout << "Enter word : ";
                std::cin >> word;

                if (word.empty()) {
                    throw std::invalid_argument("Cannot delete an empty word.");
                }
                for (char c : word) {
                    if (!std::isalpha(c)) {
                        throw std::invalid_argument("Word must contain only alphabetic characters.");
                    }
                }

                if (!trie.searchWord(word)) {
                    throw std::invalid_argument("Word not found in dictionary.");
                }
                trie.deleteWord(word);
                writeDictionary(trie);
                std::cout << "Word deleted successfully.\n";

            }
            else if (userInput == 4) {
                std::cout << "1 - Most searched words first\n2 - Shortest words first\n3 - Sort alphabetically\n";

                std::cin >> preferredOrder;

                if (std::cin.fail() || preferredOrder < 1 || preferredOrder > 3) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Invalid sorting order. Choose 1, 2, or 3.");
                }

                std::cout << "Sorting order updated.\n";

            }
            else if (userInput == 0) {
                writeDictionary(trie);
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (userInput != 0);

    return 0;
}