#include <iostream>

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
     · User inputs a new word to be added to the dictionary.
   - Delete a Word:
     · User can input an exact word for deletion, OR
     · Enter a prefix and select the desired word from a list of matches.

3. Dynamic Dataset Expansion:
   - Track word usage frequency.
   - Automatically add user-typed words to the dictionary once they've been used 3 or more times.

4. Robustness & User Experience:
   - Case Insensitivity:
     · System treats uppercase and lowercase inputs the same (e.g., "Car" == "car").
   - Exact Match Highlighting:
     · If the user's input matches a word exactly, that word is highlighted in the suggestions.
   - Error Handling:
     · Gracefully handle invalid characters or unsupported inputs.
     · Manage empty/null inputs without crashing.



*/

int main() {

    /*
    Before we make the GUI, we'll have some primitive input system, like this:
    
    1 - Find word prefixes
    2 - Add word
    3 - Delete word/word prefix
    4 - Change word sorting order
    5 - Exit
    
    */


	std::cout << "Testing" << std::endl;
}