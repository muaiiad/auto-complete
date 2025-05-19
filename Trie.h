#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include<vector>
class Trie
{
public:
	struct Node {
		bool isWord = false;
		bool isExact = false;
		int frequency = 0;
		std::map<char, Node> children;
	};
private:
	Node root;
public:
	Trie();
	~Trie();
	void insertWord(const std::string& word, const int freq = 1);
	void deleteWord(const std::string& word);
	Node* searchWord(const std::string& key);
	void increaseFrequency(const std::string& word);
	std::vector<std::string> frequencySearch(std::string prefix);
	std::vector<std::string> shortestSearch(std::string prefix);
	std::vector<std::string> lexicographicalSearch(std::string prefix);
	void DFS(Node* node, std::string& prefix, std::vector<std::string>& wordList);




};

