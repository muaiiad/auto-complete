#include "Trie.h"
#include <iostream>
#include <queue>


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
	if (temp->frequency >= 3) {
		temp->isWord = true;
	}
}

std::vector<std::string> Trie::frequencySearch(std::string prefix) {
	std::priority_queue<std::pair<int, std::string>> pq;
	std::queue<std::pair<Node*, std::string>> q;

	Node* root = searchWord(prefix);

	q.push(std::make_pair(root, prefix));


	while (!q.empty()) {
		std::pair<Node*, std::string> current = q.front();
		if (q.front().first->isWord) {
			pq.push({ q.front().first->frequency, q.front().second });
		}
		q.pop();

		for (auto& [letter, child] : current.first->children) {
			q.push(std::make_pair(&child, current.second + letter));
		}
	}


	std::vector<std::string> result;
	while (!pq.empty()) {
		result.push_back(pq.top().second);
		pq.pop();
	}
	return result;
}

std::vector<std::string> Trie::shortestSearch(std::string prefix) {
	std::vector<std::string> result;

	std::queue<std::pair<Node*, std::string>> q;

	Node* root = searchWord(prefix);

	q.push({root,prefix});


	while (!q.empty()) {
		std::pair<Node*, std::string> current = q.front();
		if (q.front().first->isWord) {
			result.push_back(q.front().second);
		}
		q.pop();

		for (auto& [letter, child] : current.first->children) {
			q.push({&child, current.second + letter});
		}
	}

	return result;
}

std::vector<std::string> Trie::lexicographicalSearch(std::string prefix) {
	std::vector<std::string> wordList;
	Node* source = searchWord(prefix);
	
	DFS(source,prefix,wordList);

	return wordList;
}

void Trie::DFS(Node* node, std::string& prefix, std::vector<std::string>& wordList) {
	if (node->isWord) {
		wordList.push_back(prefix);
	}
	for (std::map<char, Node>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
		char ch = it->first;
		Node& childNode = it->second;
		prefix.push_back(ch);
		DFS(&childNode, prefix, wordList);
		prefix.pop_back();

	}
}

