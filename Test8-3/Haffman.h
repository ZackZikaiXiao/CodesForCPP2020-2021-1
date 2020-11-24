#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;
class Haffman
{
private:
	vector<int> m_weight;
	vector<Node<char>*> m_node;
	unordered_map<char, string> m_haffmanCode;	// hashman±àÂë
	string m_inputTest;		
public:
	Haffman() = default;
	Haffman(const string& text) :m_inputTest(text) {};
	void encode();
	void codeShow();
	template<typename T>
	void getCode(Node<T>* root, string s);
	void write(string filename);
	void decode(string inputCode, string filename);
};

