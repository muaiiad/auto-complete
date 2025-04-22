#include "Trie.h"
#include <iostream>

Trie::Trie()
{
}

Trie::~Trie()
{
}

void Trie::insertWord(const std::string& word, const int frequency = 1) {

	Node* temp = &root;

	for (auto c : word) {
		char letter = tolower(c);
		if (temp->children.find(letter) == temp->children.end()) {
			temp->children[letter] = Node{ false , 0 };
		}
		temp = &temp->children[letter];
	}

	temp->isWord = true;
}

void Trie::deleteWord(const std::string& word) {

	Node* temp = &root;

	for (auto c : word) {
		char letter = tolower(c);
		if (temp->children.find(letter) == temp->children.end()) {
			std::cerr << "Word not found\n";
			return;
		}
		temp = &temp->children[letter];
	}

	temp->frequency = 0;
	temp->isWord = false;

}

Trie::Node* Trie::searchWord(const std::string& key)
{
	Node* temp = &root;

	for (auto c : key) {
		char letter = tolower(c);
		if (temp->children.find(letter) == temp->children.end()) {
			return nullptr;
		}
		temp = &temp->children[letter];
	}
	return temp;
}

void Trie::increaseFrequency(const std::string& word) {
	Node* temp = searchWord(word);

	if (temp == nullptr) {
		insertWord(word);
		return;
	}

	temp->frequency++;
}
