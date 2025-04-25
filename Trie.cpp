#include "Trie.h"
#include <iostream>

Trie::Trie()
{
}

Trie::~Trie()
{
}

void Trie::insertWord(const std::string& word, const int freq) {

	Node* temp = &root;

	for (auto c : word) {
		char letter = tolower(c);
		if (temp->children.find(letter) == temp->children.end()) {
			temp->children[letter] = Node{ false , 0 };
		}
		temp = &temp->children[letter];
	}

	temp->isWord = true;
	temp->frequency = freq;
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

std::vector<std::string> Trie::frequencySearch(std::string prefix) {
	return std::vector<std::string>();
}

std::vector<std::string> Trie::shortestSearch(std::string prefix) {


	return std::vector<std::string>();
}

std::vector<std::string> Trie::lexicographicalSearch(std::string prefix) {
	std::vector<std::string> wordList;
	Node* node = searchWord(prefix);
	
	DFS(node,prefix,wordList);

	return wordList;
}

void Trie::DFS(Node* node, std::string& prefix, std::vector<std::string>& wordList) {

	

}
